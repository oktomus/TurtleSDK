#include "object.h"

#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

Object::Object()
{
}

Object::Object(std::shared_ptr<Model> pModel) :
    model_(pModel)
{

}

void Object::draw(const Shader & shader)
{
    if(!model_->draw_) return;
    glm::mat4 transform_ = glm::mat4();

    // Revert order !
    transform_ = glm::translate(transform_, translate_);
    transform_ = glm::rotate(transform_, glm::radians(rotate_[0]), glm::vec3(1, 0, 0));
    transform_ = glm::rotate(transform_, glm::radians(rotate_[1]), glm::vec3(0, 1, 0));
    transform_ = glm::rotate(transform_, glm::radians(rotate_[2]), glm::vec3(0, 0, 1));
    transform_ = glm::scale(transform_, scale_);

    shader.setMat4("model", transform_);
    model_->draw(shader);
}

void Object::ui()
{
    ImGui::Text("Object properties");
    ImGui::SliderFloat3("Model position", glm::value_ptr(translate_), -10.f, 10.f);
    ImGui::SliderFloat3("Model rotation", glm::value_ptr(rotate_), 0.f, 360.f);
    ImGui::SliderFloat3("Model size", glm::value_ptr(scale_), 0.f, 5.f);
    model_->ui();
}
