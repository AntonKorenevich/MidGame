#pragma once
#include "Utilities/Utils.h"
#include "Utilities/InputControls.h"
#include "AIBoard.h"

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

	void OnLeftBtnPressed(sf::Vector2i vi);
	void OnMouseMoved(sf::Vector2i vi);
	void OnLeftBtnReleased(sf::Vector2i vi);

private:
	sf::RenderWindow& m_window;
	AIBoard			m_board;
	InputControls	m_ic;

	bool			m_drugging;
	sf::Vector2i	m_mousePosition;

	sf::Clock		m_aiClock;
};