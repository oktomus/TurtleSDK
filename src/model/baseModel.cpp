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
    if(indices.size())
    {
        glDrawElements(_mode, indices.size(), GL_UNSIGNED_INT, 0);
    }
    else
    {
        glDrawArrays(_mode, 0, _nb_points);
    }
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

    code = initArray();
    if(code != 0) throw std::runtime_error(
                "Unable to init the vertext buffer");
}

int Base::initArray()
{
    
    glGenVertexArrays( 1, &vaoPosition );
    glGenBuffers( 1, &vboPosition);
    glGenBuffers( 1, &eboPosition);

    glBindVertexArray( vaoPosition );

    glBindBuffer( GL_ARRAY_BUFFER, vboPosition );
    glBufferData( GL_ARRAY_BUFFER, data.size() * sizeof( float ), data.data(), GL_STATIC_DRAW );

    if(indices.size())
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboPosition);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
                indices.size() * sizeof(unsigned int),
                indices.data(),
                GL_STATIC_DRAW);
    }

    // VAO Attributes
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0 );
    glEnableVertexAttribArray(0);

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );

    return 0;
}
