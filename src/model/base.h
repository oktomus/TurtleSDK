#ifndef __BASE__
#define __BASE__

// System
#include <vector>

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
             * Creer un objet 3D avec son VBO et VAO
             *
             * @param mode     Le type d'objet (triangle, quad, etc)
             */
            Base(GLenum mode);

            /**
             * Dessine l'objet dans la fenetre
             */
            void draw();

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
             * Donnees du model.
             * Peut contenir des vertices
             */
            std::vector<float> data;

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
