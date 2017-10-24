#include "baseShader.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <map>
#include <string>

#include <GL/gl.h>

/*
        █                 █               
  ▄▄▄   █ ▄▄    ▄▄▄    ▄▄▄█   ▄▄▄    ▄ ▄▄ 
 █   ▀  █▀  █  ▀   █  █▀ ▀█  █▀  █   █▀  ▀
  ▀▀▀▄  █   █  ▄▀▀▀█  █   █  █▀▀▀▀   █    
 ▀▄▄▄▀  █   █  ▀▄▄▀█  ▀█▄██  ▀█▄▄▀   █    

 */

const std::string shader::readFile(const std::string & path)
{
    std::ifstream txtFile(path);

    if (!txtFile.is_open())
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier " + path);
    }

    std::string txtContent(
            (std::istreambuf_iterator<char>(txtFile)),
            (std::istreambuf_iterator<char>()) 
            );


    txtFile.close();
    return txtContent;
}

GLuint shader::compileShader(
        const std::string & sourcePath,
        const GLenum& shaderType){

    // Create an index

    GLuint index = glCreateShader(shaderType);

    if (index == 0)
    {
        throw std::runtime_error(
                "Unable to create a shader for " + sourcePath
                );
    }

    // Fetch the source

    const std::string source = shader::readFile(sourcePath);
    const char* sourceChar = source.c_str();

    // Load the source
    glShaderSource( index, 1, &sourceChar, nullptr );

    // Compile the source
    glCompileShader( index );

    // Check compilation state

    GLint compileStatus;
    glGetShaderiv( index, GL_COMPILE_STATUS, &compileStatus );

    if ( compileStatus == GL_FALSE )
    {

        GLint logInfoLength = 0;
        glGetShaderiv( index, GL_INFO_LOG_LENGTH, &logInfoLength );
        if ( logInfoLength > 0 )
        {
            GLchar* infoLog = new GLchar[logInfoLength];
            GLsizei length = 0;
            glGetShaderInfoLog( index, logInfoLength, &length, infoLog );
            throw std::runtime_error(
                    "Unable to compile " + sourcePath + "\nLog:\n" + infoLog);
        }

        throw std::runtime_error("Unable to compile " + sourcePath);
    }

    // Success
    return index;

}

shader::Base::Base(const std::string& path)
    : _cam(0)
{

    programId = glCreateProgram();

    if (programId == 0)
    {
        throw std::runtime_error("Unable to create the program object for the material");
    }

    vertexId = shader::compileShader(path + ".vert", GL_VERTEX_SHADER);
    fragId = shader::compileShader(path + ".frag", GL_FRAGMENT_SHADER );

    glAttachShader( programId, vertexId );
    glAttachShader( programId, fragId );

    glLinkProgram( programId );

}

void shader::Base::use() const
{
    glUseProgram( programId );

    // Camera Uniforms
    // View matrix
    std::cout << U_viewMat << "\n";
    /*
    if (_uniformsLocation.count(U_viewMat) < 1){

        _uniformsLocation.insert(
                std::make_pair<std::string, GLuint>(
                    "something", glGetUniformLocation(programId, U_viewMat)
                    )
                );
    }

    if ( _uniformsLocation.at(U_viewMat) >= 0 )
    {
        glUniformMatrix4fv(
                _uniformsLocation.at(U_viewMat), 1, GL_FALSE, 
                glm::value_ptr(_cam->viewMatrix() ) 
                );
    }
    */

    /*
    // Projection matrix
    if (_uniformsLocation.count(U_viewMat) < 1){
        _uniformsLocation[U_projMat] = glGetUniformLocation(programId, U_projMat);
    }

    if ( _uniformsLocation.at(U_projMat) >= 0 )
    {
        glUniformMatrix4fv(
                _uniformsLocation.at(U_projMat), 1, GL_FALSE, 
                glm::value_ptr(_cam->projectionMatrix()) 
                );
    }
    */
}

const GLuint & shader::Base::id() const
{
    return programId;
}

void shader::Base::setCamera(const camera::Camera& cam)
{
    _cam = &cam;
}
