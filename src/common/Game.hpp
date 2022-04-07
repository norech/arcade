/*
** EPITECH PROJECT, 2022
** B-OOP-400-RUN-4-1-arcade-ludovic.peltier
** File description:
** Game
*/

#pragma once

#include "spc/game/IGame.hpp"

namespace arc::game {

    class AGame : public IGame {
        public:
            AGame() = default;
            ~AGame() = default;

            virtual void init() {};

            virtual void update(float dt [[maybe_unused]]) {};

            virtual void render() {};

            virtual void loadGraphic(grph::IGraphic* graphic [[maybe_unused]]) {};

            virtual void unloadGraphic() {};

            virtual void setManager(IManager* manager [[maybe_unused]]) {};

            virtual bool mustLoadAnotherGraphic() { return false;};

            virtual void destroy() {};

        protected:
        private:
    };
}