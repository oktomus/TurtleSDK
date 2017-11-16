
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
// Custom
#include "mesh.h"
#include "model.h"
#include "shader.h"
#include "orbitCamera.h"

GLFWwindow* window;
std::vector<Mesh> meshes;
std::vector<Model> models;
std::vector<Shader> shaders;

OrbitCamera ocam({0, 30, 30}, {0, 10, 0});
glm::vec3 lightPos(1.2f, 7.0f, 2.0f);

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

void key_callback(GLFWwindow*, int key, int, int action, int mods);
void char_callback(GLFWwindow*, unsigned int c);

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
        glfwSetKeyCallback(window, key_callback);
        glfwSetCharCallback(window, char_callback);
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
    shaders.push_back(Shader("turtleLib/shaders/material"));
    shaders.push_back(Shader("turtleLib/shaders/phong.vert",
                          "turtleLib/shaders/purewhite.frag", ""));
}

void initObjects()
{
    //models.push_back(Model("turtleLib/models/broccoli/broccoli2.obj"));
    models.push_back(Model("turtleLib/models/woodenCase/case.obj"));
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
        ImGui::Text("Camera Pos (%f, %f, %f)", ocam.pos.x, ocam.pos.y, ocam.pos.z);
        if (ImGui::Button("Quit"))
            glfwSetWindowShouldClose(window, true);
        if (ImGui::Button("Reset Camera"))
        {
            ocam.reset();
        }
        ImGui::InputFloat("Light X", &lightPos.x, 0.1f, 1.0f);
        ImGui::InputFloat("Light Y", &lightPos.y, 0.1f, 1.0f);
        ImGui::InputFloat("Light Z", &lightPos.z, 0.1f, 1.0f);

        
        ImGui::End();
    }

    // STATE ASSIGN
    {
        glClearColor( 0.f, 0.f, 0.f, 0.0f );
        glClearDepth( 1.0 );
        //glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
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

        Shader * modelShader = &(shaders[0]);
        Shader * lightShader = &(shaders[1]);
        Model * object = &(models[0]);
        Model * light = &(models[0]);

        // Camera thing
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);

        // Drawing model
        // Camera uniform
        modelShader->use();
        modelShader->setFloat("material.shininess", 32.0f);
        modelShader->setVec3("light.ambient", .1f, .1f, .1f);
        modelShader->setVec3("light.diffuse", .5f, 0.5f, 0.5f);
        modelShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        modelShader->setVec3("light.position", lightPos);
        modelShader->setMat4("view", ocam.viewMat());
        modelShader->setVec3("viewPos", ocam.pos);
        modelShader->setMat4("projection", projection);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model;
            model = glm::translate(model, glm::vec3( -15.0f + i * 3.0f, 0, 0));
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            modelShader->setMat4("model", model);
            object->draw(*modelShader);
        }

        // Drawing light
        glm::mat4 model = glm::translate(glm::mat4(), lightPos);
        model = glm::scale(model, glm::vec3(.2f));
        // Camera uniform
        lightShader->use();
        lightShader->setMat4("view", ocam.viewMat());
        lightShader->setMat4("projection", projection);
        lightShader->setMat4("model", model);
        light->draw(*lightShader);


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

void key_callback(GLFWwindow*, int key, int, int action, int mods)
{
    ImGui_ImplGlfwGL3_KeyCallback(0, key, 0, action, mods);
}

void char_callback(GLFWwindow*, unsigned int c)
{
    ImGui_ImplGlfwGL3_CharCallback(0, c);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    ocam.process_mouse_move(window, xpos, ypos);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    ocam.process_mouse_action(window, button, action, mods);
    ImGui_ImplGlfwGL3_MouseButtonCallback(window, button, action, mods);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    ocam.process_scroll(window, xoffset, yoffset);
    ImGui_ImplGlfwGL3_ScrollCallback(window, xoffset, yoffset);
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
