#ifndef __BASE_CAMERA__
#define __BASE_CAMERA__

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*

  ▄▄▄    ▄▄▄   ▄▄▄▄▄   ▄▄▄    ▄ ▄▄   ▄▄▄  
 █▀  ▀  ▀   █  █ █ █  █▀  █   █▀  ▀ ▀   █ 
 █      ▄▀▀▀█  █ █ █  █▀▀▀▀   █     ▄▀▀▀█ 
 ▀█▄▄▀  ▀▄▄▀█  █ █ █  ▀█▄▄▀   █     ▀▄▄▀█ 

*/

namespace camera {

    class Camera{

    public:

        Camera();

        const glm::mat4& viewMatrix() const
        {
            return _viewMatrix;
        }

        const glm::mat4& projectionMatrix() const
        {
            return _projectionMatrix;
        }

    private:

        // - view
        glm::vec3 _cameraEye;
        glm::vec3 _cameraCenter;
        glm::vec3 _cameraUp;

        // - projection
        float _cameraFovY;
        float _cameraAspect;
        float _cameraZNear;
        float _cameraZFar;

        glm::mat4 _viewMatrix;
        glm::mat4 _projectionMatrix;
    };
}

#endif
