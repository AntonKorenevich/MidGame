#include "Game.h"
#include "Player.h"

Game::Game(sf::RenderWindow& rw)
	: m_window(rw)
{
	m_player = std::make_unique<Player>(rw);
}

Game::~Game()
{
}

void Game::Update(float dt)
{
	if (m_player)
	{
		m_player->Update(dt);
		m_player->ApplyForce(m_ic.GetDirection());
	}
}

void Game::Draw()
{
	if (m_player)
	{
		m_window.draw(*m_player->GetPlayerRec());
	}
}

void Game::KeyPressed(sf::Keyboard::Scancode sc)
{
	m_ic.KeyPressed(sc);
}

void Game::KeyReleased(sf::Keyboard::Scancode sc)
{
	m_ic.KeyReleased(sc);
}
