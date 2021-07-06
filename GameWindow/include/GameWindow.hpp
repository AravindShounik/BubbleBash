#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace BubbleBash
{
	class GameWindow : public State
	{
	public:
		GameWindow(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Sprite _background;

    };
}