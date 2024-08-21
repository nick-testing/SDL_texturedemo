#include "LTexture.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

#define COLOR_CHANNEL_MAX (0xFF)
#define COLOR_CHANNEL_MIN (0x00)

LTexture::LTexture(TTF_Font* font) : width(0), height(0), texture(nullptr), textureFont(font) {}

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
        SDL_SetColorKey(loadedSurface,
                        SDL_TRUE,
                        SDL_MapRGB(loadedSurface->format, 
                                   COLOR_CHANNEL_MIN,
                                   COLOR_CHANNEL_MAX, 
                                   COLOR_CHANNEL_MAX));

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

bool LTexture::LoadFromRenderedText(SDL_Renderer* renderer, const char* textureText, SDL_Color textColor) {
    Free();

    SDL_Surface* textSurface = TTF_RenderText_Solid(textureFont, textureText, textColor);
    if (!textSurface) {
        std::cerr << "Surface creation failed, SDL error: " << SDL_GetError() << std::endl;
    }
    else {
        texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!texture) {
            std::cerr << "Texture creation failed, SDL error: " << SDL_GetError() << std::endl;
        }
        else {
            width = textSurface->w;
            height = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }

    return texture;
}

void LTexture::Render(SDL_Renderer* renderer, 
                      int x,
                      int y,
                      SDL_Rect* clip,
                      double angle, 
                      SDL_Point* center, 
                      SDL_RendererFlip flip) {
                        
    SDL_Rect renderArea = {x, y, width, height};
    
    // Set cropping rectangle dimensions
    if (clip) {
        renderArea.w = clip->w;
        renderArea.h = clip->h;
    }

    SDL_RenderCopyEx(renderer, texture, clip, &renderArea, angle, center, flip); 
}

void LTexture::SetColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(texture, red, green, blue);
}

void LTexture::SetBlendMode(SDL_BlendMode blendMode) {
    SDL_SetTextureBlendMode(texture, blendMode);
}

void LTexture::SetAlpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture, alpha);
}

int LTexture::GetWidth() {
    return width;
}

int LTexture::GetHeight() {
    return height;
}

void LTexture::SetFont(TTF_Font* font) {
    textureFont = font;
}

void LTexture::Free() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
        width = 0;
        height = 0; 
    }
    if (textureFont) {
        TTF_CloseFont(textureFont);
    }
}