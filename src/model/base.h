#ifndef __BASE__
#define __BASE__

// System
#include <vector>
#include <iostream>

// Graphics Libs
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glut.h>

/*
 █                          
 █▄▄▄    ▄▄▄    ▄▄▄    ▄▄▄  
 █▀ ▀█  ▀   █  █   ▀  █▀  █ 
 █   █  ▄▀▀▀█   ▀▀▀▄  █▀▀▀▀ 
 ██▄█▀  ▀▄▄▀█  ▀▄▄▄▀  ▀█▄▄▀ 
                            
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

            friend std::ostream& operator<<(std::ostream &os, const Base& obj)
            {
                os << "Model[v:" << obj.nb_points << "]";
            }

            const size_t & nb_points;

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
             * Initialise le buffer
             *
             * @return     Une code d'execution, 0 pour succees
             */
            int initArrayBuffer();

            /**
             * Initialise l'objet lie au buffer
             *
             * @return     Une code d'execution, 0 pour succees
             */
            int initArrayObject();


    };
}
#endif
