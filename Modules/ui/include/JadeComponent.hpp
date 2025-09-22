#ifndef JADECOMPONENT_HPP_
#define JADECOMPONENT_HPP_

#include "SDL3/SDL_render.h"

enum JComponentType {
    BUTTON,
    PROGRESS_BAR
};

class JadeComponent {
    public: 
        JComponentType cType;
        virtual ~JadeComponent() = default;

        virtual void Draw(SDL_Renderer* renderer) {};
        virtual void HandleEvent(SDL_Event event) {};
        virtual void DrawText(SDL_Renderer* renderer) {};
};

#endif // JADECOMPONENT_HPP_