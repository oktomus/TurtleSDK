#ifndef __TURTLE_TOP__
#define __TURTLE_TOP__


#include <imgui.h>
#include "imgui_impl_glfw_gl3.h"
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>


#include <vector>
#include <map>
#include <string>
#include <memory>

#include "shader.h"
#include "model.h"
#include "object.h"
#include "terrain.h"
#include "camera.h"
#include "light.h"
#include "skybox.h"

/**
 * @brief Unique instance of the main turtle application.
 * Group everything required to make turtle work.
 */
class Turtle
{

public:

    /**
     * @brief Return the instance of the application
     * Create a new one if there isn't any
     * @return
     */
    static Turtle &getInstance();

    /**
      * @biref Returns the delta time of the current frame
      */
    float getDeltaTime() const;

    int getWinHeight() const;

    int getWinWidth() const;

    /**
     * @brief Init the application
     * Should be called only once
     */
    void init();

    /**
     * @brief Correctly terminate the application compounds.
     * Should be called only once
     */
    void terminate();

    /**
     * @brief Start the main loop which will draw frames
     */
    void mainLoop();

    /**
     * @brief Display of frame
     */
    void displayFrame();

    /**
     * @brief Display world lights
     */
    void displayLights();

    /**
     * @brief Display the ui.
     * Called before each frame contents
     */
    void displayUi();

private:

    /**
     * @brief Called only once when turtle.h is included.
     * Does nothing.
     */
    Turtle();

    /**
     * @brief Forbiden
     */
    Turtle(const Turtle &) = delete;

    /**
     * @brief Handle glfw errors
     * @param error             code
     * @param description       message
     */
    static void errorCallback(int error, const char* description)
    {
        fprintf(stderr, "GLFW Error %d: %s\n", error, description);
    }

    /**
     * @brief Handle windwo resize
     */
    static void framebufferSizeCallback(GLFWwindow*, int, int);

    /**
     * @brief Handle scroll events
     * @param Window
     * @param X offset
     * @param Y offset
     */
    static void scrollCallback(GLFWwindow*, double, double);

    /**
     * @brief Process inputs on each frame
     */
    void processInput(GLFWwindow *);

    /**
     * @brief Handle keyboarde events
     */
    static void keyCallback(GLFWwindow*, int, int, int, int);

    /**
     * @brief Handle text typing events
     */
    static void charCallback(GLFWwindow*, unsigned int);

    /**
     * @brief Handle mouse moves events
     */
    static void mouseCallback(GLFWwindow*, double, double);

    /**
     * @brief Handle mouse buttons events
     */
    static void mouseButtonCallback(GLFWwindow*, int, int, int);

    /**
     * @brief The application's instance
     */
    static Turtle instance_;

    /**
     * @brief Camera of the scene
     */
    std::unique_ptr<Camera> cam_;

    /**
     * @brief Shader of the scene
     */
    std::map<std::string, std::shared_ptr<Shader>> shaders_;

    /**
     * @brief Models of the scene
     */
    std::vector<std::shared_ptr<Model>> models_;

    /**
      * @brief Objects of the scene
      */
    std::vector<Object> objects_;

    /**
      * @brief Ground of the world
      */
    std::shared_ptr<Terrain> ground_;

    /**
      * @brief Model used to display lights in the viewport
      */
    Object lightDisplay_;

    /**
     * @brief Directionnal lights of the scene
     */
    std::vector<DirectionLight> dirLights_;

    /**
     * @brief Point lights of the scene
     */
    std::vector<PointLight> pointLights_;

    /**
     * @brief Spot lights of the scene
     */
    std::vector<SpotLight> spotLights_;

    std::shared_ptr<SkyBox> skybox_;

    /**
     * @brief Clear color
     */
    glm::vec4 clearColor_ = glm::vec4(0.1, 0.1, 0.1, 0);

    /**
     * @brief Time spent between current and last frame
     */
    float deltaTime_ = 0.0f;

    /**
     * @brief Time of the current frame
     */
    float currentTime_ = 0.0f;

    /**
     * @brief Current frame rate
     */
    float frameRate_ = 0.0;

    /**
     * @brief Enable or disable user inputs on the viewport
     */
    bool disableViewportEvents_ = false;

    /**
     * @brief Draw line if true, else draw faces
     */
    bool drawLine_ = false;

    /**
     * @brief Draw lights in the viewport if true
     */
    bool drawLights_ = true;

    /**
     * @brief Width of the window
     */
    int winWidth_ = 1280;

    /**
 * @brief Height of the window
     */
    int winHeight_ = 720;

    /**
     * @brief The application's window
     */
    GLFWwindow* window_ = nullptr;

    // Imgui related

    bool debug_window_ = true;
    bool scene_window = true;

};

#endif
