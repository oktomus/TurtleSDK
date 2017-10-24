#include "baseShader.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
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
