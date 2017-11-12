#include "mesh.h"

#include <stdexcept>
#include <iostream>

Mesh::Mesh()
{

    // Default values
    _drawMode = GL_TRIANGLES;
    _transformUpdate = true;

    _position = {0, 0, 0};
    _scale = {1, 1, 1};
    _rotation = {0, 0, 0};
    _vertCount = 0;
    _eboCount = 0;

    // Most important object
    glGenVertexArrays( 1, &_vaoId );
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

void Mesh::setPoints(const std::vector<GLfloat>& data)
{
    // A point is x y z
    _vertCount = data.size() / 3;
    // We don't need to store buffers ids, only the vao

    GLuint vbopos;
    glBindVertexArray(_vaoId);
    addBuffer(vbopos, GL_ARRAY_BUFFER, data);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *) 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::setIndices(const std::vector<GLuint>& data)
{
    // All changes happen when we unbind the vao
    // So we must not unbind the ebo or change the vector
    _eboCount = data.size();
    GLuint ebopos;
    glBindVertexArray(_vaoId);
    addBuffer(ebopos, GL_ELEMENT_ARRAY_BUFFER, data);
    glBindVertexArray(0);
}

void Mesh::draw() const
{
    // Drawing depends on indices if they have been set or not
    glBindVertexArray(_vaoId);
    if (_eboCount)
        glDrawElements(_drawMode, _eboCount, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(_drawMode, 0, _vertCount);
    glBindVertexArray( 0 );
}

void Mesh::drawPoints() const
{
    // Simplest drawing method
    glBindVertexArray(_vaoId);
    if (_eboCount)
        glDrawElements(GL_POINTS, _eboCount, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(GL_POINTS, 0, _vertCount);
    glBindVertexArray( 0 );
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

Mesh Mesh::triangle(const std::vector<GLfloat> & points)
{
    // Create a triangle
    // We can create multiple triangle
    // As long as we specify points 3 by 3
    if (points.size() != 3)
        throw std::invalid_argument("3 points are required to create a triangle. 9 values.");
    Mesh triangle;
    triangle._drawMode = GL_TRIANGLES;
    triangle.setPoints(points);
    // No ebo required -> 0, 1, 2, 3.. redundant
    return triangle;
}

Mesh Mesh::quad(const std::vector<GLfloat> & points)
{
    if(points.size() != 12)
        throw std::invalid_argument("4 points are required to create a quad. 12 values.");

    Mesh quad;
    quad._drawMode = GL_TRIANGLES;

    quad.setPoints(points);
    quad.setIndices({0, 1, 3, 1, 2, 3});

    return quad;

}
