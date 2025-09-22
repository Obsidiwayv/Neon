#include "JadeProgress.hpp"
#include "JadeColors.hpp"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"

void JadeProgressBar::Draw(SDL_Renderer* renderer) {
    JadeColors::Set(renderer, JadeColors::Lavender);
    SDL_FRect rect;
    rect.h = 10;
    rect.w = size;
    rect.x = pos.x;
    rect.y = pos.y;

    SDL_RenderRect(renderer, &rect);
}