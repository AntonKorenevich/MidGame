#include "InputControls.h"

void InputControls::KeyPressed(sf::Keyboard::Scancode sc)
{
	m_scs[sc] = true;
}

void InputControls::KeyReleased(sf::Keyboard::Scancode sc)
{
	m_scs[sc] = false;
}

Direction InputControls::GetDirection() const
{
	for (const auto& [scancode, isPressed] : m_scs)
	{
		if (!isPressed)
		{
			continue;
		}

		switch (scancode)
		{
		case sf::Keyboard::Scancode::A:
			return Direction::LEFT;
		case sf::Keyboard::Scancode::D:
			return Direction::RIGHT;
		case sf::Keyboard::Scancode::W:
			return Direction::TOP;
		case sf::Keyboard::Scancode::S:
			return Direction::BOTTOM;
		}
	}
	return Direction::NONE;
}
