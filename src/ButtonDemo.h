#ifndef BUTTON_DEMO_H
#define BUTTON_DEMO_H

#include "SDLProgram.h"
#include "Button.h"

class ButtonDemo : SDLProgram 
{
    public:
        ButtonDemo();
        void Run() override;
    private:
        Button buttons[BUTTON_SPRITE_TOTAL];

        bool LoadMedia() override;
        void RenderLoop() override;
        void Close() override;
};

#endif