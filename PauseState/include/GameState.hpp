#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"
#include "HelpState.hpp"
#include "PauseState.hpp"

namespace BubbleBash
{
    class GameState : public State
    {
    public:
        GameState(GameDataRef data);

        void Init();

        void HandleInput();
        void Update(float dt);
        void Draw(float dt);

    private:
        GameDataRef _data;

        sf::Sprite _background;

        sf::Sprite _gridSprite;

        sf::Sprite _pausebutton;

        sf::Sprite _helpbutton;

        sf::Font font;

        sf::Text text_time;
        sf::Text text_score;

        sf::Clock _clock;

        int gameState;
    };
}