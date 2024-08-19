#ifndef SDLPROGRAM
#define SDLPROGRAM

#include "LTexture.h"
#include <SDL2/SDL_rect.h>

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

class SDLProgram {
public:
    SDLProgram();
    virtual void Run() = 0;

protected:
    static const int SCREEN_HEIGHT = 600;
    static const int SCREEN_WIDTH = 800;

    SDL_Window* window;
    SDL_Renderer* renderer;

    virtual bool Init();
    virtual void ClearScreen();

    virtual void RenderLoop() = 0;
    virtual bool LoadMedia() = 0;
    virtual void Close() = 0;
};

#endif