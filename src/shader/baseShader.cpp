#include "baseShader.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

/*
        █                 █               
  ▄▄▄   █ ▄▄    ▄▄▄    ▄▄▄█   ▄▄▄    ▄ ▄▄ 
 █   ▀  █▀  █  ▀   █  █▀ ▀█  █▀  █   █▀  ▀
  ▀▀▀▄  █   █  ▄▀▀▀█  █   █  █▀▀▀▀   █    
 ▀▄▄▄▀  █   █  ▀▄▄▀█  ▀█▄██  ▀█▄▄▀   █    

 */

const std::string shader::readFile(const std::string & path)
{
    std::ifstream txtFile(path);

    if (!txtFile.is_open())
    {
        throw std::runtime_error("Impossible d'ouvrir le fichier " + path);
    }

    std::string txtContent(
            (std::istreambuf_iterator<char>(txtFile)),
            (std::istreambuf_iterator<char>()) 
            );


    txtFile.close();
    return txtContent;
}
