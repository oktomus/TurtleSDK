#include "mesh.h"

#include <stdexcept>
#include <iostream>

Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<GLuint> & indices,
           const std::vector<Texture> & textures)
    :
      points_(vertices),
      indices_(indices),
      textures_(textures)
{

    init();
}

void Mesh::draw(const Shader & shader, const GLenum& mode) const
{
    // Drawing depends on indices if they have been set or not

    // Need to generate texture names
    GLuint diffi = 1;
    GLuint speci = 1;
    GLuint heighti = 1;

    for(size_t i = 0; i < textures_.size(); ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string num, name = textures_.at(i).type;
        if (name == "texture_diffuse")
            num = std::to_string(diffi++);
        else if (name == "texture_specular")
            num = std::to_string(speci++);
        else if (name == "texture_height")
            num = std::to_string(heighti++);

        shader.setInt(("material." + name + num).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, textures_.at(i).id);
    }

    glBindVertexArray(_vaoId);
    if (mode == -1) glDrawElements(_drawMode, indices_.size(), GL_UNSIGNED_INT, 0);
    else glDrawElements(mode, indices_.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray( 0 );
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::updateDataBuffer()
{
    glBindVertexArray(_vaoId);
    glBindBuffer(GL_ARRAY_BUFFER, _vboId);
    glBufferData(GL_ARRAY_BUFFER, points_.size() * sizeof(Vertex),
                 points_.data(), GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void Mesh::init()
{
    // Most important object
    glGenVertexArrays( 1, &_vaoId );
    glBindVertexArray(_vaoId);

    GLuint ebo;
    addBuffer(_vboId, GL_ARRAY_BUFFER, points_);
    addBuffer(ebo, GL_ELEMENT_ARRAY_BUFFER, indices_);

    // positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, Normal));
    // Tex coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}


template <class T>
void Mesh::addBuffer(
        GLuint &idLocation,
        GLenum bufType,
        const std::vector<T>& data)
{
    // VAO bind could be done here to be sure
    // But since this is a private method
    // Nothing to worry about
    glGenBuffers( 1, &idLocation);
    glBindBuffer(bufType, idLocation);
    glBufferData(bufType, data.size() * sizeof(T),
                 data.data(), GL_STATIC_DRAW);
}

