
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
#include <glm/gtx/rotate_vector.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Custom
#include "mesh.h"
#include "model.h"
#include "shader.h"

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

int WIN_WIDTH = 1280;
int WIN_HEIGHT = 720;

// last positions of the mouse
float lastPosX, lastPosY;
bool firstMouve = true;
bool mouseRotateCamera = false;


// Camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

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
  * Process mouse events
  */
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

/**
  * Process scroll events
  *
  */
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

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
                WIN_WIDTH, WIN_HEIGHT, "TurtleSDK", NULL, NULL);

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
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);
        glfwSetMouseButtonCallback(window, mouse_button_callback);
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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
        // fase means: don't register imgui callbacks
        // May cause troubles for text inputs
        // Needs to be tested
        ImGui_ImplGlfwGL3_Init(window, false);
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "VIEWPORT...");
        glViewport(0, 0, 1280, 720);
        fprintf(stdout, "OK\n");
    }


    {
        fprintf(stdout, "WORLD...");
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
    models.push_back(Model("turtleLib/models/broccoli.obj"));
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
        ImGui::Text("Camera Pos (%f, %f, %f)", cameraPos.x, cameraPos.y, cameraPos.z);
        if (ImGui::Button("Quit"))
            glfwSetWindowShouldClose(window, true);
        if (ImGui::Button("Reset Camera"))
        {
            cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
            cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
            cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
        }

        
        ImGui::End();
    }

    // STATE ASSIGN
    {
        glClearColor( 0.f, 0.f, 0.f, 0.0f );
        glClearDepth( 1.0 );
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        //glPolygonMode( GL_FRONT, GL_FILL );
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }

    // STATE ACT
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }


    // DRAW
    {

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 model;
        shaders.back().setMat4("projection", projection);
        shaders.back().setMat4("model", model);
        glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);
        shaders.back().use();
        shaders.back().setMat4("view", view);
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

    /*
    float cameraSpeed = 2.5 * deltaTime; 

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraUp;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        */
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouve)
    {
        lastPosX = xpos;
        lastPosY = ypos;
        firstMouve = false;
    }
    float difx = xpos - lastPosX;
    float dify = ypos - lastPosY; // Y 0 top, 100 bottom -> reverse
    lastPosX = xpos; lastPosY = ypos;

    if(mouseRotateCamera){
        // Rotate
        cameraPos = glm::rotate(cameraPos, difx * 0.01f, glm::vec3(0, 1, 0));
        cameraPos = glm::rotate(cameraPos, dify * 0.01f, glm::vec3(1, 0, 0));
        // Calcule front
        glm::vec3 cameraTarget(0, 0, 0);
        cameraFront = glm::normalize(cameraPos - cameraTarget);
        // Calcule up
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraFront));
        cameraUp = glm::cross(cameraFront, cameraRight);
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        mouseRotateCamera = true;
    else
        mouseRotateCamera = false;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * float(yoffset);
    if (cameraPos.z <= 0.5f)
        cameraPos.z = 0.5f;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    WIN_WIDTH = width;
    WIN_HEIGHT = height;
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

        processInput(window);
        ImGui_ImplGlfwGL3_NewFrame();

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
