#ifndef __BASE_SHADER_
#define __BASE_SHADER_

#include <string>
#include <map>

#include <GL/glew.h>
#include <GL/gl.h>
#include "camera/baseCamera.h"


#define U_viewMat "viewMatrix"
#define U_projMat "projectionMatrix"

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

        void setCamera(const camera::Camera& cam);

    private:

        GLuint programId;
        GLuint vertexId;
        GLuint fragId;

        std::map<std::string, GLuint> _uniformsLocation;

        const camera::Camera* _cam;

    };

}

#endif
