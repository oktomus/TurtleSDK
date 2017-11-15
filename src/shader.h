#ifndef __TURTLE_SHADER__
#define __TURTLE_SHADER__

// STD
#include <string>

// Graphic
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

// Math
#include <glm/glm.hpp>

class Shader
{

public:

    /**
     * @brief Create and compile a shader
     * @param vertSrcPath       Path to the vertex shader source
     * @param fragSrcPath       Path to the fragment shader soruce
     * @param geoSrcPath        Path to the geometry shader source (default=null)
     */
    Shader(const std::string& vertSrcPath,
           const std::string& fragSrcPath,
           const std::string& geoSrcPath = "");

    /**
     * @brief Create and compile a shader with sources using same name but
     * different extension.
     * @param path      Path to the source without extension
     * @param useGeo    If true, use the geo shader
     */
    explicit Shader(std::string path,
           const bool& useGeo = false);

    /**
     * @brief Use the shader with glUseProgram.
     */
    void use() const;

    /////
    ///// Unifrom setters
    /////

    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value);
    }

    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
    }

    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(_id, name.c_str()), x, y);
    }

    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(_id, name.c_str()), x, y, z);
    }

    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(_id, name.c_str()), 1, &value[0]);
    }

    void setVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(_id, name.c_str()), x, y, z, w);
    }

    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:

    /**
     * @brief Id of the program
     */
    GLuint _id;

    /**
     * @brief Read a file's content
     * @param path      Path to the file
     * @return The file content's
     */
    static std::string readFile(const std::string & path);

    /**
     * @brief Compile a shader
     * @param sourcePath        Path to the shader source
     * @param shaderId          Generated id for the shader
     * @param type              Type of the shader
     */
    static void compileShader(const std::string & sourcePath,
                                      const GLuint & shaderId,
                                      const std::string& type);

    /**
     * @brief Check if the given shader/program has correclty been compiled/linked
     * @param id        Id of the shader/program
     * @param type      Type of the shader/program
     */
    static void checkCompileState(const GLuint& id, const std::string& type);

};

#endif
