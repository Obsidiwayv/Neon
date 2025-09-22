#ifndef JADEBUTTON_HPP_
#define JADEBUTTON_HPP_

#include "JadeComponent.hpp"
#include "JadeTexture.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <functional>

class JadeButton : public JadeComponent {
public:
    JComponentType cType = JComponentType::BUTTON;

    SDL_FRect* rectangle{};
    const char* text {};
    std::function<void(JadeButton*, SDL_Renderer*)> func{};

    ~JadeButton();
    
    JTexture tex;
    TTF_Font* font{nullptr};

    void DrawText(SDL_Renderer* renderer);

    void Draw(SDL_Renderer *renderer);
    void HandleEvent(SDL_Event event, SDL_Renderer* renderer);
    void SetPos(int x, int y);
    void SetDisabled(bool mode);
private:
    bool disabled = false;
};

#endif // JADEBUTTON_HPP_