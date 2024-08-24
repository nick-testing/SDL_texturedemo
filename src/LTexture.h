#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL2/SDL_stdinc.h>    // Uint8
#include <SDL2/SDL_blendmode.h> // SDL_BlendMode
#include <SDL2/SDL_render.h>    // SDL_RendererFlip

typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Rect SDL_rect;
typedef struct SDL_Color SDL_Color;
typedef struct _TTF_Font TTF_Font;

class LTexture 
{
    public:
        LTexture();

        ~LTexture();

        /**
         * @brief Loads texture from received file path
         * 
         * @param renderer the rendering context
         * @param path image file path
         * @return true on successful texture load, false on failure
         */
        bool LoadFromFile(SDL_Renderer* renderer, const char* path);

        #if defined(SDL_TTF_MAJOR_VERSION)
        /**
         * @brief Creates image from a font string
         * 
         * @param renderer the rendering context
         * @param textureText the text to be rendered
         * @param textColor the color of the text
         * @return true on success, false on failure
         */
        bool LoadFromRenderedText(SDL_Renderer* renderer, const char* textureText, SDL_Color textColor);
        #endif
        
        /**
         * @brief Sets rendering area at given (x, y) coordinate, renders texture to screen
         * 
         * @param renderer the rendering context
         * @param x the x coordinate of the top left corner
         * @param y the y coordinate of the top left corner
         * @param clip Optional SDL_Rect structre that will serve as a
         *             cropping rectangle for a sprite sheet
         */
        void Render(SDL_Renderer* renderer, 
                    int x,
                    int y, 
                    SDL_Rect* clip = nullptr, 
                    double angle = 0.0f, 
                    SDL_Point* center = nullptr, 
                    SDL_RendererFlip flip = SDL_FLIP_NONE);
        
        /**
         * @brief 
         * Allows altering the color of rendered texture AKA color modulation
         * 
         * Each of color channel value is modulated using the 
         * following formula:
         * `srcC = srcC * (color / 255)`
         * 
         * @param red Red color value in ranges 0x00-0xFF
         * @param green Green color value in ranges 0x00-0xFF
         * @param blue Blue color value in ranges 0x00-0xFF
         */
        void SetColor(Uint8 red, Uint8 green, Uint8 blue);

        /**
         * @brief Sets the blend mode for the texture
         * 
         * @param blendMode the SDL_BlendMode to use for texture rendering
         */
        void SetBlendMode(SDL_BlendMode blendMode);
        
        /**
         * @brief 
         * Sets the alpha value modifier used for rendering the image
         * 
         * Uses the following formula:
         * 
         * srcA = srcA * (alpha / 255)
         * 
         * @param alpha the alpha value multipled into the rendering operation
         */
        void SetAlpha(Uint8 alpha);

        /**
         * Frees texture if texture exists
         */
        void Free();
        
        int GetWidth();
        int GetHeight();
    private:
        SDL_Texture* texture;
        TTF_Font* textureFont;

        // Image dimensions
        int width;
        int height;
};

#endif