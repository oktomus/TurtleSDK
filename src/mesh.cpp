#include "mesh.h"

#include <stdexcept>
#include <iostream>

Mesh::Mesh(const std::vector<Vertex> &vertices,
           const std::vector<GLuint> & indices,
           const std::vector<Texture> & textures)
{
    // Default values
    _drawMode = GL_TRIANGLES;
    _transformUpdate = true;

    _position = {0, 0, 0};
    _scale = {1, 1, 1};
    _rotation = {0, 0, 0};

    _indicesCount = indices.size();

    // Most important object
    glGenVertexArrays( 1, &_vaoId );
    glBindVertexArray(_vaoId);

    GLuint vbo, ebo;
    addBuffer(vbo, GL_ARRAY_BUFFER, vertices);
    addBuffer(ebo, GL_ELEMENT_ARRAY_BUFFER, indices);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glBindVertexArray(0);
}

void Mesh::draw(const Shader & shader, const GLenum& mode) const
{
    // Drawing depends on indices if they have been set or not
    glBindVertexArray(_vaoId);
    if (mode == -1) glDrawElements(_drawMode, _indicesCount, GL_UNSIGNED_INT, 0);
    else glDrawElements(mode, _indicesCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray( 0 );
}

void Mesh::drawPoints(const Shader & shader) const
{
    draw(shader, GL_POINTS);
}


const glm::mat4& Mesh::getTransform()
{
    // Return the matrix used in shader to display the model

    if (_transformUpdate)
    {
        this->_transform = glm::mat4();
        this->_transform = glm::scale(
                    this->_transform,
                    this->_scale
                    );
        this->_transform = glm::rotate(
                    this->_transform,
                    this->_rotation[0],
                glm::vec3(1, 0, 0)
                );
        this->_transform = glm::rotate(
                    this->_transform,
                    this->_rotation[1],
                glm::vec3(0, 1, 0)
                );
        this->_transform = glm::rotate(
                    this->_transform,
                    this->_rotation[2],
                glm::vec3(0, 0, 1)
                );
        this->_transform = glm::translate(
                    this->_transform,
                    this->_position
                    );
        _transformUpdate = false;
    }

    return this->_transform;
}

Mesh Mesh::triangle()
{
    // Create a triangle
    std::vector<Vertex> points;
    points.push_back({{-.5f, -.5f, 0.f}});
    points.push_back({{.5f, -.5f, 0.f}});
    points.push_back({{.0f, .5f, 0.f}});

    Mesh triangle(points, {0, 1, 2}, {});
    return triangle;
}

Mesh Mesh::quad()
{
    std::vector<Vertex> points;
    points.push_back({{-.5f, -.5f, 0.f}});
    points.push_back({{.5f, -.5f, 0.f}});
    points.push_back({{.5f, .5f, 0.f}});
    points.push_back({{-.5f, .5f, 0.f}});

    Mesh quad(points, {0, 1, 3, 1, 2, 3}, {});
    return quad;
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

