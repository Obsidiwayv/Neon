#include "JadeTexture.hpp"
#include "SDL3/SDL_error.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_surface.h"
#include "SDL3_image/SDL_image.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <cstring>
#include <string>

JTexture::~JTexture()
{
    Destroy();
}

bool JTexture::Load(std::string path, SDL_Renderer* renderer)
{
    Destroy();

    SDL_Surface* lSurface = IMG_Load(path.c_str());
    SDL_SetSurfaceColorKey(lSurface, true, SDL_MapSurfaceRGB(lSurface, 0, 255, 255));
    mTex = SDL_CreateTextureFromSurface(renderer, lSurface);

    if (mTex == nullptr) {
        width = lSurface->w;
        height = lSurface->h;
    }

    SDL_DestroySurface(lSurface);
    return mTex != nullptr;
}

bool JTexture::LoadFromText(TTF_Font* font, std::string tText, SDL_Color tColor, SDL_Renderer* renderer)
{
    Destroy();

    SDL_Surface* lSurface = TTF_RenderText_Solid(font, tText.data(), strlen(tText.c_str()), tColor);

    if (lSurface == nullptr) {
        SDL_Log("unable to render text");
    }

    this->width = lSurface->w;
    this->height = lSurface->h;
    mTex = SDL_CreateTextureFromSurface(renderer, lSurface);

    if (mTex == nullptr) {
        SDL_Log("Cannot create texture from text");
    }

    SDL_DestroySurface(lSurface);
    TTF_CloseFont(font);
    return mTex != nullptr;
}

void JTexture::SetRGB(Uint8 r, Uint8 g, Uint8 b)
{
    SDL_SetTextureColorMod(mTex, r, g, b);
}

void JTexture::SetAlpha(Uint8 a)
{
    SDL_SetTextureAlphaMod(mTex, a);
}

void JTexture::SetBlend(SDL_BlendMode blend)
{
    SDL_SetTextureBlendMode(mTex, blend);
}

void JTexture::Draw(
    SDL_Renderer* renderer,
    float x,
    float y,
    SDL_FRect* clip,
    float w,
    float h,
    double degrees,
    SDL_FPoint* center,
    SDL_FlipMode flipMode)
{

    SDL_FRect dstRect;
    dstRect.w = width;
    dstRect.h = height;
    dstRect.x = x;
    dstRect.y = y;

    if (clip != nullptr) {
        dstRect.w = clip->w;
        dstRect.h = clip->h;
    }

    if (!SDL_RenderTexture(renderer, mTex, NULL, &dstRect)) {
        SDL_Log("Could not render texture %s", SDL_GetError());
    };
}

int JTexture::GetW()
{
    return width;
}

int JTexture::GetH()
{
    return height;
}

bool JTexture::Loaded()
{
    return mTex != nullptr;
}

void JTexture::Destroy()
{
    //width = 0;
    //height = 0;
}