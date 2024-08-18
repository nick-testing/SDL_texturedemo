#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define SPRITES_PER_SHEET (4)

static SDL_Rect gSpriteClips[SPRITES_PER_SHEET];

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
        window = SDL_CreateWindow("SDL Renderer",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
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

/**
 * Clears currently displayed image
 */
void Game::ClearScreen() {
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

/**
 * Renders a texture with color modulation applied
 * 
 * \param renderer the rendering context
 * \param r red color value
 * \param g green color value
 * \param b blue color value
 */
void Game::RenderColorModulation(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) {
    ClearScreen();
    modulatedTexture.SetColor(r, g, b);
    modulatedTexture.Render(renderer, 0, 0);
}

/**
 * Renders the alpha modulation scene
 * 
 * \param renderer the rendering context
 * \param alpha alpha value used for modulating the texture
 */
void Game::RenderAlphaModulation(SDL_Renderer* renderer, Uint8 alpha) {
    ClearScreen();
    bgAlphaTexture.Render(renderer, 0, 0);
    fgAlphaTexture.SetAlpha(alpha);
    fgAlphaTexture.Render(renderer, 0, 0);
}

void Game::Close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;

    defaultTexture.Free();
    backgroundTexture.Free();
    foregroundTexture.Free();
    spriteClipTexture.Free();
    modulatedTexture.Free();
    
    SDL_Quit();
    IMG_Quit();
}

/**
 * Manually load all textures stored at the ./assets/ directory
 * 
 * \todo convert this to automatic loading
 */
bool Game::LoadMedia() {
    bool textureLoadSuccess = true;

    // Load default texture
    textureLoadSuccess = defaultTexture.LoadFromFile(renderer, "assets/mainmenu.png");
    
    // Load foreground texture
    textureLoadSuccess = foregroundTexture.LoadFromFile(renderer, "assets/foreground.png");

    // Load background texture
    textureLoadSuccess = backgroundTexture.LoadFromFile(renderer, "assets/background.png");

    textureLoadSuccess = spriteClipTexture.LoadFromFile(renderer, "assets/samplespritesheet.png");
    
    if (textureLoadSuccess) {
        // Top left sprite
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 100;
        gSpriteClips[0].h = 100;
        
        // Top right sprite
        gSpriteClips[1].x = 100;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = 100;
        gSpriteClips[1].h = 100;

        // Bottom left sprite
        gSpriteClips[2].x = 0;
        gSpriteClips[2].y = 100;
        gSpriteClips[2].w = 100;
        gSpriteClips[2].h = 100;

        // Bottom right sprite
        gSpriteClips[3].x = 100;
        gSpriteClips[3].y = 100;
        gSpriteClips[3].w = 100;
        gSpriteClips[3].h = 100;
    }

    // Load modulated texture
    textureLoadSuccess = modulatedTexture.LoadFromFile(renderer, "assets/RGBWtexture.png");
    
    // Load alpha blend textures
    textureLoadSuccess = fgAlphaTexture.LoadFromFile(renderer, "assets/alphafadeout.png");
    if(textureLoadSuccess) {
        fgAlphaTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
    }
    textureLoadSuccess = bgAlphaTexture.LoadFromFile(renderer, "assets/alphafadein.png");

    return textureLoadSuccess;
}

void Game::RenderLoop() {
    bool quit = false;
    SDL_Event e;

    // Demo mode flags
    bool rgbModulationOn = false;
    bool alphaModulationOn = false;

    // Modulation componenets
    Uint8 r = 0xFF;
    Uint8 g = 0xFF;
    Uint8 b = 0xFF;
    // Alpha component
    Uint8 a = 0xFF;

    // Show main menu
    ClearScreen();
    defaultTexture.Render(renderer, 0, 0);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (SDL_QUIT == e.type) {
                quit = true;
            }
            else if(SDL_KEYDOWN == e.type) {
                switch (e.key.keysym.sym) {
                    case SDLK_F1:
                        // Render Midnight sky texture
                        ClearScreen();
                        backgroundTexture.Render(renderer, 0, 0);
                        foregroundTexture.Render(renderer, 324, 418);
                        rgbModulationOn = false;
                        alphaModulationOn = false;
                        break;

                    case SDLK_F2:
                        // Render sprites from sprite sheet
                        // Render top left sprite
                        spriteClipTexture.Render(renderer, 0, 0, &gSpriteClips[0]);

                        // Render top right sprite
                        spriteClipTexture.Render(renderer,
                                                 SCREEN_WIDTH - gSpriteClips[1].w, 
                                                 0, 
                                                 &gSpriteClips[1]);
                        
                        // Render bottom left sprite
                        spriteClipTexture.Render(renderer,
                                                 0,
                                                 SCREEN_HEIGHT - gSpriteClips[2].h, 
                                                 &gSpriteClips[2]);

                        // Render bottom right sprite
                        spriteClipTexture.Render(renderer, 
                                                SCREEN_WIDTH - gSpriteClips[3].w,
                                                SCREEN_HEIGHT - gSpriteClips[3].h,
                                                &gSpriteClips[3]);
                        break;
                    
                    case SDLK_F3:
                        // Color modulation - change rgb value on keypress
                        RenderColorModulation(renderer, r, g, b);
                        rgbModulationOn = true;
                        alphaModulationOn = false;
                        break;

                    case SDLK_F4:
                        // Alpha modulation - change alpha value on keypress
                        RenderAlphaModulation(renderer, a);
                        alphaModulationOn = true;
                        break;
                    
                    case SDLK_ESCAPE:
                        quit = true;
                }

                if(rgbModulationOn) {
                    switch (e.key.keysym.sym) {
                        case SDLK_q:
                            r += 32;
                            RenderColorModulation(renderer, r, g, b);
                            break;

                        case SDLK_w:
                            g += 32;
                            RenderColorModulation(renderer, r, g, b);
                            break;

                        case SDLK_e:
                            b+=32;
                            RenderColorModulation(renderer, r, g, b);
                            break;

                        case SDLK_a:
                            r -= 32;
                            RenderColorModulation(renderer, r, g, b);
                            break;

                        case SDLK_s:
                            g -= 32;
                            RenderColorModulation(renderer, r, g, b);
                            break;

                        case SDLK_d:
                            b -= 32;
                            RenderColorModulation(renderer, r, g, b);
                            break;
                    }
                }
                if (alphaModulationOn) {
                    if (e.key.keysym.sym == SDLK_w) {
                        a = (a + 32 > 255) ? 255 : a + 32;
                        RenderAlphaModulation(renderer, a);
                    }
                    if (e.key.keysym.sym == SDLK_s) {
                        a = (a - 32 < 0) ? 0 : a - 32;
                        RenderAlphaModulation(renderer, a);
                    }
                }
            }
        }
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