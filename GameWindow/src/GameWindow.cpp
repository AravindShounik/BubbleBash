#pragma once

#include <sstream>
#include "GameWindow.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace BubbleBash
{
	GameWindow::GameWindow(GameDataRef data) : _data(data)
	{

	}

	void GameWindow::Init()
	{
		this->_data->assets.LoadTexture("Background", GAME_PLAY_FILEPATH);				
		


		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		

	}

	void GameWindow::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
	

		}
	}

	void GameWindow::Update(float dt)
	{

	}

	void GameWindow::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Blue);

		this->_data->window.draw(this->_background);
		
		this->_data->window.display();
	}
}