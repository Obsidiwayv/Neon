#ifndef JADECOLORS_HPP_
#define JADECOLORS_HPP_

#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_render.h"

namespace JadeColors {

constexpr SDL_Color Lavender { 171, 158, 252, SDL_ALPHA_OPAQUE };
constexpr SDL_Color White { 255, 255, 255, SDL_ALPHA_OPAQUE };
constexpr SDL_Color Black { 0, 0, 0, SDL_ALPHA_OPAQUE };
constexpr SDL_Color Charcoal {  54, 69, 79, SDL_ALPHA_OPAQUE }; 
constexpr SDL_Color OuterSpace { 65, 74, 76, SDL_ALPHA_OPAQUE};

inline void Set(SDL_Renderer* r, SDL_Color color) {
    SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
};

}

#endif // JADECOLORS_HPP_