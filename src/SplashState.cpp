#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <sstream>

namespace BubbleBash
{
    SplashState::SplashState(GameDataRef data) : _data(data){}
    void SplashState::Init()
    {
        this->_data->assets.LoadTexture("SplashStateBackGround",SPLASH_STATE_FILEPATH);
        _background.setTexture(this->_data->assets.GetTexture("SplashStateBackGround"));
    }

    void SplashState::HandleInput()
    {
        sf::Event e;
        while(this->_data->window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
            {
                this->_data->window.close();
            }
        }
    }

    void SplashState::Update(float dt)
    {
        if(this->_clock.getElapsedTime().asSeconds()>SPLASH_STATE_SHOW_TIME)
        {std::cout<<"Go to Main Menu"<<std::endl;}
    }

    void SplashState::Draw(float dt)
    {
        this->_data->window.clear();
        this->_data->window.draw(this->_background);
        this->_data->window.display();
    }

}