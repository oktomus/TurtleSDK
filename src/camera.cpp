#include "camera.h"
#include "turtle.h"

void Camera::process_mouse_move(GLFWwindow* window, double xpos, double ypos)
{
}

void Camera::process_mouse_action(GLFWwindow* window, int button, int action, int mods)
{
}

void Camera::process_scroll(GLFWwindow* window, double xoffset, double yoffset)
{
}

void Camera::process_key(GLFWwindow*, int, int, int, int)
{
}

glm::mat4 Camera::projection() const
{
    return glm::perspective(glm::radians(fov), 
            (float) Turtle::getInstance().getWinWidth() / 
            (float) Turtle::getInstance().getWinHeight(), 
            0.1f, 1000.0f);  
}
