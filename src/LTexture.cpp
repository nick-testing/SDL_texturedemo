#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

LTexture::LTexture() : width(0), height(0), texture(nullptr) {}

LTexture::~LTexture() {
    Free();
}