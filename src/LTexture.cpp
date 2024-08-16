#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

LTexture::LTexture() : width(0), height(0), texture(nullptr) {}

LTexture::~LTexture() {
    Free();
}

bool LTexture::LoadFromFile(const char* path) {

}

void LTexture::Render(int x, int y) {

}

int LTexture::GetWidth() {
    return width;
}

int LTexture::GetHeight() {
    return height;
}

void LTexture::Free() {
    SDL_DestroyTexture(texture);
}