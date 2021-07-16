#include "PauseState.hpp"
#include <iostream>
#include <sstream>
#include "GameState.hpp"

namespace BubbleBash
{
    PauseState::PauseState(GameDataRef data) : _data(data)
    {
    }

    void PauseState::Init()
    {
        this->_data->assets.LoadTexture("Background", PAUSE_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("RESUME", RESUME_BUTTON_FILEPATH);
        this->_data->assets.LoadTexture("RESTART", RESTART_BUTTON_FILEPATH);
        this->_data->assets.LoadTexture("EXIT", EXIT_BUTTON_FILEPATH);

        this->_background.setTexture(this->_data->assets.GetTexture("Background"));
        this->_resumebutton.setTexture(this->_data->assets.GetTexture("RESUME"));
        this->_restartbutton.setTexture(this->_data->assets.GetTexture("RESTART"));
        this->_exitbutton.setTexture(this->_data->assets.GetTexture("EXIT"));

        this->_resumebutton.setPosition(460, 270);
        this->_restartbutton.setPosition(453, 350);
        this->_exitbutton.setPosition(457, 430);
    }

    void PauseState::HandleInput()
    {
        sf::Event event;

        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }

            else if (this->_data->input.IsSpriteClicked(this->_resumebutton, sf::Mouse::Left, this->_data->window))
            {
                // Resume Game By Popping Of The Current State (Pause State)
                this->_data->machine.RemoveState();
            }
            else if (this->_data->input.IsSpriteClicked(this->_restartbutton, sf::Mouse::Left, this->_data->window))
            {
                    this->_data->machine.AddState(StateRef(new GameState(_data)), true);
            }
            else if (this->_data->input.IsSpriteClicked(this->_exitbutton, sf::Mouse::Left, this->_data->window))
            {
                this->_data->window.close();
            }
        }
    }

    void PauseState::Update(float dt)
    {
    }

    void PauseState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Red);

        this->_data->window.draw(this->_background);
        this->_data->window.draw(this->_resumebutton);
        this->_data->window.draw(this->_restartbutton);
        this->_data->window.draw(this->_exitbutton);

        this->_data->window.display();
    }
}