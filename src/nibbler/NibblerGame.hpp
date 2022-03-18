/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** NibblerGame
*/

#ifndef NIBBLERGAME_HPP_
#define NIBBLERGAME_HPP_

#include "../common/Palette.hpp"
#include "spc/game/IGame.hpp"
#include "spc/graphic/ICanvas.hpp"
#include "spc/graphic/IGraphic.hpp"

namespace arc::game {
    class NibblerGame : public IGame {
        public:
            NibblerGame();
            ~NibblerGame();

            void init() override;
            void update(float dt) override;
            void render() override;
            void loadGraphic(grph::IGraphic* graphic) override;
            void unloadGraphic() override;
            bool mustLoadAnotherGraphic() const override;
            void destroy() override;

        protected:
        private:
            grph::Palette _palette;
            std::shared_ptr<grph::ICanvas> _canvas;
            grph::IGraphic* _graphic;
    };
}

#endif /* !NIBBLERGAME_HPP_ */
