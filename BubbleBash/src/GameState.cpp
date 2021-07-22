#include "GameState.hpp"
#include "HelpState.hpp"
#include "PauseState.hpp"
#include <iostream>
#include <sstream>


namespace BubbleBash
{
    GameState::GameState(GameDataRef data,int i) : _data(data),level(i)
    {
    }

    void GameState::Init()
    {
        this->_data->assets.PauseOrGame_State.push_back(0);
        obj.mC.restart();
        obj.runTime =0;
        obj.bPaused = false;

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

        time_text.setFont(font);
        time_text.setCharacterSize(35);
        time_text.setColor(sf::Color::Yellow);
        time_text.setPosition(310, 100);

        this->_data->assets._music.openFromFile(GAME_PLAY_MUSIC_FILEPATH);
        this->_data->assets._music.setVolume(50);
        this->_data->assets._music.setLoop(true);
        this->_data->assets._music.play();

        
    }

    void GameState::HandleInput()
    {
        sf::Event event;

        while (this->_data->window.pollEvent(event))
        {
            if (sf::Event::Closed == event.type)
            {
                this->_data->assets._music.stop();
                this->_data->window.close();
            }

            else if (this->_data->input.IsSpriteClicked(this->_pausebutton, sf::Mouse::Left, this->_data->window))
            {
                obj.Pause();
                this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
            }
            else if (this->_data->input.IsSpriteClicked(this->_helpbutton, sf::Mouse::Left, this->_data->window))
            {
                this->_data->assets._music.stop();
                this->_data->machine.AddState(StateRef(new HelpState(_data)), true);
            }

            if (event.type == sf::Event::EventType::KeyPressed)
            {
                // Up and down to control volume
                if (event.key.code == sf::Keyboard::Down)
                    this->_data->assets._music.setVolume(_data->assets._music.getVolume() - 10);

                if (event.key.code == sf::Keyboard::Key::Up)
                    this->_data->assets._music.setVolume(_data->assets._music.getVolume() + 10);
            }
        }
    }

    void GameState::Update(float dt)
    {
        time = obj.GetElapsedSeconds();
        time = TIME_EASY - level*10 - time;
        std::stringstream ss;
        ss << time;
        time_text.setString(ss.str().c_str());

        if (this->_data->assets.PauseOrGame_State.back() == 1)
        {
            obj.Start();
            this->_data->assets.PauseOrGame_State.pop_back();
        }
        
        if (time < 0)
        {
            std::cout << "Go to EndGame state" << std::endl;
        }

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

        this->_data->window.draw(time_text);

        this->_data->window.display();
    }
}