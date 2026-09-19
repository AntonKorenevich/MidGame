#pragma once
#include "Utilities/Utils.h"

class Piece
{
public:
	Piece(int id);
	Piece(PieceTemplate pt, int id);
	void GeneratePiece();
	void Normalize();
	void SetPosition(sf::Vector2i pos);
	const sf::Vector2i GetPosition() const;

	void SetStockPosition(sf::Vector2i pos);
	const sf::Vector2i GetStockPosition() const;

	const int GetID() const { return m_id; };
	PieceTemplate GetCells() const;
private:
	sf::Vector2i	m_position;
	sf::Vector2i	m_stockPosition;

	PieceTemplate	m_piece;
	int				m_id;
};