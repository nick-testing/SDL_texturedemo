#include "SDLRenderDemo.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define SPRITES_PER_SHEET (4)

static SDL_Rect gSpriteClips[SPRITES_PER_SHEET];

SDLRenderDemo::SDLRenderDemo(): SDLProgram() {};

void SDLRenderDemo::RenderColorModulation(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b) {
    ClearScreen();
    modulatedTexture.SetColor(r, g, b);
    modulatedTexture.Render(renderer, 0, 0);
}

void SDLRenderDemo::RenderAlphaModulation(SDL_Renderer* renderer, Uint8 alpha) {
    ClearScreen();
    bgAlphaTexture.Render(renderer, 0, 0);
    fgAlphaTexture.SetAlpha(alpha);
    fgAlphaTexture.Render(renderer, 0, 0);
}

void SDLRenderDemo::Close() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;

    defaultTexture.Free();
    backgroundTexture.Free();
    foregroundTexture.Free();
    spriteSheetTexture.Free();
    modulatedTexture.Free();
    fgAlphaTexture.Free();
    bgAlphaTexture.Free();
    
    SDL_Quit();
    IMG_Quit();
}

bool SDLRenderDemo::LoadMedia() {
    bool textureLoadSuccess = true;

    // Load default texture
    textureLoadSuccess = defaultTexture.LoadFromFile(renderer, "assets/mainmenu.png");
    
    // Load foreground texture
    textureLoadSuccess = foregroundTexture.LoadFromFile(renderer, "assets/foreground.png");

    // Load background texture
    textureLoadSuccess = backgroundTexture.LoadFromFile(renderer, "assets/background.png");

    textureLoadSuccess = spriteSheetTexture.LoadFromFile(renderer, "assets/samplespritesheet.png");
    
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

void SDLRenderDemo::RenderLoop() {
    bool quit = false;
    SDL_Event e;

    // User selection render mode flag
    RenderMode renderMode = RENDER_DEFAULT;

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
            // Input handling
            else if(SDL_KEYDOWN == e.type) {
                switch (e.key.keysym.sym) {
                    // Render static texture
                    case SDLK_F1:
                        renderMode = RENDER_DEFAULT;
                        ClearScreen();
                        backgroundTexture.Render(renderer, 0, 0);
                        foregroundTexture.Render(renderer, 324, 418);
                        break;

                    // Render sprites from sprie sheet
                    case SDLK_F2:
                        // Top left sprite
                        spriteSheetTexture.Render(renderer, 0, 0, &gSpriteClips[0]);

                        // Top right sprite
                        spriteSheetTexture.Render(renderer,
                                                 SCREEN_WIDTH - gSpriteClips[1].w, 
                                                 0, 
                                                 &gSpriteClips[1]);
                        
                        // Bottom left sprite
                        spriteSheetTexture.Render(renderer,
                                                 0,
                                                 SCREEN_HEIGHT - gSpriteClips[2].h, 
                                                 &gSpriteClips[2]);

                        // Bottom right sprite
                        spriteSheetTexture.Render(renderer, 
                                                SCREEN_WIDTH - gSpriteClips[3].w,
                                                SCREEN_HEIGHT - gSpriteClips[3].h,
                                                &gSpriteClips[3]);
                        break;
                    
                    // Color modulation
                    case SDLK_F3:
                        renderMode = RENDER_RGB_MODULATION;
                        RenderColorModulation(renderer, r, g, b);
                        break;
                    
                    // Alpha modulation
                    case SDLK_F4:
                        renderMode = RENDER_ALPHA_MODULATION;
                        RenderAlphaModulation(renderer, a);
                        break;
                    
                    case SDLK_ESCAPE:
                        quit = true;
                }

                if (RENDER_RGB_MODULATION == renderMode) {
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
                else if (RENDER_ALPHA_MODULATION == renderMode) {
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

void SDLRenderDemo::Run() {
    if (Init()) {
        LoadMedia();
        RenderLoop();
    }
    Close();
}