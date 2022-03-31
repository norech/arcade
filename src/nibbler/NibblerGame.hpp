/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** NibblerGame
*/

#ifndef NIBBLERGAME_HPP_
#define NIBBLERGAME_HPP_

#include <vector>

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

            void initMap();
            void drawMap();
            void movePlayer();
            void collision();
            void tailPosition();
            void drawTail();

        protected:
        private:
            grph::Palette _palette;
            std::shared_ptr<grph::ICanvas> _canvas;
            grph::IGraphic* _graphic;
            bool _mustLoadAnotherGraphic = false;
            int _playerX = 0;
            int _playerY = 0;
            int _score = 0;
            int _velocityX = 0;
            int _velocityY = 0;
            int _move = 0;
            int _turn = 0;
            std::vector<std::string> _map;
            std::vector<std::vector<int>> _position;
    };
}

#endif /* !NIBBLERGAME_HPP_ */
