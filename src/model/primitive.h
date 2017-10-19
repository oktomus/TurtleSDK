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
    };
}

#endif
