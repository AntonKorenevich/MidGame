#pragma once
#include "Utilities/Utils.h"
#include "Utilities/InputControls.h"

class Player;

class Game
{
public:
	Game(sf::RenderWindow& rw);
	~Game();
	void Update(float dt);
	void Draw();

	void KeyPressed(sf::Keyboard::Scancode sc);
	void KeyReleased(sf::Keyboard::Scancode sc);

private:
	sf::RenderWindow& m_window;
	std::unique_ptr<Player> m_player;
	InputControls m_ic;
};