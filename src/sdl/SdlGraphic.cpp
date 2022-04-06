//
// EPITECH PROJECT, 2022
// arcade
// File description:
// sdlgraphic
//

#include "SdlGraphic.hpp"
#include "SdlCanvas.hpp"

namespace arc::grph {

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
        _size_x, _size_y, windowFlag, &_window, &_renderer);
    if (_window == NULL) {
        std::cerr << SDL_GetError() << std::endl;
        std::exit(84);
    }
    SDL_SetWindowTitle(_window, "SDL");
    SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0");
    TTF_Init();
    _font = TTF_OpenFont("./font.ttf", 20);

    if (_renderer == NULL) {
        std::cerr << SDL_GetError() << std::endl;
        std::exit(84);
    }
}

void SdlGraphic::close() { _shouldClose = true; }

void SdlGraphic::clear()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
}

void SdlGraphic::render()
{
    SDL_RenderPresent(_renderer);
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
            switch (event.key.keysym.sym) {
            case SDLK_DOWN:
                input.type = Event::KEYDOWN;
                input.keyboardInput.keyCode = KeyCode::S;
                return (true);
            case SDLK_UP:
                input.type = Event::KEYDOWN;
                input.keyboardInput.keyCode = KeyCode::Z;
                return (true);
            case SDLK_LEFT:
                input.type = Event::KEYDOWN;
                input.keyboardInput.keyCode = KeyCode::Q;
                return (true);
            case SDLK_RIGHT:
                input.type = Event::KEYDOWN;
                input.keyboardInput.keyCode = KeyCode::D;
                return (true);
            case SDLK_RETURN:
                input.type = Event::KEYDOWN;
                input.keyboardInput.keyCode = KeyCode::I;
                return (true);
            case SDLK_SPACE:
                input.type = Event::KEYDOWN;
                input.keyboardInput.keyCode = KeyCode::U;
                return (true);
            default:
                break;
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
    TTF_CloseFont(_font);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
    _window = nullptr;
}

float SdlGraphic::tick() { return (0.025); }

void SdlGraphic::registerSprite(game::ISprite& sprite [[maybe_unused]])
{
    return;
}

}
