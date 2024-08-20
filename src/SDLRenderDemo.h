#ifndef SDLRENDERDEMO_H
#define SDLRENDERDEMO_H

#include "LTexture.h"
#include "SDLProgram.h"
#include <SDL2/SDL_rect.h>

typedef struct SDL_Window SDL_Window;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;

typedef enum RenderMode {
    RENDER_DEFAULT,
    RENDER_RGB_MODULATION,
    RENDER_ALPHA_MODULATION,
    RENDER_ROTATION
} RenderMode;

class SDLRenderDemo : SDLProgram {
public:
    SDLRenderDemo();
    void Run() override;

private:
    LTexture defaultTexture;

    LTexture backgroundTexture;
    LTexture foregroundTexture;

    // Scene sprites
    LTexture spriteSheetTexture;

    // modulation test texture
    LTexture modulatedTexture;

    // Alpha blend textures
    LTexture fgAlphaTexture;
    LTexture bgAlphaTexture; 

    // Rotation texture
    LTexture rotationTexture;
    

    /**
     * Renders a texture with color modulation applied
     * 
     * \param renderer the rendering context
     * \param r red color value
     * \param g green color value
     * \param b blue color value
     */
    void RenderColorModulation(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b);

    /**
     * Renders the alpha modulation scene
     * 
     * \param renderer the rendering context
     * \param alpha alpha value used for modulating the texture
     */
    void RenderAlphaModulation(SDL_Renderer* renderer, Uint8 alpha);

    /**
     * Manually load all textures stored at the ./assets/ directory
     * 
     * \todo convert this to automatic loading
     */
    bool LoadMedia() override;


    void RenderLoop() override;
    void Close() override;
};

#endif