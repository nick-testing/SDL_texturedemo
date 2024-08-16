#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

Game::Game(): window(NULL), renderer(NULL) {};

/**
 * Initialize SDL and SDL_image libraries.
 * Init() also creates an SDL window and a hardware accelerated SDL renderer for that window.
 * 
 * \return true on succes, false on failure
 */
bool Game::Init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed, SDL error: " << SDL_GetError() << std::endl;
        success = false;
    }
    else {
        window = SDL_CreateWindow("SDL Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cerr << "SDL window creation failed, SDL error: " << SDL_GetError() << std::endl;
            success = false;
        }
        else {
            // Create renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (!renderer) {
                std::cerr << "SDL CreateRenderer failed, SDL error: " << SDL_GetError() << std::endl;
                success = false;
            }
            else {
                // Initialize SDL image PNG loading
                if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
                    std::cerr << "SDL_Image init failed, SDL error: " << SDL_GetError() << std::endl;
                    success = false;
                }
            }
        }
    }

    return success;
}

bool Game::LoadMedia() {
    bool success = true;
    
    success = foregroundTexture.LoadFromFile(renderer, "assets/foreground.png");

    success = backgroundTexture.LoadFromFile(renderer, "assets/background.png");
    
    return success;
}

void Game::Close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;

    backgroundTexture.Free();
    foregroundTexture.Free();

    SDL_Quit();
    IMG_Quit();
}