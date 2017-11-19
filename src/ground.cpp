#include <iostream>
#include <imgui.h>

#include "ground.h"
#include "mesh.h"

Ground::Ground()
{
    loadModel("turtleLib/models/ground.obj");

    Texture texture;
    texture.id = textureFromFile("height03.png", "turtleLib/textures");
    texture.type = "texture_height";

    meshes.at(0).textures_.push_back(texture);

    updateVars();
}

void Ground::randomize()
{

}

void Ground::draw(const Shader &shader)
{
    shader.setFloat("size", size_);
    shader.setFloat("baseHeight", baseHeight_);
    shader.setFloat("heightFactor", heightFactor_);
    shader.setVec3("groundColor1", color_);
    shader.setVec3("outside", outsideColor_);
    Model::draw(shader);
}

void Ground::ui()
{
    Model::ui();
    ImGui::SliderFloat("Height factor", &heightFactor_, 1, 10);
}

void Ground::updateVars()
{
    float nearx = 100000;
    float farx = -1000000;
    float lowerLine = 100000;
    for(Vertex v: meshes.at(0).points_)
    {
        if(v.Position.x > farx) farx = v.Position.x;
        if(v.Position.x < nearx) nearx = v.Position.x;
        if(v.Position.y < lowerLine) lowerLine = v.Position.y;
    }

    size_ = farx - nearx;
    baseHeight_ = lowerLine;
}
