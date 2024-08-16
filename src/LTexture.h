#ifndef LTEXURE_H
#define LTEXTURE_H

typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Rect SDL_rect;

class LTexture {
    public:
        LTexture();

        ~LTexture();

        bool LoadFromFile(SDL_Renderer*, const char*);

        void Render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr);

        void Free();

        int GetWidth();
        int GetHeight();
    private:
        SDL_Texture* texture;

        int width;
        int height;
};

#endif