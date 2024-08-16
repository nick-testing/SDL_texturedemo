#ifndef LTEXURE_H
#define LTEXTURE_H

typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;

class LTexture {
    public:
        LTexture();

        ~LTexture();

        bool LoadFromFile(SDL_Renderer&, const char*);

        // Render texture at a given (x,y) point
        void Render(SDL_Renderer&, int, int);

        // Deallocate memory
        void Free();

        int GetWidth();
        int GetHeight();
    private:
        SDL_Texture* texture;

        // Image dimensions
        int width;
        int height;
};

#endif