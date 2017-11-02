// Class
#include "baseModel.h"

// System
#include <iostream>
#include <stdexcept>

/*
                   █         ▀▀█   
 ▄▄▄▄▄   ▄▄▄    ▄▄▄█   ▄▄▄     █   
 █ █ █  █▀ ▀█  █▀ ▀█  █▀  █    █   
 █ █ █  █   █  █   █  █▀▀▀▀    █   
 █ █ █  ▀█▄█▀  ▀█▄██  ▀█▄▄▀    ▀▄▄ 

 */

using namespace model;

Base::Base(GLenum mode, size_t points) : 
    _mode(mode), 
    vboPosition(0), 
    vaoPosition(0), 
    _nb_points(points),
    _meshColor(1.f)
{
}

void Base::draw()
{
    glBindVertexArray(vaoPosition);
    glDrawArrays(_mode, 0, _nb_points);
    glBindVertexArray( 0 );
}

void Base::draw_points()
{
    glBindVertexArray(vaoPosition);
    glDrawArrays(GL_POINTS, 0, _nb_points);
    glBindVertexArray( 0 );
}

void Base::setColor(const float& r, const float& g, const float& b)
{
    _meshColor[0] = r;
    _meshColor[1] = g;
    _meshColor[2] = b;
}

const glm::vec3&  Base::color() const
{
    return _meshColor;
}

const glm::mat4& Base::matrix()
{
    this->_meshMatrix = glm::rotate( 
            glm::mat4(),
            static_cast< float >(glfwGetTime()), 
            glm::vec3( 0.0f, 1.f, 0.f ) );
    return this->_meshMatrix;

}

void Base::prepare()
{
    int code;

    code = initArrayBuffer();
    if(code != 0) throw std::runtime_error(
                "Impossibile d'initialiser le VBO");

    code = initArrayObject();
    if(code != 0) throw std::runtime_error(
                "Impossibile d'initialiser le VAO");
}

int Base::initArrayBuffer()
{

    // VBO ID
    glGenBuffers( 1, &vboPosition);
    // bind VBO
    glBindBuffer( GL_ARRAY_BUFFER, vboPosition );
    // CPU to host
    glBufferData( GL_ARRAY_BUFFER, data.size() * sizeof( float ), data.data(), GL_STATIC_DRAW );
    // unbind
    glBindBuffer( GL_ARRAY_BUFFER, 0 );


    return 0;
}

int Base::initArrayObject()
{

    glGenVertexArrays( 1, &vaoPosition );
    // bind VAO
    glBindVertexArray( vaoPosition );
    // bind VBO
    glBindBuffer( GL_ARRAY_BUFFER, vboPosition );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    // Enable access to attribute 0
    glEnableVertexAttribArray(0);

    // unbind VAO
    glBindVertexArray( 0 );
    // unbind VBO
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    return 0;
}
