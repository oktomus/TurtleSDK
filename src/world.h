#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include <memory>

#include "camera/baseCamera.h"
#include "model/primitive.h"

/*
                      ▀▀█        █ 
▄     ▄  ▄▄▄    ▄ ▄▄    █     ▄▄▄█ 
▀▄ ▄ ▄▀ █▀ ▀█   █▀  ▀   █    █▀ ▀█ 
 █▄█▄█  █   █   █       █    █   █ 
  █ █   ▀█▄█▀   █       ▀▄▄  ▀█▄██ 

 */

namespace world{

    class World{

    public:
        World();

        void init();

        const camera::Camera& currentCamera() const;

        void moveCamera()
        {
            _cameras.at(_currentCamera).move();
        }

    private:

        std::vector<camera::Camera> _cameras;
        int _currentCamera;


    };


}

#endif
