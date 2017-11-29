#ifndef __TURTLE_ORBIT_CAMERA__
#define __TURTLE_ORBIT_CAMERA__

#include "camera.h"

/**
  * @brief Camera used to rotate around a round-shaped object.
  */
class OrbitCamera : public Camera
{

public:

    glm::vec3 target;

    /**
      * @brief Create a camera with a default position and target
      */
    OrbitCamera();

    /**
      * @brief Reset the camera target and position
      */
    void reset();

    void process_mouse_move(GLFWwindow* window, double xpos, double ypos);
    void process_mouse_action(GLFWwindow* window, int button, int action, int mods);
    void process_scroll(GLFWwindow* window, double xoffset, double yoffset);

    glm::mat4 view() const;
    glm::vec3 up() const;

private:

    glm::vec3 _initialTarget;

    bool _mouseRotateCamera;
};

#endif
