#include "ButtonDemo.h"
#include <SDL2/SDL.h>

ButtonDemo::ButtonDemo() : SDLProgram() {}

bool ButtonDemo::LoadMedia() 
{
    bool loadSuccessful = true;

    for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) 
    {
        loadSuccessful = buttons[i].LoadMedia(renderer, "assets/button.png");
    }
    buttons[1].SetPosition(300,0);
    buttons[2].SetPosition(0, 200);
    buttons[3].SetPosition(300, 200);

    return loadSuccessful;
}

void ButtonDemo::RenderLoop() 
{
    bool quit = false;
    SDL_Event e;

    while (!quit) 
    {
        while(SDL_PollEvent(&e)) 
        {
            if (SDL_QUIT == e.type) 
            {
                quit = true;
            }
            for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) 
            {
                buttons[i].HandleEvent(&e);
            }
        }

        ClearScreen();
        for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) 
        {
            buttons[i].Render(renderer);
        }

        SDL_RenderPresent(renderer);
    }
}

void ButtonDemo::Close() 
{
    for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) 
    {
        buttons[i].Free();
    }
    SDLProgram::Close();
}

void ButtonDemo::Run() 
{
    if (Init()) 
    {
        LoadMedia();
        RenderLoop();
    }
    Close();

}