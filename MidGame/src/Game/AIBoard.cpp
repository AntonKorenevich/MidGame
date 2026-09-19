#include "AIBoard.h"

const int BORDER_WEIGHT = 5;
const int EMPTY_WEIGHT = 10;
const int FULL_WEIGHT = -10;
const int LINE_CLEARED_WEIGHT = 50;

AIBoard::AIBoard(sf::RenderWindow& rw)
	: Board(rw)
	, m_selectedPieceID(-1)
	, m_moveCounter(0)
{
}

void AIBoard::Iterate()
{
	if (!m_deck.empty() && m_possibilities.empty())
	{
		GetPossibleMoves();
		EvaluateMoves();
		SelectMove();
		Move();
		UpdateBoard();
		if (m_deck.empty())
		{
			FillDeck();
		}
	}
}

void AIBoard::GetPossibleMoves()
{
	// for each piece
	for (const auto& p : m_deck)
	{
		// for each board cell
		for (const auto& [key, value] : m_board)
		{
			bool placablePiece = true;
			// for each piece's cell
			for (const auto& c : p->GetCells())
			{
				std::pair<int, int> cPos = { key.first + c.first, key.second + c.second };
				if (cPos.first > 7 || cPos.second > 7 || cPos.first < 0 || cPos.second < 0
					|| m_board[{cPos.first, cPos.second}] == true)
				{
					placablePiece = false;
					break;
				}
			}
			
			if (placablePiece)
			{
				m_possibilities[p->GetID()].emplace_back(key.first, key.second);
			}
		}
	}
}

void AIBoard::EvaluateMoves()
{
	m_pseudoBoard.board = m_board;
	m_pseudoBoard.lWeight = -100000;
	m_pseudoBoard.rWeight = -100000;
	m_pseudoBoard.selectedPieceIDDowngrade = -1;
	m_pseudoBoard.selectedPieceIDUpgrade = -1;
	CalculateCurrentWeight();

	for (const auto& [key, value] : m_possibilities)
	{
		auto it = std::find_if(m_deck.begin(), m_deck.end(),
			[key](const std::unique_ptr<Piece>& piece)
			{
				return key == piece->GetID();
			});

		if (it != m_deck.end())
		{
			for (const auto& possibleCell : value)
			{
				m_pseudoBoard.board = m_board;

				for (const auto& c : (*it)->GetCells())
				{
					m_pseudoBoard.board[{ possibleCell.first + c.first, possibleCell.second + c.second }] = true;
				}

				m_pseudoBoard.lineCounter = 0;

				UpdatePseudoBoard();
				CalculatePseudoMoveWeight();

				if (m_pseudoBoard.weight >= m_pseudoBoard.currentWeight)
				{
					// Upgrade
					if (m_pseudoBoard.lWeight < m_pseudoBoard.weight)
					{
						m_pseudoBoard.lWeight = m_pseudoBoard.weight;
						m_pseudoBoard.selectedMoveUpgrade = possibleCell;
						m_pseudoBoard.selectedPieceIDUpgrade = key;
					}
				}
				else
				{
					// Downgrade
					if (m_pseudoBoard.rWeight < m_pseudoBoard.weight)
					{
						m_pseudoBoard.rWeight = m_pseudoBoard.weight;
						m_pseudoBoard.selectedMoveDowngrade = possibleCell;
						m_pseudoBoard.selectedPieceIDDowngrade = key;
					}
				}
			}
		}
	}
}

void AIBoard::SelectMove()
{
	
	if (m_pseudoBoard.selectedPieceIDUpgrade != -1)
	{
		m_selectedMove = m_pseudoBoard.selectedMoveUpgrade;
		m_selectedPieceID = m_pseudoBoard.selectedPieceIDUpgrade;
	}
	else
	{
		m_selectedMove = m_pseudoBoard.selectedMoveDowngrade;
		m_selectedPieceID = m_pseudoBoard.selectedPieceIDDowngrade;
	}
}

void AIBoard::PseudoMove()
{
}

void AIBoard::Move()
{
	if (m_selectedPieceID >= 0)
	{
		auto it = std::find_if(m_deck.begin(), m_deck.end(),
			[this](const std::unique_ptr<Piece>& piece)
			{
				return m_selectedPieceID == piece->GetID();
			});
		if (it != m_deck.end())
		{
			for (const auto& c : (*it)->GetCells())
			{
				m_board[{m_selectedMove.first + c.first, m_selectedMove.second + c.second}] = true;
			}

			m_deck.erase(it);
			m_selectedPieceID = -1;
		}

		++m_moveCounter;
		std::cout << "Counter: " << m_moveCounter << std::endl;
	}
	m_possibilities.clear();
}

void AIBoard::CalculatePseudoMoveWeight()
{
	m_pseudoBoard.weight = 0;

	for (const auto& [key, value] : m_pseudoBoard.board)
	{
		if (value == false)
		{
			m_pseudoBoard.weight += EMPTY_WEIGHT;
		}
		else
		{
			m_pseudoBoard.weight += FULL_WEIGHT;
		}
	}

	if (m_pseudoBoard.lineCounter > 0)
	{
		m_pseudoBoard.weight += m_pseudoBoard.lineCounter * LINE_CLEARED_WEIGHT;
	}
}

void AIBoard::CalculateCurrentWeight()
{
	m_pseudoBoard.currentWeight = 0;

	for (const auto& [key, value] : m_board)
	{
		if (value == false)
		{
			m_pseudoBoard.currentWeight += EMPTY_WEIGHT;
		}
		else
		{
			m_pseudoBoard.currentWeight += FULL_WEIGHT;
		}
	}
}

void AIBoard::UpdatePseudoBoard()
{
	std::vector<int> removeI;
	std::vector<int> removeJ;

	for (int i = 0; i < 8; i++)
	{
		bool jState = true;
		for (int j = 0; j < 8; j++)
		{
			if (m_pseudoBoard.board[{i, j}] == false)
			{
				jState = false;
			}
		}
		if (jState)
		{
			removeI.push_back(i);
			m_pseudoBoard.lineCounter++;
		}
	}

	for (int i = 0; i < 8; i++)
	{
		bool iState = true;
		for (int j = 0; j < 8; j++)
		{
			if (m_pseudoBoard.board[{j, i}] == false)
			{
				iState = false;
			}
		}
		if (iState)
		{
			removeJ.push_back(i);
			m_pseudoBoard.lineCounter++;
		}
	}

	for (int n : removeI)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (i == n)
				{
					m_pseudoBoard.board[{i, j}] = false;
				}
			}
		}
	}

	for (int n : removeJ)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (j == n)
				{
					m_pseudoBoard.board[{i, j}] = false;
				}
			}
		}
	}
}
