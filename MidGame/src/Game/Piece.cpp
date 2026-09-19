#include "Piece.h"
#include "Utilities/PieceTemplates.h"

Piece::Piece(int id)
	: m_position(0, 0)
	, m_stockPosition(0, 0)
	, m_id(id)
{
}

Piece::Piece(PieceTemplate pt, int id)
	: m_position(0, 0)
	, m_stockPosition(0, 0)
	, m_piece(pt)
	, m_id(id)
{
}

void Piece::GeneratePiece()
{
	int rIndex = RandomGenerator::GetInstance().GetRandom7();
	m_piece = pieceTemplates[rIndex];

	// rotation
	int rotation = RandomGenerator::GetInstance().GetRandom3();
	
	for (int i = 0; i < rotation; i++)
	{
		for (auto& p : m_piece)
		{
			std::swap(p.first, p.second);
			p.first *= (-1);
		}
	}
	Normalize();
}

void Piece::Normalize()
{
	if (m_piece.empty())
	{
		std::cout << "ERROR: Empty piece array on normalize attempt!" << std::endl;
		return;
	}

	int min_x = m_piece[0].first;
	int min_y = m_piece[0].second;
	for (auto& p : m_piece)
	{
		min_x = std::min(p.first, min_x);
		min_y = std::min(p.second, min_y);
	}

	for (auto& p : m_piece)
	{
		p.first -= min_x;
		p.second -= min_y;
	}
}

void Piece::SetPosition(sf::Vector2i pos)
{
	m_position = pos;
}

const sf::Vector2i Piece::GetPosition() const
{
	return m_position;
}

void Piece::SetStockPosition(sf::Vector2i pos)
{
	m_stockPosition = pos;
}

const sf::Vector2i Piece::GetStockPosition() const
{
	return m_stockPosition;
}

PieceTemplate Piece::GetCells() const
{
	return m_piece;
}
