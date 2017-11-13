#include "orbitCamera.h"

OrbitCamera::OrbitCamera(const glm::vec3& initialPos,
        const glm::vec3& initialTarget) :
    _initialPos(initialPos),
    _initialTarget(initialTarget),
    pos(initialPos),
    target(initialTarget),
    _firstMove(true),
    _mouseRotateCamera(false)
{

}

void OrbitCamera::reset()
{
    pos = _initialPos;
    target = _initialTarget;
}

void OrbitCamera::process_mouse_move(GLFWwindow* window, double xpos, double ypos)
{
    if (_firstMove)
    {
        _lastPosX = xpos;
        _lastPosY = ypos;
        _firstMove = false;
    }
    float difx = xpos - _lastPosX;
    float dify = ypos - _lastPosY; // Y 0 top, 100 bottom -> reverse
    _lastPosX = xpos; _lastPosY = ypos;

    if(_mouseRotateCamera){
        // Rotate
        pos = glm::rotate(pos, difx * 0.01f, glm::vec3(0, 1, 0));
        pos = glm::rotate(pos, dify * 0.01f, glm::vec3(1, 0, 0));
    }

}

void OrbitCamera::process_mouse_action(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        _mouseRotateCamera = true;
    else
        _mouseRotateCamera = false;
}

void OrbitCamera::process_scroll(GLFWwindow* window, double xoffset, double yoffset)
{
    glm::vec3 cameraDirection = glm::normalize(pos - target);
    pos -= cameraDirection * float(yoffset);
}

glm::mat4 OrbitCamera::viewMat() const
{
    glm::vec3 cameraDirection = glm::normalize(pos - target);
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
    glm::mat4 view = glm::lookAt(pos, cameraDirection, cameraUp);
    return view;
}
