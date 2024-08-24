#include "SDLAnimationDemo.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

static const int WALKING_ANIMATION_FRAMES = 4;
static const int FRAME_DELAY = 35;
static SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];

SDLAnimationDemo::SDLAnimationDemo(): SDLProgram() {};

void SDLAnimationDemo::Close() 
{
    spriteSheetTexture.Free();
            
    SDLProgram::Close();
}

bool SDLAnimationDemo::LoadMedia() 
{
    bool loadMediaSuccessful = true;
    loadMediaSuccessful = spriteSheetTexture.LoadFromFile(renderer, "assets/animationsheet.png");

    if (loadMediaSuccessful) 
    {
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 100;
        gSpriteClips[0].h = 330;

        gSpriteClips[1].x = 100;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = 100;
        gSpriteClips[1].h = 330;

        gSpriteClips[2].x = 200;
        gSpriteClips[2].y = 0;
        gSpriteClips[2].w = 100;
        gSpriteClips[2].h = 330;

        gSpriteClips[3].x = 300;
        gSpriteClips[3].y = 0;
        gSpriteClips[3].w = 100;
        gSpriteClips[3].h = 330;
    }

    return loadMediaSuccessful;
}

void SDLAnimationDemo::RenderLoop() 
{
    bool quit = false;
    SDL_Event e;

    // Holds current animation frame
    int frame = 0;

    while (!quit) 
    {
        while (SDL_PollEvent(&e)) 
        {
            if (SDL_QUIT == e.type || SDLK_ESCAPE == e.key.keysym.sym) 
            {
                quit = true;
            }
        }
        ClearScreen();

        // Render current frame - leave frame on screen for (FRAME_DELAY) screen refreshes
        SDL_Rect* currentClip = &gSpriteClips[frame / FRAME_DELAY];
        spriteSheetTexture.Render(renderer,
                                  (SCREEN_WIDTH - currentClip->w) / 2,
                                  (SCREEN_HEIGHT - currentClip->h) / 2, 
                                  currentClip);

        SDL_RenderPresent(renderer);
        
        // Cycle the animation
        frame = ((frame + 1) / FRAME_DELAY) < WALKING_ANIMATION_FRAMES ? frame + 1 : 0;
    }

}

void SDLAnimationDemo::Run() 
{
    if (Init()) 
    {
        LoadMedia();
        RenderLoop();
    }
    Close();
}