#include"LevelState.hpp"
#include <iostream>
#include <sstream>
#include "GameState.hpp"

namespace BubbleBash
{
	LevelState::LevelState(GameDataRef data) : _data(data)
	{

	}

	void LevelState::Init()
	{
		this->_data->assets.LoadTexture("Background", LEVEL_STATE_FILEPATH);		
		this->_data->assets.LoadTexture("EASY", EASY_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("MEDIUM", MEDIUM_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("HARD", HARD_BUTTON_FILEPATH);
		
		


		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_easybutton.setTexture(this->_data->assets.GetTexture("EASY"));
		this->_mediumbutton.setTexture(this->_data->assets.GetTexture("MEDIUM"));
		this->_hardbutton.setTexture(this->_data->assets.GetTexture("HARD"));




		this->_easybutton.setPosition(450,275);
		this->_mediumbutton.setPosition(453,355);
		this->_hardbutton.setPosition(453,435);


		if(!font.loadFromFile(MARKER_FONT_FILEPATH))
        {
            throw("COULD NOT LOAD FONT");
        }

		title.setFont(font);
        title.setCharacterSize(80);
        title.setColor(sf::Color::Magenta);
        title.setPosition(320,20);


        title.setString("SELECT LEVEL");




		}

	void LevelState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
	

			else if (this->_data->input.IsSpriteClicked(this->_easybutton, sf::Mouse::Left, this->_data->window))
			{
				// Switch To Game State (easy level)
				this->_data->machine.AddState(StateRef(new GameState(_data)), true);
			}
			else if (this->_data->input.IsSpriteClicked(this->_mediumbutton, sf::Mouse::Left, this->_data->window))
			{
				// Switch to medium level
				std :: cout << "medium level" << std ::endl;

			}
			else if (this->_data->input.IsSpriteClicked(this->_hardbutton, sf::Mouse::Left, this->_data->window))
			{
				// Switch to hard level
				std :: cout << "hard level" << std ::endl;
			}
		}
	}

	void LevelState::Update(float dt)
	{

	}

	void LevelState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Blue);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_easybutton);
		this->_data->window.draw(this->_mediumbutton);
		this->_data->window.draw(this->_hardbutton);
		this->_data->window.draw(title);

		this->_data->window.display();
	}
}