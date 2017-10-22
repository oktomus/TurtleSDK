// Class
#include "base.h"

// System
#include <iostream>
#include <stdexcept>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

/*
 █                          
 █▄▄▄    ▄▄▄    ▄▄▄    ▄▄▄  
 █▀ ▀█  ▀   █  █   ▀  █▀  █ 
 █   █  ▄▀▀▀█   ▀▀▀▄  █▀▀▀▀ 
 ██▄█▀  ▀▄▄▀█  ▀▄▄▄▀  ▀█▄▄▀ 
 */

using namespace model;

Base::Base(GLenum mode, size_t points) : 
    _mode(mode), 
    vboPosition(0), 
    vaoPosition(0), 
    nb_points(_nb_points),
    _nb_points(points)
{
}

void Base::draw()
{
    glBindVertexArray(vaoPosition);
    glDrawArrays(_mode, 0, _nb_points);
    glBindVertexArray( 0 );
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
    std::cout << "Initialisation du VBO\n";

    // VBO ID
    std::cout << "Gen Buffer...\n";
    std::cout << "VBO " << vboPosition << "\n";
    glGenBuffers( 1, &vboPosition);
    // bind VBO
    std::cout << "Bind Buffer...\n";
    glBindBuffer( GL_ARRAY_BUFFER, vboPosition );
    // CPU to host
    std::cout << "Buffer Data...\n";
    glBufferData( GL_ARRAY_BUFFER, data.size() * sizeof( float ), data.data(), GL_STATIC_DRAW );
    // unbind
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    return 0;
}

int Base::initArrayObject()
{
    std::cout << "Initialisation du VAO\n";

    glGenVertexArrays( 1, &vaoPosition );
    // bind VAO
    glBindVertexArray( vaoPosition );
    // bind VBO
    glBindBuffer( GL_ARRAY_BUFFER, vboPosition );
    glVertexAttribPointer( 0, _nb_points, GL_FLOAT, GL_FALSE, 0, 0 );
    // Enable access to attribute 0
    glEnableVertexAttribArray(0);

    // unbind VAO
    glBindVertexArray( 0 );
    // unbind VBO
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    return 0;
}
