#ifndef __TURTLE_ORBIT_CAMERA__
#define __TURTLE_ORBIT_CAMERA__

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

// Graphics
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

/**
  * @brief Camera used to rotate around a round-shaped object.
  */
class OrbitCamera
{

public:

    glm::vec3 pos;

    glm::vec3 target;

    /**
      * @brief Create a camera with a given position and target
      *
      * @param initialPos       Initial position, can be reset
      * @param initialTarget    Initial target, can be reset
      */
    OrbitCamera(const glm::vec3& initialPos,
                const glm::vec3& initialTarget);

    /**
      * @brief Reset the camera target and position
      */
    void reset();

    void process_mouse_move(GLFWwindow* window, double xpos, double ypos);
    void process_mouse_action(GLFWwindow* window, int button, int action, int mods);
    void process_scroll(GLFWwindow* window, double xoffset, double yoffset);

    glm::mat4 viewMat() const;
    glm::vec3 up() const;

private:

    glm::vec3 _initialPos;
    glm::vec3 _initialTarget;

    // Used to process uer input
    float _lastPosX, _lastPosY;
    bool _firstMove;
    bool _mouseRotateCamera;

};

#endif
