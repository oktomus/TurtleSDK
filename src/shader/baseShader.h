#ifndef __BASE_SHADER_
#define __BASE_SHADER_

#include <string>

#include <GL/glew.h>
#include <GL/gl.h>

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

}

#endif
