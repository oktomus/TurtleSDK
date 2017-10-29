#ifndef __BASE_SHADER_
#define __BASE_SHADER_

#include <string>
#include <map>
#include <memory>
#include "model/baseModel.h"

#include <GL/glew.h>
#include <GL/gl.h>
#include "camera/baseCamera.h"


#define U_count 5
#define U_viewMat 0
#define U_projMat 1
#define U_meshColor 2
#define U_meshMat 3
#define U_time 4

/*
        █                 █               
  ▄▄▄   █ ▄▄    ▄▄▄    ▄▄▄█   ▄▄▄    ▄ ▄▄ 
 █   ▀  █▀  █  ▀   █  █▀ ▀█  █▀  █   █▀  ▀
  ▀▀▀▄  █   █  ▄▀▀▀█  █   █  █▀▀▀▀   █    
 ▀▄▄▄▀  █   █  ▀▄▄▀█  ▀█▄██  ▀█▄▄▀   █    

 */

namespace shader{

    const std::array<const GLchar *, U_count> U_names = {
        "viewMatrix",
        "projectionMatrix",
        "meshColor",
        "modelMatrix",
        "time",
    };

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
        void updateUniforms();
        void addModelBuffer(std::shared_ptr<model::Base> m);
        void drawBuffer();
        void clearBuffer();

    private:

        GLuint programId;
        GLuint vertexId;
        GLuint fragId;

        std::map<int8_t, GLuint> _uniformsLocation;
        std::vector<std::shared_ptr<model::Base>> _modelBuffer;

        const camera::Camera* _cam;


    };

}

#endif
