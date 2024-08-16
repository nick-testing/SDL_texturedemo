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
    
    // Load foreground texture
    success = foregroundTexture.LoadFromFile(renderer, "assets/foreground.png");

    // Load background texture
    success = backgroundTexture.LoadFromFile(renderer, "assets/background.png");

    success = spriteClipTexture.LoadFromFile(renderer, "assets/samplespritesheet.png");
    
    if (success) {
        spriteClips[0].x = 0;
        spriteClips[0].y = 0;
        spriteClips[0].w = 100;
        spriteClips[0].h = 100;
        
        spriteClips[1].x = 100;
        spriteClips[1].y = 0;
        spriteClips[1].w = 100;
        spriteClips[1].h = 100;

        spriteClips[2].x = 0;
        spriteClips[2].y = 100;
        spriteClips[2].w = 100;
        spriteClips[2].h = 100;

        spriteClips[3].x = 100;
        spriteClips[3].y = 100;
        spriteClips[3].w = 100;
        spriteClips[3].h = 100;
    }
        
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

void Game::RenderLoop() {
    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (SDL_QUIT == e.type) {
                quit = true;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Render background texture
        backgroundTexture.Render(renderer, 0, 0);

        // Render foreground texture
        foregroundTexture.Render(renderer, 324, 418);

        // Reender sprites clipped from sprite sheet
        spriteClipTexture.Render(renderer, 0, 0, &spriteClips[0]);
        spriteClipTexture.Render(renderer, SCREEN_WIDTH - spriteClips[1].w, 0, &spriteClips[1]);
        spriteClipTexture.Render(renderer, 0, SCREEN_HEIGHT - spriteClips[2].h, &spriteClips[2]);
        spriteClipTexture.Render(renderer, 
                                 SCREEN_WIDTH - spriteClips[3].w,
                                 SCREEN_HEIGHT - spriteClips[3].h,
                                 &spriteClips[3]);

        // Update screen
        SDL_RenderPresent(renderer);
    }
}

void Game::Run() {
    if (Init()) {
        LoadMedia();
        RenderLoop();
    }
    Close();
}