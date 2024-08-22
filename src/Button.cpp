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

void Button::Render(SDL_Renderer* renderer) {
    buttonSpriteSheetTexture.Render(renderer, position.x, position.y, &spriteClips[currentSprite]);
}

bool Button::LoadMedia(SDL_Renderer* renderer, const char* path) {
    Free();
    bool loadMediaSuccessful = true;
    loadMediaSuccessful = buttonSpriteSheetTexture.LoadFromFile(renderer, path);

    if (loadMediaSuccessful) {
        spriteClips[0].x = 0;
        spriteClips[0].y = 0;
        spriteClips[0].w = BUTTON_WIDTH;
        spriteClips[0].h = BUTTON_HEIGHT;

        spriteClips[1].x = 0;
        spriteClips[1].y = 200;
        spriteClips[1].w = BUTTON_WIDTH;
        spriteClips[1].h = BUTTON_HEIGHT;

        spriteClips[2].x = 0;
        spriteClips[2].y = 400;
        spriteClips[2].w = BUTTON_WIDTH;
        spriteClips[2].h = BUTTON_HEIGHT;

        spriteClips[3].x = 0;
        spriteClips[3].y = 600;
        spriteClips[3].w = BUTTON_WIDTH;
        spriteClips[3].h = BUTTON_HEIGHT;
    }

    return loadMediaSuccessful;
}

void Button::Free() {
    buttonSpriteSheetTexture.Free();
}