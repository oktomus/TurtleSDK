#include "fpsCamera.h"
#include "turtle.h"

FPSCamera::FPSCamera() : Camera()
{
    pos = _initialPos = {0, 3, 3};
    camFront = _initialFront;
    camUp = _initialUp;
    fov = 45.0f;
}

void FPSCamera::reset()
{
    pos = _initialPos;
    camUp = _initialUp;
    camFront = _initialFront;
    fov = 45.0f;
}

void FPSCamera::process_mouse_move(GLFWwindow* window, double xpos, double ypos)
{
    static float yaw = -90.f, pitch = 0.f;
    if (_firstMove)
    {
        _lastPosX = xpos;
        _lastPosY = ypos;
        _firstMove = false;
    }
    float difx = xpos - _lastPosX;
    float dify = ypos - _lastPosY; // Y 0 top, 100 bottom -> reverse
    _lastPosX = xpos; _lastPosY = ypos;

    static float sensi = 0.2f;
    difx *= sensi;
    dify *= sensi;

    yaw += difx;
    pitch += dify;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.y = sin(glm::radians(pitch));
    front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    camFront = glm::normalize(front);
}


void FPSCamera::process_scroll(GLFWwindow* window, double xoffset, double yoffset)
{
    if(fov >= 1.0f && fov <= 75.0f)
        fov -= yoffset;
    if(fov <= 1.0f)
        fov = 1.0f;
    if(fov >= 75.0f)
        fov = 75.0f;
}

void FPSCamera::process_key(GLFWwindow* window, int key, int, int action, int moods)
{
    static float defaultSpeed = 5.5f;
    float cameraSpeed = defaultSpeed * Turtle::getInstance().getDeltaTime();

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) // Top
        pos += cameraSpeed * camFront;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) // Back
        pos -= cameraSpeed * camFront;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) // Left
        pos -= glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) // Right
        pos += glm::normalize(glm::cross(camFront, camUp)) * cameraSpeed;
}


glm::mat4 FPSCamera::view() const
{
    return glm::lookAt(pos, pos + camFront, camUp);
}

glm::vec3 FPSCamera::up() const
{
    return camUp;
}
