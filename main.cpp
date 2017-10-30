
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

// Graphics
// - GLEW (always before "gl.h")
#include <GL/glew.h>
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

    glColor4f( 1.f, 0.f, 0.f, 1.f );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    //mat.drawBuffer();
    glBegin(GL_POINTS);
    glVertex3f(-.5f, -.5f, 0.f);
    glVertex3f(.5f, -.5f, 0.f);
    glVertex3f(.5f, .5f, 0.f);
    glVertex3f(-.5f, .5f, 0.f);
    glEnd();


    // Deactivate current shader program
    glUseProgram( 0 );

    //--------------------
    // END frame
    //--------------------
    // OpenGL commands are not synchrone, but asynchrone (stored in a "command buffer")
    glFlush();
    // Swap buffers for "double buffering" display mode (=> swap "back" and "front" framebuffers)
    glfwSwapBuffers(window);
    glfwPollEvents();
}

/******************************************************************************
 * Callback continuously called when events are not being received
 ******************************************************************************/
void idle( void )
{
    // Mark current window as needing to be redisplayed
}

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

    GLenum error = glewInit();
    if ( error != GLEW_OK )
    {
        fprintf( stderr, "Error: %s\n", glewGetErrorString( error ) );
        exit( -1 );
    }

    // Initialize all your resources (graphics, data, etc...)
    initialize();

    while (!glfwWindowShouldClose(window))
    {

        display();
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

    glfwTerminate();
    //finalize();
}
