#include "Player.h"

static const int s_factor = 10;
Player::Player(const sf::RenderWindow& rw)
	: m_rw(rw)
	, m_accelerator(0.f)
	, m_moveDirection(Direction::NONE)
	, m_forceDirection(Direction::NONE)
{
	m_rec.setSize(sf::Vector2f(50, 50));
	sf::Vector2f pos = sf::Vector2f(rw.getSize().x / 2 - m_rec.getSize().x / 2, rw.getSize().y / 2 - m_rec.getSize().y / 2);
	m_rec.setPosition(pos);
	m_rec.setFillColor(sf::Color::Green);
}

void Player::ApplyForce(Direction dir)
{
	m_forceDirection = dir;

}

void Player::MoveObject()
{
	sf::Vector2f currentPos = m_rec.getPosition();
	float width = (float)m_rw.getSize().x;
	float heigh = (float)m_rw.getSize().y;
	float deltaPos = m_accelerator / s_factor;
	if (m_accelerator > 0.f)
	{
		switch (m_moveDirection)
		{
		case Direction::TOP:
			break;

		case Direction::BOTTOM:
			break;

		case Direction::LEFT:
			currentPos.x = currentPos.x - deltaPos > 0 ? currentPos.x - deltaPos : width;
			break;

		case Direction::RIGHT:
			currentPos.x = currentPos.x + deltaPos < width ? currentPos.x + deltaPos : 0;
			break;
		};
	}
	m_rec.setPosition(currentPos);
}

void Player::Update(float dt)
{
	// apply force
	if (m_forceDirection != Direction::NONE && 
		m_moveDirection == m_forceDirection)
	{
		m_accelerator += dt;
		m_moveDirection = m_forceDirection;
	}

	// inertion
	if (m_moveDirection != m_forceDirection)
	{
		m_accelerator -= dt;
	}
	m_accelerator = std::fmax(0.f, m_accelerator);
	if (m_accelerator == 0)
	{
		m_moveDirection = m_forceDirection;
	}
	
	std::cout << "Speed: " << m_accelerator << std::endl;
	MoveObject();

}
