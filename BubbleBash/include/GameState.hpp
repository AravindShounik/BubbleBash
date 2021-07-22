#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "DEFINITIONS.hpp"



namespace BubbleBash
{
    static struct Timer
    {
        int runTime;
        bool bPaused;
        sf::Clock mC;

        Timer()
        {
            bPaused = false;
            runTime = 0;
        }

        void Start()
        {
            if (bPaused)
            {
                mC.restart();
            }
            bPaused = false;
        }

        void Pause()
        {
            if (!bPaused)
            {
                runTime += mC.getElapsedTime().asSeconds();
            }
            bPaused = true;
        }

        int GetElapsedSeconds()
        {
            if (!bPaused)
            {
                return runTime + mC.getElapsedTime().asSeconds();
            }
            return runTime;
        }
    }obj;

    class GameState : public State
    {
    public:
        GameState(GameDataRef data,int i);

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

        sf::Text text_time, time_text;
        sf::Text text_score;

        
        int time,level;

        std::string string_time;
    };
}