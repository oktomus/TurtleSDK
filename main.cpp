
/******************************************************************************
 ******************************* INCLUDE SECTION ******************************
 ******************************************************************************/


//#include <imgui.h>
// STL
#include <iostream>
#include <vector>
#include <fstream>
#include <memory>
#include <functional>

// System
#include <cstdio>


#include <imgui.h>
#include "imgui_impl_glfw_gl3.h"
// Graphics
// - GLEW (always before "gl.h")
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
// - GL
#ifdef _WIN32
#include <windows.h>
#endif

// glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Custom
#include "model/primitive.h"
#include "world.h"
#include "shader/baseShader.h"

/******************************************************************************
 ****************************** NAMESPACE SECTION *****************************
 ******************************************************************************/

/******************************************************************************
 ************************* DEFINE AND CONSTANT SECTION ************************
 ******************************************************************************/


world::World globalWorld;

GLFWwindow* window;
// Shader program
std::vector<shader::Base> materials;

std::vector<std::shared_ptr<model::Base>> models;

bool show_another_window = false;

/******************************************************************************
 ***************************** TYPE DEFINITION ********************************
 ******************************************************************************/

/******************************************************************************
 ***************************** METHOD DEFINITION ******************************
 ******************************************************************************/

/******************************************************************************
 ***************************** METHOD DEFINITION ******************************
 ******************************************************************************/

bool initialize();
bool checkExtensions();
bool initializeShaderProgram();
bool finalize();

/******************************************************************************
 * Initialize all
 ******************************************************************************/
bool initialize()
{
    std::cout << "Initialize all..." << std::endl;
    std::cout << "Initializing world object..\n";
    globalWorld.init();

    bool statusOK = true;

    if ( statusOK )
    {
        statusOK = checkExtensions();
    }

    if ( statusOK )
    {
        statusOK = initializeShaderProgram();
    }

    models.push_back(std::make_shared<model::Triangle>(
                -.3f, -.3f, 0.f, 
                .3f, -.3f, 0.f, 
                .15f, .15f, 0.f
                ));
    models.at(0)->setColor(1.f, 0.1f, 0.1f);

    models.push_back(std::make_shared<model::Triangle>(
                .5f, -.3f, 0.f, 
                .9f, .0f, 0.f, 
                .7f, .3f, 0.f
                ));

    models.at(1)->setColor(0.1f, 1.f, 0.1f);

    models.push_back(std::make_shared<model::Quad>(
                -.5f, -.5f, 0.f,
                .5f, -.5f, 0.f,
                .5f, .5f, 0.f,
                -.5f, .5f, 0.f
                ));
    models.at(2)->setColor(1.f, 1.f, 1.f);
    /*

    models.push_back(std::make_shared<model::Cube>(0.f, 0.f, 0.f, .4f));
    models.at(3)->setColor(0.1f, 1.f, 1.f);

    models.push_back(std::make_shared<model::Cube>(0.f, 0.f, -1.6f, .8f));
    models.at(3)->setColor(0.1f, .1f, .5f);
    */

    return statusOK;
}

/******************************************************************************
 * Finalize all
 ******************************************************************************/
bool finalize()
{
    bool statusOK = true;

    std::cout << "Finalize all..." << std::endl;

    return statusOK;
}

/******************************************************************************
 * Check GL extensions
 ******************************************************************************/
bool checkExtensions()
{
    bool statusOK = true;

    std::cout << "Check GL extensions..." << std::endl;

    return statusOK;
}

/******************************************************************************
 * Initialize shader program
 ******************************************************************************/
bool initializeShaderProgram()
{

    bool statusOK = true;

    std::cout << "Initialize shader program...\n" << std::endl;

    materials.push_back(shader::Base("shaders/animated"));
    materials.at(0).setCamera(globalWorld.currentCamera());
    std::cout << "End Initialize shader program.\n" << std::endl;

    return statusOK;
}

/******************************************************************************
 * Callback to display the scene
 ******************************************************************************/
void display( void )
{


    {
        ImGui::Begin("Another Window", &show_another_window);
        ImGui::Text("Hello from another window!");
        ImGui::End();
    }
    //ImGui::Text("Hello, world!");

    //--------------------
    // START frame
    //--------------------
    // Clear the color buffer (of the main framebuffer)
    // - color used to clear
    glClearColor( 0.f, 0.f, 0.f, 0.f );
    glClearDepth( 1.f );
    // - clear the "color" framebuffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    //glEnable(GL_BLEND);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    GLint uniformLocation;

    //--------------------
    // Activate shader program
    //--------------------
    shader::Base& mat = materials.at(0);
    for (std::shared_ptr<model::Base> mod: models)
    {
        mat.addModelBuffer(mod);
    }
    mat.use();

    //--------------------
    // Send uniforms to GPU
    //--------------------

    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    mat.drawBuffer();


    // Deactivate current shader program
    glUseProgram( 0 );

    //--------------------
    // END frame
    //--------------------
    // OpenGL commands are not synchrone, but asynchrone (stored in a "command buffer")
    glFlush();
    // Swap buffers for "double buffering" display mode (=> swap "back" and "front" framebuffers)

}

/******************************************************************************
 * Callback continuously called when events are not being received
 ******************************************************************************/
void idle( void )
{
    // Mark current window as needing to be redisplayed
}

/**
  * Process key input
  *
  * @param window   The window which received the input
  */
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/**
  * Window resize callback
  *
  * @param window       The window
  * @param width        The new width
  * @param height       The new height
  */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

/**
  * Catch glfw errors
  *
  * @param error    Error code
  * @param description  Error message
  */
static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

/******************************************************************************
 * Main function
 ******************************************************************************/
int main( int argc, char** argv )
{
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(
            1280, 720, "TurtleSDK", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    if (gl3wInit()) {
        fprintf(stderr, "failed to initialize OpenGL\n");
        return -1;
    }

    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
            glGetString(GL_SHADING_LANGUAGE_VERSION));


    ImGui_ImplGlfwGL3_Init(window, true);
    glViewport(0, 0, 1280, 720);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    // Initialize all your resources (graphics, data, etc...)
    initialize();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        ImGui_ImplGlfwGL3_NewFrame();
        display();

        ImGui::Render();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Grahics window
    // - configure the main framebuffer to store rgba colors,
    //   and activate double buffering (for fluid/smooth visualization)
    //glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE );

    // Callbacks
    // - callback called when displaying window (user custom fonction pointer: "void f( void )")
    //glutDisplayFunc( display );
    // - callback continuously called when events are not being received
    //glutIdleFunc( idle );


    // Enter the GLUT main event loop (waiting for events: keyboard, mouse, refresh screen, etc...)
    //    glutMainLoop();

    // Clean all

    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();
    //finalize();
}
