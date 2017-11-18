#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>

#include "light.h"

Light::Light(const glm::vec3 &pambient, const glm::vec3 &pdiffuse, const glm::vec3 &pspecular) :
    ambient_(pambient), diffuse_(pdiffuse), specular_(pspecular)
{
}

Light::Light() :
    Light({0.1f, .1f, .1f}, {.5f, .5f, .5f}, {1.f, 1.f, 1.f})
{

}

void Light::setUniforms(const Shader &shader, const std::string &uname) const
{
    shader.setVec3(uname + ".value.ambient", ambient_);
    shader.setVec3(uname + ".value.diffuse", diffuse_);
    shader.setVec3(uname + ".value.specular", specular_);
}

void Light::ui()
{
    ImGui::SliderFloat3("Ambient", glm::value_ptr(ambient_), 0.0f, 1.0f);
    ImGui::SliderFloat3("Diffuse", glm::value_ptr(diffuse_), 0.0f, 1.0f);
    ImGui::SliderFloat3("Specular", glm::value_ptr(specular_), 0.0f, 1.0f);
}

void DirectionLight::setUniforms(const Shader &shader, const std::string &uname) const
{
    Light::setUniforms(shader, uname);
    shader.setVec3(uname + ".direction", direction_);
}

void DirectionLight::ui()
{
    Light::ui();
    ImGui::SliderFloat3("Direction", glm::value_ptr(direction_), -10.f, 10.f);
}

void PointLight::setUniforms(const Shader &shader, const std::string &uname) const
{
    Light::setUniforms(shader, uname);
    shader.setFloat(uname + ".constant", constant_);
    shader.setFloat(uname + ".linear", linear_);
    shader.setFloat(uname + ".quadratic", quadratic_);
    shader.setVec3(uname + ".position", position_);
}

void PointLight::ui()
{
    Light::ui();
    ImGui::SliderFloat("Constant", &constant_, 0, 10);
    ImGui::SliderFloat("Linear", &linear_, 0, 1);
    ImGui::SliderFloat("Quadratic", &quadratic_, 0, .1);
    ImGui::SliderFloat3("Position", glm::value_ptr(position_), -10, 10);
}

void SpotLight::setUniforms(const Shader &shader, const std::string &uname) const
{
    DirectionLight::setUniforms(shader, uname);
    PointLight::setUniforms(shader, uname);
    shader.setFloat(uname + ".cutOff", cutOff_);
    shader.setFloat(uname + ".outerCutOff", outerCutOff_);
}

void SpotLight::ui()
{
    PointLight::ui();
    ImGui::SliderFloat3("Direction", glm::value_ptr(direction_), -10.f, 10.f);
    ImGui::SliderAngle("Cut off", &cutOff_, 0, 360.f);
    ImGui::SliderAngle("Outer cut off", &outerCutOff_, 0, 360.f);
}
