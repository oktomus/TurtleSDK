#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include <memory>

#include "camera/baseCamera.h"

namespace shader{
    class Base;
}

namespace model{
    class Base;
}

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

    private:

        std::vector<camera::Camera> _cameras;
        int _currentCamera;

        std::vector<shader::Base> _materials;
        std::vector<std::unique_ptr<model::Base>> _models;



    };


}

#endif
