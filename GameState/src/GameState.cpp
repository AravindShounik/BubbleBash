#include "GameState.hpp"
#include <iostream>
#include <sstream>


namespace BubbleBash
{
    GameState::GameState(GameDataRef data) : _data(data)
    {
    }

    void GameState::Init()
    {
        gameState = STATE_PLAYING;

        this->_data->assets.LoadTexture("Background", GAME_WINDOW_STATE_FILEPATH);
        this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);

        this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON_FILEPATH);
        this->_data->assets.LoadTexture("Help Button", HELP_BUTTON_FILEPATH);
        
        _background.setTexture(this->_data->assets.GetTexture("Background"));
        _gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

        _pausebutton.setTexture(this->_data->assets.GetTexture("Pause Button"));
        _helpbutton.setTexture(this->_data->assets.GetTexture("Help Button"));
       

        _gridSprite.setPosition(500, 200);

        _pausebutton.setPosition(50,400);
        _helpbutton.setPosition(50,500);

        if (!font.loadFromFile(MARKER_FONT_FILEPATH))
        {
            throw("COULD NOT LOAD FONT");
        }

        text_time.setFont(font);
        text_time.setCharacterSize(35);
        text_time.setColor(sf::Color::Yellow);
        text_time.setPosition(50, 100);

        text_score.setFont(font);
        text_score.setCharacterSize(35);
        text_score.setColor(sf::Color::Yellow);
        text_score.setPosition(50, 155);

        text_time.setString("Time Remaining : ");
        text_score.setString("Current Score : ");
    }

    void GameState::HandleInput()
    {
        sf::Event event;

        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->window.close();
            }

            else if (this->_data->input.IsSpriteClicked(this->_pausebutton, sf::Mouse::Left, this->_data->window))
            {
                std::cout << "Go to Pause State" << std::endl;
            }
            else if (this->_data->input.IsSpriteClicked(this->_helpbutton, sf::Mouse::Left, this->_data->window))
            {
                this->_data->machine.AddState(StateRef(new HelpState(_data)), true);
            }
        }
    }

    void GameState::Update(float dt)
    {
    }

    void GameState::Draw(float dt)
    {
        this->_data->window.clear(sf::Color::Black);

        this->_data->window.draw(this->_background);
        this->_data->window.draw(this->_gridSprite);

        this->_data->window.draw(this->_pausebutton);
        this->_data->window.draw(this->_helpbutton);

        this->_data->window.draw(text_time);
        this->_data->window.draw(text_score);

        this->_data->window.display();
    }
}
