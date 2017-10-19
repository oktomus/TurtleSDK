// Class
#include "base.h"

// System
#include <iostream>

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

Base::Base(GLenum mode) : _mode(mode), vboPosition(0), vaoPosition(0)
{
    data = {
        -1.f, -1.f, 0.f,
        1.f, -1.f, 0.f,
        0.f,  1.f, 0.f
    };

    int code;

    code = initArrayBuffer();
    if(code != 0) throw std::runtime_error(
                "Impossibile d'initialiser le VBO");

    code = initArrayObject();
    if(code != 0) throw std::runtime_error(
                "Impossibile d'initialiser le VAO");
}

void Base::draw()
{
    glBindVertexArray(vaoPosition);
    glDrawArrays(_mode, 0, 3);
    glBindVertexArray( 0 );
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
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
    // Enable access to attribute 0
    glEnableVertexAttribArray(0);

    // unbind VAO
    glBindVertexArray( 0 );
    // unbind VBO
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    return 0;
}
