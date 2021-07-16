#include"MainmenuState.hpp"
#include <iostream>
#include <sstream>

namespace BubbleBash
{
	MainmenuState::MainmenuState(GameDataRef data) : _data(data)
	{

	}

	void MainmenuState::Init()
	{
		this->_data->assets.LoadTexture("Background", MAIN_MENU_STATE_FILEPATH);		
		this->_data->assets.LoadTexture("PLAY", PLAY_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("HELP", HELP_BUTTON_FILEPATH);
		this->_data->assets.LoadTexture("EXIT", EXIT_BUTTON_FILEPATH);
		
		


		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_playbutton.setTexture(this->_data->assets.GetTexture("PLAY"));
		this->_helpbutton.setTexture(this->_data->assets.GetTexture("HELP"));
		this->_exitbutton.setTexture(this->_data->assets.GetTexture("EXIT"));




		this->_playbutton.setPosition(460,275);
		this->_helpbutton.setPosition(453,355);
		this->_exitbutton.setPosition(457,435);



		}

	void MainmenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
	

			else if (this->_data->input.IsSpriteClicked(this->_playbutton, sf::Mouse::Left, this->_data->window))
			{
				// Switch To Level State
				this->_data->machine.AddState(StateRef(new LevelState(_data)), true);
			}
			else if (this->_data->input.IsSpriteClicked(this->_helpbutton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new HelpState(_data)), true);
			}
			else if (this->_data->input.IsSpriteClicked(this->_exitbutton, sf::Mouse::Left, this->_data->window))
			{
				this->_data->window.close();
			}
		}
	}

	void MainmenuState::Update(float dt)
	{

	}

	void MainmenuState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_playbutton);
		this->_data->window.draw(this->_helpbutton);
		this->_data->window.draw(this->_exitbutton);

		this->_data->window.display();
	}
}