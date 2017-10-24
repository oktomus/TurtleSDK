#ifndef __BASE_SHADER_
#define __BASE_SHADER_

#include <string>

#include <GL/glew.h>
#include <GL/gl.h>
#include "world.h"

/*
        █                 █               
  ▄▄▄   █ ▄▄    ▄▄▄    ▄▄▄█   ▄▄▄    ▄ ▄▄ 
 █   ▀  █▀  █  ▀   █  █▀ ▀█  █▀  █   █▀  ▀
  ▀▀▀▄  █   █  ▄▀▀▀█  █   █  █▀▀▀▀   █    
 ▀▄▄▄▀  █   █  ▀▄▄▀█  ▀█▄██  ▀█▄▄▀   █    

 */

namespace shader{


    const std::string readFile(const std::string & path);
    GLuint compileShader(
            const std::string & sourcePath,
            const GLenum & shaderType);

    class Base
    {

    public:

        Base(const std::string& path);

        void use() const;
        const GLuint & id() const;

    private:

        GLuint programId;
        GLuint vertexId;
        GLuint fragId;

    };

}

#endif
