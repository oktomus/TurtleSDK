#ifndef __TURTLE_FPS_CAMERA__
#define __TURTLE_FPS_CAMERA__

#include "camera.h"

/**
  * @brief Camera used to navigate in a scene
  */
class FPSCamera : public Camera
{

public:

    glm::vec3 camFront;
    glm::vec3 camUp;

    /**
      * @brief Create a default fps camera
      */
    FPSCamera();

    /**
      * @brief Reset the camera values
      */
    void reset();

    void process_mouse_move(GLFWwindow* window, double xpos, double ypos);
    void process_scroll(GLFWwindow* window, double xoffset, double yoffset);
    void process_key(GLFWwindow*, int, int, int, int);

    glm::mat4 view() const;
    glm::vec3 up() const;

private:

    glm::vec3 _initialFront = {0, 0, -1};
    glm::vec3 _initialUp = {0, 1, 0};


};

#endif
