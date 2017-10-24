#include "world.h"

#include <vector>

#include "shader/baseShader.h"

/*
                      ▀▀█        █ 
▄     ▄  ▄▄▄    ▄ ▄▄    █     ▄▄▄█ 
▀▄ ▄ ▄▀ █▀ ▀█   █▀  ▀   █    █▀ ▀█ 
 █▄█▄█  █   █   █       █    █   █ 
  █ █   ▀█▄█▀   █       ▀▄▄  ▀█▄██ 

 */

world::World::World()
{
}

void world::World::init(){
    _cameras.push_back(camera::Camera());
    _currentCamera = 0;
}

const camera::Camera& world::World::currentCamera() const{
    return _cameras.at(_currentCamera);
}

