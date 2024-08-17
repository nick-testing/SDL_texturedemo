#ifndef GAME_H
#define GAME_H

#include "LTexture.h"
#include <SDL2/SDL_rect.h>

#define SPRITES_PER_SHEET (4)

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

class Game {
public:
    Game();
    void Run();

private:
    static const int SCREEN_HEIGHT = 600;
    static const int SCREEN_WIDTH = 800;

    SDL_Window* window;
    SDL_Renderer* renderer;
    LTexture backgroundTexture;
    LTexture foregroundTexture;

    // Scene sprites
    LTexture spriteClipTexture;
    SDL_Rect spriteClips[SPRITES_PER_SHEET];

    // modulation test texture
    LTexture modulatedTexture;
    
    bool Init();
    bool LoadMedia();
    void RenderLoop();
    void Close();
};

#endif