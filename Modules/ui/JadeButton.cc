#include "JadeButton.hpp"
#include "JadeColors.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_mouse.h"
#include "SDL3/SDL_pixels.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <string>

struct MouseMovement {
    float x;
    float y;
};

// Default color for this button
SDL_Color color = JadeColors::Charcoal;

void JadeButton::Draw(SDL_Renderer* renderer)
{

    if (disabled) {
        color = JadeColors::OuterSpace;
        tex.SetRGB(65, 74, 76); // JadeColors::OuterSpace
    }
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderRect(renderer, this->rectangle);
    tex.Draw(renderer,
        rectangle->x + (rectangle->w - tex.GetW()) / 2.0f,
        rectangle->y + (rectangle->h - tex.GetH()) / 2.0f);
}

void JadeButton::DrawText(SDL_Renderer* renderer)
{
    font = TTF_OpenFont("C:/Windows/Fonts/segoeui.ttf", 24);
    if (font == nullptr) {
        SDL_Log("Could not load font");
    }

    if (!tex.LoadFromText(font, text, JadeColors::White, renderer)) {
        SDL_Log("Could not load texture");
    }
}

void JadeButton::HandleEvent(SDL_Event event, SDL_Renderer* renderer)
{
    if (!disabled) {
        if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            MouseMovement movement;
            SDL_GetMouseState(&movement.x, &movement.y);

            bool inside = true;

            if (movement.x < rectangle->x
                || movement.x > rectangle->x + rectangle->w
                || movement.y < rectangle->y
                || movement.y > rectangle->y + rectangle->h)
                inside = false;

            if (inside) {
                color = JadeColors::Lavender;
                func(this, renderer);
            }
        } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
            color = JadeColors::Charcoal;
        }
    }
}

void JadeButton::SetDisabled(bool mode)
{
    disabled = mode;
}

JadeButton::~JadeButton()
{
    tex.Destroy();
    TTF_CloseFont(font);
}