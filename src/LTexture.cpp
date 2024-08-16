#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

LTexture::LTexture() : width(0), height(0), texture(nullptr) {}

LTexture::~LTexture() {
    Free();
}

bool LTexture::LoadFromFile(const SDL_Renderer& rederer, const char* path) {

}

void LTexture::Render(const SDL_Renderer& renderer, int x, int y) {

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