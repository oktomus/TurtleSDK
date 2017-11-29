#ifndef __TURTLE_CAMERA__
#define __TURTLE_CAMERA__

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

// Graphics
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

/**
  * @brief Camera used to navigate in a scene
  */
class Camera
{

public:

    glm::vec3 pos;

    float fov = 0;

    /**
      * @brief Reset the camera values
      */
    virtual void reset() = 0;

    virtual void process_mouse_move(GLFWwindow* window, double xpos, double ypos);
    virtual void process_mouse_action(GLFWwindow* window, int button, int action, int mods);
    virtual void process_scroll(GLFWwindow* window, double xoffset, double yoffset);
    virtual void process_key(GLFWwindow*, int, int, int, int);

    virtual glm::mat4 view() const = 0;
    virtual glm::mat4 projection() const;
    virtual glm::vec3 up() const = 0;

protected:

    glm::vec3 _initialPos = {0, 0, 3};

    // Used to process uer input
    float _lastPosX, _lastPosY;
    bool _firstMove = true;
};

#endif
