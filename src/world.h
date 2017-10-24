#ifndef __WORLD__
#define __WORLD__

#include <vector>

#include "model/primitive.h"
#include "shader/baseShader.h"
#include "camera/baseCamera.h"

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
        World()
        {
        }

        void init(){

            _cameras.push_back(camera::Camera());
            _currentCamera = 0;

        }

        const camera::Camera& currentCamera() const{
            return _cameras.at(_currentCamera);
        }

    private:

        std::vector<camera::Camera> _cameras;
        int _currentCamera;

        std::vector<shader::Base> _materials;
        std::vector<std::unique_ptr<model::Base>> _models;



    };


}

#endif
