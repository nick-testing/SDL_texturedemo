#ifndef GAME_H
#define GAME_H

#include "LTexture.h"
#include <SDL2/SDL_rect.h>

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

typedef enum RenderMode {
    RENDER_DEFAULT,
    RENDER_RGB_MODULATION,
    RENDER_ALPHA_MODULATION
} RenderMode;

class Game {
public:
    Game();
    void Run();

private:
    static const int SCREEN_HEIGHT = 600;
    static const int SCREEN_WIDTH = 800;

    SDL_Window* window;
    SDL_Renderer* renderer;
    LTexture defaultTexture;

    LTexture backgroundTexture;
    LTexture foregroundTexture;

    // Scene sprites
    LTexture spriteClipTexture;

    // modulation test texture
    LTexture modulatedTexture;

    // Alpha blend textures
    LTexture fgAlphaTexture;
    LTexture bgAlphaTexture; 
    
    bool Init();
    bool LoadMedia();
    void RenderLoop();
    void Close();

    void RenderColorModulation(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);
    void RenderAlphaModulation(SDL_Renderer* renderer, Uint8 alpha);

    void ClearScreen();
};

#endif