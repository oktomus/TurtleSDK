#ifndef __PRIMITIVE__
#define __PRIMITIVE__

#include "base.h"

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
}

#endif
