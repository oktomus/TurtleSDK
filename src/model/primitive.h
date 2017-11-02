#ifndef __PRIMITIVE__
#define __PRIMITIVE__

#include "baseModel.h"

/*
                 ▀             ▀      ▄      ▀                 
 ▄▄▄▄    ▄ ▄▄  ▄▄▄    ▄▄▄▄▄  ▄▄▄    ▄▄█▄▄  ▄▄▄    ▄   ▄   ▄▄▄  
 █▀ ▀█   █▀  ▀   █    █ █ █    █      █      █    ▀▄ ▄▀  █▀  █ 
 █   █   █       █    █ █ █    █      █      █     █▄█   █▀▀▀▀ 
 ██▄█▀   █     ▄▄█▄▄  █ █ █  ▄▄█▄▄    ▀▄▄  ▄▄█▄▄    █    ▀█▄▄▀ 
 █                                                             
 */

namespace model{

    /**
     * Represente un triangle 3D
     */
    class Triangle : public Base
    {
        public:

            /**
             * Creer un triange
             *
             * Les points sont passes en parametres
             */
            Triangle(
                    float xa, float ya, float za,
                    float xb, float yb, float zb,
                    float xc, float yc, float zc);

            const char* modelType() const
            {
                return "Triangle";
            }
    };

    class EBOTriangle : public Base
    {
        public:

            EBOTriangle(
                    float xa, float ya, float za,
                    float xb, float yb, float zb,
                    float xc, float yc, float zc);

            const char* modelType() const
            {
                return "EBOTriangle";
            }
    };
    
    /**
     * Represente un Quad 3D
     */
    class Quad : public Base
    {
        public:

            /**
             * Creer un quad
             *
             * Les points sont passes en parametres
             */
            Quad(
                    float xa, float ya, float za,
                    float xb, float yb, float zb,
                    float xc, float yc, float zc,
                    float xd, float yd, float zd);

            const char* modelType() const
            {
                return "Quad";
            }
    };

    /**
     * Represente un Cube
     */
    class Cube : public Base
    {
        public:

            /**
             * Creer un cube
             *
             * @param center    La position centrale du cube
             * @param size      La taille du cube
             */
            Cube(float x, float y, float z, float size);

            const char* modelType() const
            {
                return "Cube";
            }
    };
}

#endif
