#include "JadeWindow.hpp"
#include "JadeButton.hpp"
#include "JadeStructs.hpp"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_messagebox.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_video.h"
#include "SDL3_ttf/SDL_ttf.h"

JadeWindow::JadeWindow(const char* title, int width, int height)
{
    window = SDL_CreateWindow(title, width, height, 0);
    renderer = SDL_CreateRenderer(window, "direct3d11");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        Throw("SDL3 main renderer could not start");
    }
    if (!TTF_Init()) {
        Throw("SDL3 font renderer could not start");
    }

    wSize = WindowSize { width, height };
}

void JadeWindow::Throw(const char* reason)
{
    will_start = false;

    const SDL_MessageBoxButtonData msgBox_buttons[] {
        { 0, 0, "Okay" }
    };
    const SDL_MessageBoxData msgBox = {
        SDL_MESSAGEBOX_ERROR,
        NULL,
        "Startup Error",
        reason,
        SDL_arraysize(msgBox_buttons),
        msgBox_buttons,
        NULL
    };
    SDL_ShowMessageBox(&msgBox, NULL);
}

void JadeWindow::Start(std::function<void(SDL_Renderer* r)> main_render)
{
    if (will_start) {
        for (JadeButton& button : buttons) {
            button.DrawText(renderer);
        }
        while (is_active) {
            SDL_Event event;

            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_EVENT_QUIT) {
                    is_active = false;
                }
                for (JadeButton& button : buttons) {
                    button.HandleEvent(event, renderer);
                }
            }
            SDL_SetRenderDrawColor(renderer, 40, 40, 40, 0xFF);
            SDL_RenderClear(renderer);

            for (JadeButton& button : buttons) {
                button.Draw(renderer);
            }

            main_render(renderer);

            SDL_RenderPresent(renderer);
        }
    }
}

void JadeWindow::AddButton(JadeButton button)
{
    buttons.push_back(button);
}

void JadeWindow::AddProgressBar(JadeProgressBar pBar) {
    progressBars.push_back(pBar);
}

JadeWindow::~JadeWindow()
{
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}