#ifndef JADEPROGRESS_HPP_
#define JADEPROGRESS_HPP_

#include "JadeComponent.hpp"
#include "JadeStructs.hpp"
#include "SDL3/SDL_render.h"

class JadeProgressBar : public JadeComponent {
    public:
        JComponentType cType = JComponentType::PROGRESS_BAR;
        int size{};
        int currentProg = 0;
        Vector2 pos;

        void Draw(SDL_Renderer* renderer) override;
        void CountEvent(int cur);
};

#endif // JADEPROGRESS_HPP_