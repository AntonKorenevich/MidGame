#pragma once
#include <memory>
#include "Utilities/Utils.h"
#include "Piece.h"

class Board
{
public:
	Board(sf::RenderWindow& rw);
	~Board() = default;

	void FillDeck();

	bool CapturePiece(sf::Vector2i vi);
	void MovePiece(sf::Vector2i vi);
	void ReleasePiece(sf::Vector2i vi);
	void ApplyPiece();
	sf::Vector2i GetCapturedPiecePos() const;
	void ReleasePiece();
	void UpdateBoard();
	void Draw();
	void SetCapturedOffset(sf::Vector2i vi);

	Piece* GetPiece(sf::Vector2i vi);

protected:
	std::map<std::pair<int, int>, bool> m_board;
	std::vector<std::unique_ptr<Piece>> m_deck;
	Piece*			m_capturedPiece;
	sf::Vector2i	m_captureOffset;
	sf::RenderWindow& m_window;

private:

};
