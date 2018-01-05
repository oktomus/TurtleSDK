#include <cassert>
#include <iostream>

#include "turtle.h"
#include "grid.h"
#include "orbitCamera.h"
#include "fpsCamera.h"
#include "terrain.h"

Turtle Turtle::instance_;

Turtle &Turtle::getInstance()
{
    return Turtle::instance_;
}

float Turtle::getDeltaTime() const
{
    return deltaTime_;
}

int Turtle::getWinHeight() const
{
    return winHeight_;
}

int Turtle::getWinWidth() const
{
    return winWidth_;
}

void Turtle::init()
{
    static bool once = false;
    assert(!once);
    once = true;


    fprintf(stdout, "Initializing...\n");

    {
        fprintf(stdout, "GLFW...");
        glfwSetErrorCallback(Turtle::errorCallback);
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
        window_ = glfwCreateWindow(
                    winWidth_, winHeight_, "TurtleSDK", NULL, NULL);

        if (!window_)
        {
            fprintf(stderr, "Unable to create a window.\n");
            exit(2);
        }
        glfwMakeContextCurrent(window_);
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "CALLBACKS...");
        glfwSetFramebufferSizeCallback(window_, this->framebufferSizeCallback);
        glfwSetCursorPosCallback(window_, this->mouseCallback);
        glfwSetScrollCallback(window_, this->scrollCallback);
        glfwSetMouseButtonCallback(window_, this->mouseButtonCallback);
        glfwSetKeyCallback(window_, this->keyCallback);
        glfwSetCharCallback(window_, this->charCallback);

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
        ImGui_ImplGlfwGL3_Init(window_, false);
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "VIEWPORT...");
        glViewport(0, 0, winWidth_, winHeight_);
        framebufferSizeCallback(window_, winWidth_, winHeight_);
        fprintf(stdout, "OK\n");
    }


    {
        fprintf(stdout, "WORLD...");
        fprintf(stdout, "OK\n");
    }

    {
        fprintf(stdout, "SHADERS...");
        shaders_["phong"] = std::make_shared<Shader>("turtleLib/shaders/material");
        shaders_["sky"] = std::make_shared<Shader>("turtleLib/shaders/sky");
        shaders_["solid"] = std::make_shared<Shader>("turtleLib/shaders/solid");
        shaders_["light"] = std::make_shared<Shader>("turtleLib/shaders/flatBillBoardStill.vert",
                                                     "turtleLib/shaders/flatBillBoardStill.frag", "");

        fprintf(stdout, "OK\n");
    }
    {
        fprintf(stdout, "OBJECTS...");
        cam_ = std::make_unique<OrbitCamera>();
        models_.push_back(std::make_shared<Model>("turtleLib/models/woodenCase/case.obj"));
        objects_.push_back(Object(models_.back()));
        objects_.back().translate_.y = 10;
        models_.push_back(std::make_shared<Model>("turtleLib/models/light/light.obj"));
        lightDisplay_ = Object(models_.back());
        ground_ = std::make_shared<Terrain>(GridGenerator::flatGrid(50, 50));

        skybox_ = std::make_shared<SkyBox>("turtleLib/textures/craterlake", ".tga");

        // Lights
        dirLights_.push_back(DirectionLight());
        pointLights_.push_back(PointLight());
        pointLights_.push_back(PointLight());
        pointLights_.push_back(PointLight());
        pointLights_.push_back(PointLight());
        spotLights_.push_back(SpotLight());
        fprintf(stdout, "OK\n");
    }


    fprintf(stdout, "Init OK\n");

}

void Turtle::terminate()
{
    static bool once = false;
    assert(!once);
    once = true;

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

void Turtle::mainLoop()
{
    // Number of frames evaluated during the last second
    static unsigned int frames = 0;
    // Time pos of the last frame
    static float lastFrame = 0;
    // Time pas of last sec
    static float startFramesTime = 0;

    while (!glfwWindowShouldClose(window_))
    {
        frames += 1;
        currentTime_ = glfwGetTime();
        deltaTime_ = currentTime_ - lastFrame;
        lastFrame = currentTime_;

        if (currentTime_ - startFramesTime >= 1.0)
        {
            frameRate_ = 1000 / double(frames);
            frames = 0;
            startFramesTime += 1.0;
        }

        processInput(window_);
        ImGui_ImplGlfwGL3_NewFrame();

        displayFrame();

        {
            glFlush();
            ImGui::Render();
            glfwPollEvents();
            glfwSwapBuffers(window_);
        }
    }

}

void Turtle::displayFrame()
{
    displayUi();
    // STATE ASSIGN
    {
        glClearColor(clearColor_[0], clearColor_[1], clearColor_[2], clearColor_[3]);
        glClearDepth( 1.0 );
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

        //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        if(drawLine_)
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        else
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    // STATE ACT
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }

    // DRAW
    {

        glDepthMask(GL_FALSE);
        shaders_["sky"]->use();
        shaders_["sky"]->setMat4("projection", cam_->projection());
        shaders_["sky"]->setMat4("view", glm::mat4(glm::mat3(cam_->view())));
        skybox_->draw(*(shaders_["sky"].get()));
        glDepthMask(GL_TRUE);

        shaders_["phong"]->use();
        shaders_["phong"]->setFloat("material.shininess", 32.0f);

        dirLights_.back().setUniforms(*(shaders_["phong"].get()), "dirLight");
        for(size_t i = 0; i < 4; ++i)
        {
            pointLights_.at(i).setUniforms(*(shaders_["phong"].get()), "pointLights[" + std::to_string(i) + "]");
        }
        pointLights_.back().setUniforms(*(shaders_["phong"].get()), "spotLight");

        shaders_["phong"]->setMat4("view", cam_->view());
        shaders_["phong"]->setVec3("viewPos", cam_->pos);
        shaders_["phong"]->setMat4("projection", cam_->projection());
        shaders_["phong"]->setBool("noTexture", false);

        for(auto o : objects_)
        {
            o.draw(*(shaders_["phong"].get()));
        }
        shaders_["phong"]->setBool("noTexture", true);
        ground_->draw(*(shaders_["phong"].get()));

        if(drawLights_) displayLights();
    }
}

void Turtle::displayLights()
{
    shaders_["light"]->use();
    shaders_["light"]->setMat4("view", cam_->view());
    shaders_["light"]->setMat4("projection", cam_->projection());
    glm::vec3 CameraRight_worldspace = {cam_->view()[0][0], cam_->view()[1][0], cam_->view()[2][0]};
    glm::vec3 CameraUp_worldspace = {cam_->view()[0][1], cam_->view()[1][1], cam_->view()[2][1]};
    shaders_["light"]->setVec3("camUp", CameraUp_worldspace);
    shaders_["light"]->setVec3("camRight", CameraRight_worldspace);

    for(DirectionLight d : dirLights_)
    {
        lightDisplay_.translate_ = d.direction_;
        shaders_["light"]->setVec3("fill", d.diffuse_);
        shaders_["light"]->setVec3("billboardCenter", d.direction_);
        lightDisplay_.draw(*(shaders_["light"].get()));
    }

    for(PointLight p: pointLights_)
    {
        lightDisplay_.translate_ = p.position_;
        shaders_["light"]->setVec3("fill", p.diffuse_);
        shaders_["light"]->setVec3("billboardCenter", p.position_);
        lightDisplay_.draw(*(shaders_["light"].get()));
    }

    for(SpotLight s: spotLights_)
    {
        lightDisplay_.translate_ = s.position_;
        shaders_["light"]->setVec3("fill", s.diffuse_);
        shaders_["light"]->setVec3("billboardCenter", s.position_);
        lightDisplay_.draw(*(shaders_["light"].get()));
    }

}

void Turtle::displayUi()
{
    // IMGUI
    {
        // Top bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("Turtle"))
            {
                static bool should_quit = false;
                ImGui::MenuItem("Quit", "Escape", &should_quit);
                if(should_quit) glfwSetWindowShouldClose(window_, true);
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Windows"))
            {
                ImGui::MenuItem("Debug", "", &debug_window_);
                ImGui::MenuItem("Objects", "", &scene_window);
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
        // Debug win
        if(debug_window_)
        {
            ImGui::Begin("Turtle", &debug_window_);

            ImGui::Checkbox("Disable viewport events", &disableViewportEvents_);
            ImGui::Text("%f ms/frame, ~%d FPS", frameRate_, (long)(1000 / frameRate_));
            ImGui::ColorEdit4("Clear color", glm::value_ptr(clearColor_));
            ImGui::End();

        }

        if(scene_window)
        {
            ImGui::Begin("Scene", &scene_window);

            ImGui::Checkbox("Wireframe mode", &drawLine_);
            ImGui::Checkbox("Display lights in the viewport", &drawLights_);

            if(ImGui::CollapsingHeader("Skybox"))
            {
                ImGui::Checkbox("Show sky", &skybox_->draw_);
            }

            if(ImGui::CollapsingHeader("Terrain"))
            {
                ImGui::Checkbox("Show terrain", &ground_->draw_);

                if(ImGui::Button("Randomize Terrain"))
                    ground_->randomize();
            }


            if(ImGui::CollapsingHeader("Camera"))
            {
                ImGui::Text("Camera Pos (%f, %f, %f)", cam_->pos.x, cam_->pos.y, cam_->pos.z);
                if (ImGui::Button("Reset Camera"))
                {
                    cam_->reset();
                }
                if (ImGui::Button("Switch to FPS"))
                {
                    cam_ = std::make_unique<FPSCamera>();
                }
                if (ImGui::Button("Switch to Orbit"))
                {
                    cam_ = std::make_unique<OrbitCamera>();
                }
            }

            if(ImGui::CollapsingHeader("Objects"))
            {
                static int currentModel = 0;
                std::string modelCombo = "";
                for(size_t i = 0; i < objects_.size(); i++)
                {
                    modelCombo += std::to_string(i) + '\0';
                }
                modelCombo += '\0';
                ImGui::Combo("Edit Object", &currentModel, modelCombo.c_str());

                objects_.at(currentModel).ui();
                if (ImGui::Button("Create a new instance"))
                {
                    objects_.push_back(objects_.at(currentModel));
                }
                if (ImGui::Button("Create a new random instance"))
                {
                    objects_.push_back(objects_.at(currentModel));
                    objects_.back().random();
                }
            }

            if(ImGui::CollapsingHeader("Lighting"))
            {
                static int currentLight = 0;
                std::string lightsCombo = "";
                for(size_t i = 0; i < dirLights_.size() + pointLights_.size() + spotLights_.size(); i++)
                    lightsCombo += std::to_string(i) + '\0';
                lightsCombo += '\0';
                ImGui::Combo("Edit Light", &currentLight, lightsCombo.c_str());

                if(currentLight == -1)
                    ImGui::Text("No light selected");
                else if(currentLight < dirLights_.size())
                {
                    ImGui::Text("Directional light");
                    dirLights_.at(currentLight).ui();
                }
                else if(currentLight < dirLights_.size() + pointLights_.size())
                {
                    ImGui::Text("Point light");
                    pointLights_.at(currentLight - dirLights_.size()).ui();
                }
                else
                {
                    ImGui::Text("Spot light");
                    spotLights_.at(currentLight - dirLights_.size() - pointLights_.size()).ui();
                }
            }

            ImGui::End();

        }
    }

}

Turtle::Turtle()
{

}

void Turtle::framebufferSizeCallback(GLFWwindow *, int pwidth, int pheight)
{
    Turtle & tu = Turtle::getInstance();
    glViewport(0, 0, pwidth, pheight);
    tu.winWidth_ = pwidth;
    tu.winHeight_ = pheight;
}

void Turtle::scrollCallback(GLFWwindow *, double xoffset, double yoffset)
{
    Turtle & tu = Turtle::getInstance();
    ImGui_ImplGlfwGL3_ScrollCallback(tu.window_, xoffset, yoffset);

    if(ImGui::IsAnyWindowHovered()) return;

    if(tu.disableViewportEvents_) return;

    tu.cam_->process_scroll(tu.window_, xoffset, yoffset);

}

void Turtle::processInput(GLFWwindow *)
{
    if(ImGui::IsAnyWindowHovered()) return;
}

void Turtle::keyCallback(GLFWwindow*, int key, int, int action, int mods)
{
    ImGui_ImplGlfwGL3_KeyCallback(0, key, 0, action, mods);
    if(ImGui::IsAnyWindowHovered()) return;

    Turtle & tu = Turtle::getInstance();
    // keyboard shortcuts
    if(key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(tu.window_, true);
    if(key == GLFW_KEY_R) tu.cam_->reset();
    if(key == GLFW_KEY_F) tu.cam_ = std::make_unique<FPSCamera>();
    if(key == GLFW_KEY_V) tu.cam_ = std::make_unique<OrbitCamera>();

    if(!tu.disableViewportEvents_)
        tu.cam_->process_key(tu.window_, key, 0, action, mods);
}

void Turtle::charCallback(GLFWwindow*, unsigned int c)
{
    ImGui_ImplGlfwGL3_CharCallback(0, c);
    if(ImGui::IsAnyWindowHovered()) return;
}

void Turtle::mouseCallback(GLFWwindow*, double xpos, double ypos)
{
    Turtle & tu = Turtle::getInstance();
    static bool hidden = false;
    if(ImGui::IsAnyWindowHovered())
    {
        if(hidden)
        {
            glfwSetInputMode(tu.window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            hidden = false;
        }
        return;
    }
    else
    {
        if(!hidden)
        {
            glfwSetInputMode(tu.window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            hidden = true;
        }
    }

    if(!tu.disableViewportEvents_)
        tu.cam_->process_mouse_move(tu.window_, xpos, ypos);
}

void Turtle::mouseButtonCallback(GLFWwindow*, int button, int action, int mods)
{
    Turtle & tu = Turtle::getInstance();
    ImGui_ImplGlfwGL3_MouseButtonCallback(tu.window_, button, action, mods);
    if(ImGui::IsAnyWindowHovered()) return;

    if(!tu.disableViewportEvents_)
        tu.cam_->process_mouse_action(tu.window_, button, action, mods);
}
