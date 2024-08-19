#ifndef SDLRENDERDEMO_H
#define SDLRENDERDEMO_H

#include "LTexture.h"
#include "SDLProgram.h"
#include <SDL2/SDL_rect.h>

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

typedef enum RenderMode {
    RENDER_DEFAULT,
    RENDER_RGB_MODULATION,
    RENDER_ALPHA_MODULATION
} RenderMode;

class SDLRenderDemo : SDLProgram {
public:
    SDLRenderDemo();
    void Run() override;

private:
    LTexture defaultTexture;

    LTexture backgroundTexture;
    LTexture foregroundTexture;

    // Scene sprites
    LTexture spriteSheetTexture;

    // modulation test texture
    LTexture modulatedTexture;

    // Alpha blend textures
    LTexture fgAlphaTexture;
    LTexture bgAlphaTexture; 
    
    bool LoadMedia() override;
    void RenderLoop() override;
    void Close() override;

    void RenderColorModulation(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
    void RenderAlphaModulation(SDL_Renderer* renderer, Uint8 alpha);
};

#endif