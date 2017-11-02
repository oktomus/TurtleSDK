#ifndef __BASE_MODEL_
#define __BASE_MODEL_

// System
#include <vector>
#include <iostream>

// Graphics Libs
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*
                   █         ▀▀█   
 ▄▄▄▄▄   ▄▄▄    ▄▄▄█   ▄▄▄     █   
 █ █ █  █▀ ▀█  █▀ ▀█  █▀  █    █   
 █ █ █  █   █  █   █  █▀▀▀▀    █   
 █ █ █  ▀█▄█▀  ▀█▄██  ▀█▄▄▀    ▀▄▄ 
 */

namespace model{

    /**
     * Represente un model 3D
     */
    class Base
    {
        public:

            /**
             * Dessine l'objet dans la fenetre
             */
            void draw();

            /**
              * Dessine les points de l'objet
              */
            void draw_points();

            friend std::ostream& operator<<(std::ostream &os, const Base& obj)
            {
                os << obj.modelType() << "[v:" << obj.nb_points() << "]";
            }

            size_t nb_points() const
            {
                return _nb_points;
            }

            void setColor(const float& r, const float& g, const float& b);

            const glm::vec3&  color() const;

            const glm::mat4& matrix();

            virtual const char* modelType() const = 0;

        protected:

            /**
             * Creer un objet 3D avec son VBO et VAO
             *
             * @param mode     Le type d'objet (triangle, quad, etc)
             * @param points   Nombre de points
             */
            Base(GLenum mode, size_t points);

            /**
              *
              */
            Base() = default;

            glm::vec3 _meshColor;

            glm::mat4 _meshMatrix;

            /**
             * Donnees du model.
             * Peut contenir des vertices
             */
            std::vector<float> data;

            /**
              * Prepare le model pour etre utilise avec GL.
              *
              * Appel initVBO et VBA
              */
            void prepare();


        private:

            /**
             * Le mode utilise pour afficher le model
             */
            GLenum _mode;

            /**
             * Buffer Data
             */
            GLuint vboPosition;

            /**
             * Array object
             */
            GLuint vaoPosition;

            /**
              * Nombre de points dans le model
              */
            size_t _nb_points;

            /**
             * Init the VBO then the VAO
             *
             * @return     Success code
             */
            int initArray();
    };

}
#endif
