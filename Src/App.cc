#include "JadeButton.hpp"
#include "JadeColors.hpp"
#include "JadeTexture.hpp"
#include "JadeWindow.hpp"
#include "SDL3/SDL_rect.h"
#include "SDL3/SDL_render.h"
#include "SDL3_ttf/SDL_ttf.h"
#include <string>

JTexture tex;
TTF_Font* font;
float mWidth;

void render_text(SDL_Renderer* r, std::string text);

void handle_button(JadeButton* p, SDL_Renderer* r) {
    p->SetDisabled(true);
    render_text(r, "Downloading...");
}

void main_render(SDL_Renderer* r) {
    tex.Draw(r, (420 - tex.GetW()) / 2.0f , 35);
}

void render_text(SDL_Renderer* r, std::string text) {
    font = TTF_OpenFont("C:/Windows/Fonts/segoeui.ttf", 26);
    tex.LoadFromText(font, text, JadeColors::White, r);
}

int main() {
    JadeWindow ui("Test", 400, 200);
    SDL_FRect rectangle;
    rectangle.h = 40;
    rectangle.w = 130;
    rectangle.x = 150;
    rectangle.y = 100;
    mWidth = rectangle.w;

    render_text(ui.renderer, "Click download to start.");

    JadeButton button;
    button.rectangle = &rectangle;
    button.text = "Download";
    button.func = handle_button;

    ui.AddButton(button);
    ui.Start(main_render);
}