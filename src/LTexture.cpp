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
    // Free previously held texture
    Free();
    
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (!loadedSurface) {
        std::cerr << "Image loading failed, SDL error: " << SDL_GetError() << std::endl;
    }
    else {
        // Set the color key(transparent pixel color) in the loaded surface
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, COLOR_CHANNEL_MIN, 
                        COLOR_CHANNEL_MAX, COLOR_CHANNEL_MAX));

        // Create a texture from the color keyed loaded surface
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (!texture) {
            std::cerr << "Texture creation failed, SDL error: " << SDL_GetError() << std::endl;
        }
        else {
            // Set image dimensions for the texture
            width = loadedSurface->w;
            height = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    return texture;
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