#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL_rect.h>  // SDL_Point
#include "LTexture.h"       // LTexture

typedef union SDL_Event SDL_Event;
typedef struct SDL_Renderer SDL_Renderer;

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
     * 
     * \param renderer the rendering context
     */
    void Render(SDL_Renderer* renderer);

    /**
     * Loads desired button texture
     * 
     * \param renderer the rendering context
     * \param path image file path
     * \return true on success, false otherwise
     */
    bool LoadMedia(SDL_Renderer* renderer, const char* path);

    /**
     * Frees allocated texture
     */
    void Free();

private:
    const int BUTTON_WIDTH = 300;
    const int BUTTON_HEIGHT = 200;
    SDL_Rect spriteClips[BUTTON_SPRITE_TOTAL];

    LTexture buttonSpriteSheetTexture;
    
    SDL_Point position;

    ButtonSprite currentSprite;
};

#endif