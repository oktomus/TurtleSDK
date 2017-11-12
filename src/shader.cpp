#include "shader.h"

#include <fstream>

Shader::Shader(const std::string &vertSrcPath, const std::string &fragSrcPath, const std::string &geoSrcPath)
{

    GLuint geoId;
    GLuint vertId = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertSrcPath, vertId, "VERTEX");
    GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragSrcPath, fragId, "FRAGMENT");
    if (geoSrcPath.size())
    {
        geoId = glCreateShader(GL_GEOMETRY_SHADER);
        compileShader(geoSrcPath, geoId, "GEOMETRY");
    }

    _id = glCreateProgram();
    glAttachShader(_id, vertId);
    glAttachShader(_id, fragId);
    if (geoSrcPath.size())
        glAttachShader(_id, geoId);
    glLinkProgram(_id);
    checkCompileState(_id, "PROGRAM");
    glDeleteShader(vertId);
    glDeleteShader(fragId);
    if (geoSrcPath.size())
        glDeleteShader(geoId);
}

Shader::Shader(std::string path, const bool &useGeo) :
    Shader(path + ".vert", path + ".frag", (useGeo) ? path + ".geo" : "")
{
}

void Shader::use() const
{
   glUseProgram(_id);
}

std::string Shader::readFile(const std::string & path)
{
    std::ifstream txtFile(path);

    if (!txtFile.is_open())
    {
        fprintf(stderr, "ERROR::SHADER::FILE: Cannot read file %s\n", path);
        return "";
    }

    std::string txtContent(
            (std::istreambuf_iterator<char>(txtFile)),
            (std::istreambuf_iterator<char>())
            );

    txtFile.close();
    return txtContent;
}

void Shader::compileShader(
        const std::string & sourcePath,
        const GLuint & shaderId,
        const std::string& type)
{

    if (shaderId == 0)
    {
        fprintf(stderr, "ERROR::SHADER::ID: Can't compile the shader. It \
                hasn't been created correctly\n");
        return;
    }


    // Fetch the source

    const std::string source = readFile(sourcePath);
    const char* sourceChar = source.c_str();

    // Load the source
    glShaderSource( shaderId, 1, &sourceChar, nullptr );

    // Compile the source
    glCompileShader( shaderId );

    checkCompileState(shaderId, type);
}

void Shader::checkCompileState(const GLuint &id, const std::string &type)
{
    GLint code;

    bool shader = type != "PROGRAM";

    if(shader)
        glGetShaderiv(id, GL_COMPILE_STATUS, &code);
    else
        glGetProgramiv(id, GL_COMPILE_STATUS, &code);

    if(!code)
    {
        GLint logLength = 0;
        if (shader)
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
        else
            glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);

        std::string message;
        if (shader) message = "ERROR::SHADER_COMPILATION::" + type;
        else message = "ERROR::PROGRAM_LINK::" + type;

        if (logLength)
        {
            GLchar* log = new GLchar[logLength];
            GLsizei length = 0;
            if (shader) glGetShaderInfoLog(id, logLength, &length, log);
            else        glGetProgramInfoLog(id, logLength, &length, log);
            message += "\n";
            message += log;
            delete[] log;
        }
        fprintf(stderr, "%s\n", message.c_str());
    }

}
