#ifndef SDLANIMATIONDEMO_H
#define SDLANIMATIONDEMO_H

#include "LTexture.h"
#include "SDLProgram.h"

class SDLAnimationDemo : SDLProgram {
public:
    SDLAnimationDemo();
    void Run() override;
private: 
    LTexture spriteSheetTexture;
    bool LoadMedia() override;
    void RenderLoop() override;
    void Close() override; 
};

#endif