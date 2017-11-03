#include "baseShader.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <map>
#include <string>

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
                    "Unable to compile the shader " + sourcePath + "\nLog:\n" + infoLog);
        }

        throw std::runtime_error("Unable to compile the shader " + sourcePath);
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

    GLint success;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if(!success) {
        GLint logInfoLength = 0;
        glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logInfoLength );
        if ( logInfoLength > 0 )
        {
            GLchar* infoLog = new GLchar[logInfoLength];
            GLsizei length = 0;
            glGetProgramInfoLog(programId, logInfoLength, &length, infoLog);
            throw std::runtime_error(
                    "Unable to link the material" + path + "\nLog:\n" + infoLog);
        }
        throw std::runtime_error("Unable to link the material " + path);
    }
    glDeleteShader(vertexId);
    glDeleteShader(fragId);  


}

void shader::Base::use() const
{
    glUseProgram( programId );
    GLuint uniformLocation;

    uniformLocation = glGetUniformLocation( id(), U_names[U_time] );
    if ( uniformLocation >= 0 )
    {
        glUniform1f( uniformLocation, 
                static_cast< float >(glfwGetTime())
                );
    }
    // Camera Uniforms
    if(_cam)
    {
        uniformLocation = glGetUniformLocation(programId, U_names[U_viewMat] );

        if ( uniformLocation >= 0 )
        {
            glUniformMatrix4fv(uniformLocation, 1, 
                    GL_FALSE, glm::value_ptr(_cam->viewMatrix()));
        }


        uniformLocation = glGetUniformLocation(programId, U_names[U_projMat] );

        if ( uniformLocation >= 0 )
        {
            glUniformMatrix4fv(uniformLocation, 1, 
                    GL_FALSE, glm::value_ptr(_cam->projectionMatrix()));
        }
        
    }


}

const GLuint & shader::Base::id() const
{
    return programId;
}

void shader::Base::setCamera(const camera::Camera& cam)
{
    _cam = &cam;
    glUseProgram( programId );
}

void shader::Base::updateUniforms()
{
    glUseProgram( programId );
    throw std::runtime_error("Not implemented");
    /*
    // View matrix
    _uniformsLocation[U_viewMat] = glGetUniformLocation(programId, shader::U_names[U_viewMat]);
    // Projection matrix
    _uniformsLocation[U_projMat] = glGetUniformLocation(programId, shader::U_names[U_projMat]);
    */


    glUseProgram( 0 );
}
void shader::Base::addModelBuffer(std::shared_ptr<model::Base> m)
{
    _modelBuffer.push_back(m);
}

void shader::Base::drawBuffer()
{
    GLuint uniformLocation;
    use();
    for(std::shared_ptr<model::Base> m : _modelBuffer)
    {
        uniformLocation = glGetUniformLocation( id(), U_names[U_meshColor]);
        if ( uniformLocation >= 0 )
        {
            glUniform3fv( uniformLocation, 1, glm::value_ptr( m->color() ) );
        }
        uniformLocation = glGetUniformLocation(id(), U_names[U_meshMat]);
        if ( uniformLocation >= 0 )
        {
            glUniformMatrix4fv( uniformLocation, 1, GL_FALSE, glm::value_ptr( m->matrix() ) );
        }
        m->draw();
        m->draw_points();
    }
}

void shader::Base::clearBuffer()
{
    _modelBuffer.clear();
}
