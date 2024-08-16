#ifndef LTEXURE_H
#define LTEXTURE_H

typedef struct SDL_Texture SDL_Texture;

class LTexture {
    public:
        LTexture();

        ~LTexture();

        bool LoadFromFile(const char*);

        void Free();

        // Render texture at a given (x,y) point
        void Render(int, int);

        int GetWidth();
        int GetHeight();

    private:
        SDL_Texture* texture;

        // Image dimensions
        int width;
        int height;
};

#endif