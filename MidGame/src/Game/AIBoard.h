#pragma once
#include "Utilities/Utils.h"
#include "Piece.h"
#include "Board.h"

struct PseudoBoard
{
	std::map<std::pair<int, int>, bool> board;
	int									currentWeight = -100000;
	int									weight = 0;
	int									lWeight = -100000;
	int									rWeight = -100000;
	int									selectedPieceIDUpgrade = -1;
	std::pair<int, int>					selectedMoveUpgrade = {0,0};
	int									selectedPieceIDDowngrade = -1;
	std::pair<int, int>					selectedMoveDowngrade = {0,0};
	int									lineCounter = 0;
};

class AIBoard : public Board
{
public:
	AIBoard(sf::RenderWindow& rw);
	~AIBoard() = default;

	void	Iterate();
	// game loop
	void	GetPossibleMoves();
	void	EvaluateMoves();
	void	SelectMove();
	void	PseudoMove();
	void	Move();
	void	CalculatePseudoMoveWeight();
	void	CalculateCurrentWeight();
	void	UpdatePseudoBoard();



private:
	std::map<int, std::vector<std::pair<int, int>>> m_possibilities;
	int						m_selectedPieceID;
	std::pair<int, int>		m_selectedMove;

	PseudoBoard m_pseudoBoard;

	int m_moveCounter;
};