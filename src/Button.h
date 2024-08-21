#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL_rect.h>  // SDL_Point
#include "LTexture.h"       // LTexture

typedef struct SDL_Event SDL_Event;

typedef enum {
    BUTTON_SPRITE_MOUSE_OUT,
    BUTTON_SPRITE_MOUSE_OVER_MOTION,
    BUTTON_SPRITE_MOUSE_DOWN,
    BUTTON_SPRITE_MOUSE_UP,
    BUTTON_SPRITE_TOTAL
} ButtonSprite;

class Button {
public:
    Button();

    /**
     * Set top left coordinate of the button
     * 
     * \param x x coordinate
     * \param y y coordinate
     */
    void SetPosition(int x, int y);

    /**
     * Handles mouse events
     * 
     * \param e SDL_Event* input struct
     */
    void HandleEvent(SDL_Event* e);

    /**
     * Draw button sprite on screen
     */
    void Render();

private:
    const int BUTTON_WIDTH = 300;
    const int BUTTON_HEIGHT = 200;
    const int TOTAL_BUTTONS = 4;

    LTexture buttonSpriteSheetTexture;
    
    SDL_Point position;

    ButtonSprite currentSprite;
};

#endif