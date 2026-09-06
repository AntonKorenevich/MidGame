#pragma once
#include "Utilities/Utils.h"

class Player
{
public:
	Player(const sf::RenderWindow& rw);
	~Player() {};

	void ApplyForce(Direction dir);
	void MoveObject();
	void Update(float dt);

	const sf::RectangleShape* GetPlayerRec() const
	{
		return &m_rec;
	}

private:
	float			m_accelerator;
	Direction		m_moveDirection;
	Direction		m_forceDirection;

	sf::RectangleShape m_rec;
	const sf::RenderWindow& m_rw;
};