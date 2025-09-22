#pragma once

#include "JadeProgress.hpp"
#include "JadeStructs.hpp"
#include <functional>
#ifndef JADEWINDOW_HPP_
#define JADEWINDOW_HPP_

#include "JadeButton.hpp"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_video.h"
#include <vector>

class JadeWindow {
public:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    bool is_active = true;
    bool will_start = true;

    JadeWindow(const char* title, int width, int height);
    void AddButton(JadeButton button);
    void AddProgressBar(JadeProgressBar pBar);
    void Start(std::function<void(SDL_Renderer* r)> main_render);
    void Throw(const char* reason);
    ~JadeWindow();
    WindowSize wSize;

private:
    std::vector<JadeButton> buttons;
    std::vector<JadeProgressBar> progressBars;
};

#endif // JADEWINDOW_HPP_