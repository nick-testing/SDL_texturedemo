#ifndef LTEXURE_H
#define LTEXTURE_H

typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Rect SDL_rect;

class LTexture {
    public:
        LTexture();

        ~LTexture();

        bool LoadFromFile(SDL_Renderer* renderer, const char* path);

        void Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr);

        void SetColor(Uint8 red, Uint8 green, Uint8 blue);

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