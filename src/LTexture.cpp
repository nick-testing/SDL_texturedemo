#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#define COLOR_CHANNEL_MAX (0xFF)
#define COLOR_CHANNEL_MIN (0x00)

LTexture::LTexture() : width(0), height(0), texture(nullptr) {}

LTexture::~LTexture() {
    Free();
}

bool LTexture::LoadFromFile(SDL_Renderer* renderer, const char* path) {

}

void LTexture::Render(SDL_Renderer* renderer, int x, int y) {

}

int LTexture::GetWidth() {
    return width;
}

int LTexture::GetHeight() {
    return height;
}

/**
 * Frees texture if texture exists
 */
void LTexture::Free() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0; 
    }
}