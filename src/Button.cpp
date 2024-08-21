#include "Button.h"
#include <SDL2/SDL.h>

Button::Button() : position({0, 0}), currentSprite(BUTTON_SPRITE_MOUSE_OUT) {}

void Button::SetPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void Button::HandleEvent(SDL_Event* e) {
    if (SDL_MOUSEMOTION == e->type || SDL_MOUSEBUTTONDOWN == e->type || SDL_MOUSEBUTTONUP == e->type) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        bool clickedInside = true;
        if (x < position.x || x > position.x + BUTTON_WIDTH || y < position.y || y > position.y + BUTTON_HEIGHT) {
            clickedInside = false;
        }

        if (!clickedInside) {
            currentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
        else {
            switch (e->type) {
                case SDL_MOUSEMOTION:
                currentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;

                case SDL_MOUSEBUTTONDOWN:
                currentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;

                case SDL_MOUSEBUTTONUP:
                currentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
            }
        }

    }
}