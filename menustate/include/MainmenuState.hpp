#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace BubbleBash
{
	class MainmenuState : public State
	{
	public:
		MainmenuState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;

		sf::Sprite _playbutton;

		sf::Sprite _helpbutton;

		sf::Sprite _exitbutton;

		
	};
}