#include "baseCamera.h"

/*

  ▄▄▄    ▄▄▄   ▄▄▄▄▄   ▄▄▄    ▄ ▄▄   ▄▄▄  
 █▀  ▀  ▀   █  █ █ █  █▀  █   █▀  ▀ ▀   █ 
 █      ▄▀▀▀█  █ █ █  █▀▀▀▀   █     ▄▀▀▀█ 
 ▀█▄▄▀  ▀▄▄▀█  █ █ █  ▀█▄▄▀   █     ▀▄▄▀█ 

*/

camera::Camera::Camera(){
    _cameraEye = glm::vec3( 0.f, 2.f, 3.f );
    _cameraCenter = glm::vec3( 0.f, 0.f, 0.f );
    _cameraUp = glm::vec3( 0.f, 1.f, 0.f );

    _cameraFovY = 45.f;
    _cameraAspect = 1.f;
    _cameraZNear = 0.1f;
    _cameraZFar = 100.f;

    _viewMatrix = glm::lookAt( _cameraEye, _cameraCenter, _cameraUp );
    _projectionMatrix = glm::perspective( _cameraFovY, _cameraAspect, _cameraZNear, _cameraZFar );
}
