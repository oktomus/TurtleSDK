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

    glm::vec3 direction_;

};

class PointLight : public Light
{

public:

    virtual void setUniforms(const Shader& shader, const std::string& uname) const;
    virtual void ui();

    glm::vec3 position_;
    float constant_;
    float linear_;
    float quadratic_;
};

class SpotLight : public PointLight, public DirectionLight
{

public:

    virtual void setUniforms(const Shader& shader, const std::string& uname) const;
    virtual void ui();

    float cutOff_;
    float outerCutOff_;

};

#endif
