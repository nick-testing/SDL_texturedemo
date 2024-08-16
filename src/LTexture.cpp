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

/**
 * Loads texture from received file path
 * 
 * \param renderer the rendering context
 * \param path image file path
 * \return true on successful texture load, false on failure
 */
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

/**
 * Sets rendering area at given (x, y) coordinate, renders texture to screen
 * 
 * \param renderer the rendering context
 * \param x the x coordinate of the top left corner
 * \param y the y coordinate of the top left corner
 */
void LTexture::Render(SDL_Renderer* renderer, int x, int y) {
    SDL_Rect renderArea = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, NULL, &renderArea); 
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