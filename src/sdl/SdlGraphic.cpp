//
// EPITECH PROJECT, 2022
// arcade
// File description:
// sdlgraphic
//

#include "SdlGraphic.hpp"
#include "SdlCanvas.hpp"

namespace arc::grph {

// clang-format off
std::unordered_map<int, arc::KeyCode> SdlGraphic::_keyMap
    = {
        { SDLK_RETURN, arc::KeyCode::ENTER },
        { SDLK_BACKSPACE, arc::KeyCode::BACKSPACE },
        { SDLK_UP, arc::KeyCode::Z },
        { SDLK_DOWN, arc::KeyCode::S },
        { SDLK_LEFT, arc::KeyCode::Q },
        { SDLK_RIGHT, arc::KeyCode::D },
        { SDLK_SPACE, arc::KeyCode::SPACE }
    };
// clang-format on

SdlGraphic::SdlGraphic()
    : _name("arcade")
    , _size_x(800)
    , _size_y(600)
{
}

SdlGraphic::~SdlGraphic() { }

void SdlGraphic::init()
{
    int windowFlag = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "error init SDL" << std::endl;
        std::exit(84);
    }
    _shouldClose = false;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_CreateWindowAndRenderer(
        _size_x, _size_y, windowFlag, &window, &renderer);
    if (window == NULL) {
        std::cerr << SDL_GetError() << std::endl;
        std::exit(84);
    }
    SDL_SetWindowTitle(window, "SDL");
    // SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
    TTF_Init();
    font = TTF_OpenFont("./font.ttf", 20);

    if (renderer == NULL || font == NULL) {
        std::cerr << SDL_GetError() << std::endl;
        std::exit(84);
    }
}

void SdlGraphic::close() { _shouldClose = true; }

void SdlGraphic::clear()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SdlGraphic::render()
{
    SDL_RenderPresent(renderer);
    SDL_Delay(25);
}

bool SdlGraphic::pollEvent(Event& input [[maybe_unused]])
{
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            input.type = Event::QUIT;
            return (true);
        }
        if (event.type == SDL_KEYDOWN) {
            for (auto& it : _keyMap) {
                if (it.first == event.key.keysym.sym) {
                    input.type = Event::KEYDOWN;
                    input.keyboardInput.keyCode = it.second;
                    return (true);
                }
            }
            if (event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z') {
                input.type = Event::KEYDOWN;
                input.keyboardInput.keyCode = event.key.keysym.sym;
                return (true);
            }
        }
    }
    return (false);
}

bool SdlGraphic::isOpen()
{
    if (_shouldClose)
        return (false);
    if (window == NULL) {
        return (false);
    } else {
        return (true);
    }
}

void SdlGraphic::loadCanvas(std::shared_ptr<ICanvas>& canvas [[maybe_unused]])
{
    canvas.reset(new SdlCanvas(this));
}

void SdlGraphic::unloadCanvas(std::shared_ptr<ICanvas>& canvas [[maybe_unused]])
{
    canvas.reset();
}

void SdlGraphic::destroy()
{
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    window = nullptr;
}

float SdlGraphic::tick() { return (0.025); }

}
