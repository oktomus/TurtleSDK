
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

world::World globalWorld;
GLFWwindow* window;
std::vector<shader::Base> materials;
std::vector<std::shared_ptr<model::Base>> models;
bool show_another_window = false;

/**
  * Initialize anything required to run Turtle
  */
void init();

/**
  * Init the scene materials
  */
void initMaterials();

/**
  * Init the scene objects
  */
void initObjects();

/**
  * Terminate the current project
  */
void terminate();

/**
  * Display a frame
  */
void display();

/**
  * Process glfw input
  *
  * @param window   The window which received the input
  */
void processInput(GLFWwindow *window);

/**
  * Window resize callback
  *
  * @param window       The window
  * @param width        The new width
  * @param height       The new height
  */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/**
  * Catch glfw errors
  *
  * @param error    Error code
  * @param description  Error message
  */
static void error_callback(int error, const char* description);

void init()
{
    fprintf(stdout, "Initializing...\n");

    {
        fprintf(stdout, "GLFW...");
        glfwSetErrorCallback(error_callback);
        if (!glfwInit())
        {
            fprintf(stderr, "Unable to init GLFW.\n");
            exit(3);
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(
                1280, 720, "TurtleSDK", NULL, NULL);

        if (!window)
        {
            fprintf(stderr, "Unable to create a window.\n");
            exit(2);
        }
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "GL3W...");

        if (gl3wInit()) {
            fprintf(stderr, "failed to initialize GL3W.\n");
            exit(4);
        }

        printf("OpenGL %s, GLSL %s...", glGetString(GL_VERSION),
                glGetString(GL_SHADING_LANGUAGE_VERSION));
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "IMGUI...");
        ImGui_ImplGlfwGL3_Init(window, true);
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "VIEWPORT...");
        glViewport(0, 0, 1280, 720);
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "CALLBACKS...");
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "WORLD...");
        globalWorld.init();
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "SHADERS...");
        initMaterials();
        fprintf(stdout, "OK\n");
    }
    {
        fprintf(stdout, "OBJECTS...");
        initObjects();
        fprintf(stdout, "OK\n");
    }


    fprintf(stdout, "Init OK\n");
}

void initMaterials()
{


    materials.push_back(shader::Base("shaders/animated"));
    materials.push_back(shader::Base("shaders/solid"));
    materials.at(0).setCamera(globalWorld.currentCamera());
    materials.at(1).setCamera(globalWorld.currentCamera());

}

void initObjects()
{
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
}


/******************************************************************************
 * Finalize all
 ******************************************************************************/
void terminate()
{
    fprintf(stdout, "Terminate...\n");

    {
        fprintf(stdout, "IMGUI...");
        ImGui_ImplGlfwGL3_Shutdown();
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "GLFW...");
        glfwTerminate();
        fprintf(stdout, "OK\n");
    }

    fprintf(stdout, "Terminate OK\n");
}

void display()
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

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main( int argc, char** argv )
{

    // Initialize all your resources (graphics, data, etc...)
    init();

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        ImGui_ImplGlfwGL3_NewFrame();
        display();
        ImGui::Render();
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    terminate();

}
