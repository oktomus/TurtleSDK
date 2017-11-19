#ifndef __TURTLE_LIGHT__
#define __TURTLE_LIGHT__

#include <string>

// glm
#include <glm/glm.hpp>

#include "shader.h"


class Light{

public:

    Light(const glm::vec3& pambient, const glm::vec3 &pdiffuse, const glm::vec3 &pspecular);
    Light();

    virtual void setUniforms(const Shader& shader, const std::string& uname) const;
    virtual void ui();

    glm::vec3 ambient_;
    glm::vec3 diffuse_;
    glm::vec3 specular_;
};


class DirectionLight : public Light
{

public:

    virtual void setUniforms(const Shader& shader, const std::string& uname) const;
    virtual void ui();

    glm::vec3 direction_ = {-10.f, -10.f, -10.f};

};

class PointLight : public Light
{

public:

    virtual void setUniforms(const Shader& shader, const std::string& uname) const;
    virtual void ui();

    glm::vec3 position_ = {5.f, 5.f, 5.f};
    float constant_ = 1;
    float linear_ = 0.09;
    float quadratic_ = 0.032;
};

class SpotLight : public PointLight
{

public:

    virtual void setUniforms(const Shader& shader, const std::string& uname) const;
    virtual void ui();

    float cutOff_ = 12.5f;
    float outerCutOff_ = 20.f;
    glm::vec3 direction_ = {-10.f, -10.f, -10.f};

};

#endif
