//
// EPITECH PROJECT, 2022
// arcade
// File description:
// sdlgraphic
//

#include "SdlGraphic.hpp"
#include "SdlCanvas.hpp"

namespace arc::grph {

SdlGraphic::SdlGraphic(
    std::string& name, int size_x [[maybe_unused]], int size_y [[maybe_unused]])
    : _name(name)
    , _size_x(800)
    , _size_y(600)
{
}

SdlGraphic::~SdlGraphic() { }

void SdlGraphic::init()
{
    int renderFlag = SDL_RENDERER_ACCELERATED;
    int windowFlag = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "error init SDL" << std::endl;
        std::exit(84);
    }
    _window = SDL_CreateWindow("arcade", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, _size_x, _size_y, windowFlag);
    if (_window == NULL) {
        std::cerr << SDL_GetError() << std::endl;
        std::exit(84);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    _renderer = SDL_CreateRenderer(_window, -1, renderFlag);
    if (_renderer == NULL) {
        std::cerr << SDL_GetError() << std::endl;
        std::exit(84);
    }
}

void SdlGraphic::close()
{
    SDL_Quit();
    _window = nullptr;
}

void SdlGraphic::clear()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void SdlGraphic::render() { SDL_RenderPresent(_renderer); }

bool SdlGraphic::pollEvent(Event& input [[maybe_unused]])
{
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            input.type = Event::QUIT;
            return (true);
        }
        if (event.type == SDL_KEYDOWN) {
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
    if (_window == NULL) {
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
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
    _window = nullptr;
}

float SdlGraphic::tick() { return (0); }
}
