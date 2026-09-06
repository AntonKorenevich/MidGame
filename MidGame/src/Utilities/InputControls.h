#pragma once
#include "Utils.h"

class InputControls
{
public:
	void KeyPressed(sf::Keyboard::Scancode sc);
	void KeyReleased(sf::Keyboard::Scancode sc);

	Direction GetDirection() const;

private:
	std::map<sf::Keyboard::Scancode, bool> m_scs;
};