#ifndef JADETEXTURE_HPP_
#define JADETEXTURE_HPP_

#include "SDL3/SDL_blendmode.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <string>

class JTexture {
public:
    ~JTexture();
    bool Load(std::string path, SDL_Renderer* renderer);
    bool LoadFromText(TTF_Font* font, std::string tText, SDL_Color tColor, SDL_Renderer* renderer);
    void SetRGB(Uint8 r, Uint8 g, Uint8 b);
    void SetAlpha(Uint8 alpha);
    void SetBlend(SDL_BlendMode mode);
    SDL_Texture* mTex;
    void Draw(
        SDL_Renderer* renderer,
        float x,
        float y,
        SDL_FRect* clip = nullptr,
        float w = -1.f,
        float h = -1.f,
        double degrees = 0.0,
        SDL_FPoint* center = nullptr,
        SDL_FlipMode flipMode = SDL_FLIP_NONE);
        int GetW();
        int GetH();
        bool Loaded();
        void Destroy();
        
        int width;
        int height;
private:
    bool success{true};
};

#endif // JADETEXTURE_HPP_