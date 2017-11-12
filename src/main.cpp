
/******************************************************************************
 ******************************* INCLUDE SECTION ******************************
 ******************************************************************************/


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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Custom
#include "mesh.h"
#include "model.h"
#include "shader.h"
#include "world.h"

world::World globalWorld;
GLFWwindow* window;
std::vector<Mesh> meshes;
std::vector<Model> models;
std::vector<Shader> shaders;
bool show_another_window = false;
// Time spent between each frame
float deltaTime = 0.0f;
// Time of last frame
float lastFrame = 0.0f;
// Number of frames during the last second
size_t frames = 0;
// Time it was when reseting frame counter
float startFramesTime = 0.0f;
// The time of the current frame
float currentTime;
// The current frame rate
float frameRate = 0.0;

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
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif
        window = glfwCreateWindow(
                1280, 720, "TurtleSDK", NULL, NULL);

        if (!window)
        {
            fprintf(stderr, "Unable to create a window.\n");
            exit(2);
        }
        glfwMakeContextCurrent(window);
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "CALLBACKS...");
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
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
    shaders.push_back(Shader("turtleLib/shaders/solid"));
}

void initObjects()
{
    /*
    // Doesnt work..
    meshes.push_back(Mesh::triangle({.5f, -.3f, 0.f,
                                     .9f, 0.f, 0.f,
                                     .7f, .3f, 0.f,
                                     .0f, 0.f, 0.f,
                                     .3f, .3f, 0.f,
                                     .0f, 6.f, 0.f,
                                    }));
    meshes.push_back(Mesh::triangle({.5f, -.3f, 0.f,

                                     .9f, 0.f, 0.f,
                                     .7f, .3f, 0.f
                                    }));
    meshes.back().setIndices({0, 1, 2});
    */
    //meshes.push_back(Mesh::quad());
    models.push_back(Model("/home/oktomus/Downloads/spinner.obj"));
    /*
        models.push_back(std::make_shared<model::EBOTriangle>(
                    -.3f, -.3f, 0.f,
                    .3f, -.3f, 0.f,
                    .15f, .15f, 0.f
                    ));
        models.at(0)->setColor(1.f, 0.1f, 0.1f);
        */

    /*
        models.push_back(std::make_shared<model::EBOTriangle>(
                    .5f, -.3f, 0.f,
                    .9f, .0f, 0.f,
                    .7f, .3f, 0.f
                    ));

        models.back()->setColor(0.1f, 1.f, 0.1f);
        materials.at(0)->addModelBuffer(models.back());
        */
        /*

        models.push_back(std::make_shared<model::Quad>(
                    -.5f, -.5f, 0.f,
                    .5f, -.5f, 0.f,
                    .5f, .5f, 0.f,
                    -.5f, .5f, 0.f
                    ));
        models.at(2)->setColor(1.f, 1.f, 1.f);

        models.push_back(std::make_shared<model::Cube>(0.f, 0.f, 0.f, .4f));
        models.back()->setColor(0.3f, 0.f, 0.3f);
        materials.at(0)->addModelBuffer(models.back());
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

    {
        fprintf(stdout, "MEMORY...");
        fprintf(stdout, "OK\n");
    }

    fprintf(stdout, "Terminate OK\n");
}

void display()
{
    // IMGUI
    {
        ImGui::Begin("Turtle Settings", &show_another_window);
        ImGui::Text("%f ms/frame, ~%d FPS", frameRate, (long)(1000 / frameRate));
        ImGui::End();
    }

    // STATE ASSIGN
    {
        glClearColor( 0.f, 0.f, 0.f, 0.0f );
        glClearDepth( 1.0 );
        glEnable(GL_BLEND);
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glPolygonMode( GL_FRONT, GL_FILL );
        //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }

    // STATE ACT
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }


    // DRAW
    {
        //materials.at(0)->drawBuffer();
        //materials.at(0)->drawBuffer();
        //materials.at(1)->use();
        //glUseProgram(materials.at(1)->id());
        //meshes.back().drawPoints(shaders.back());
        //meshes.back().draw(shaders.back());
        //glUseProgram(0);
        models.back().draw(shaders.back());
    }

    //globalWorld.moveCamera();


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

    try
    {
        init();
    }
    catch(const std::exception &e)
    {
        std::cout <<"\n\nInitialisation failed. Reason:\n" << e.what() << "\n\n";
        terminate();
        return 2;
    }

    while (!glfwWindowShouldClose(window))
    {
        frames += 1;
        currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
        if (currentTime - startFramesTime >= 1.0)
        {
            frameRate = 1000 / double(frames);
            frames = 0;
            startFramesTime += 1.0;
        }

        {
            processInput(window);
            ImGui_ImplGlfwGL3_NewFrame();
        }
        display();
        {
            glFlush();
            ImGui::Render();
            glfwPollEvents();
            glfwSwapBuffers(window);
        }
    }

    terminate();
    return 0;

}
