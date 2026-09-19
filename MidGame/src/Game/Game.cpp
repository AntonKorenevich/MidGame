#include "Game.h"

Game::Game(sf::RenderWindow& rw)
	: m_window(rw)
	, m_board(rw)
	, m_drugging(false)
{
}

Game::~Game()
{
}

void Game::Update(float dt)
{
	if (m_aiClock.getElapsedTime().asSeconds() < 0.5f)
		return;

	m_aiClock.restart();
	m_board.Iterate();
}

void Game::Draw()
{
	m_board.Draw();
}

void Game::KeyPressed(sf::Keyboard::Scancode sc)
{
	m_ic.KeyPressed(sc);
}

void Game::KeyReleased(sf::Keyboard::Scancode sc)
{
	m_ic.KeyReleased(sc);
}

void Game::OnLeftBtnPressed(sf::Vector2i vi)
{
	m_drugging = m_board.CapturePiece(vi);
}

void Game::OnMouseMoved(sf::Vector2i vi)
{
	if (m_drugging)
	{
		m_board.MovePiece(vi);
	}
}

void Game::OnLeftBtnReleased(sf::Vector2i vi)
{
	m_board.ReleasePiece(vi);
	m_drugging = false;
}
