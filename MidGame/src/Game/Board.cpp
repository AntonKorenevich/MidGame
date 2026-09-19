#include "Board.h"


Board::Board(sf::RenderWindow& rw)
	: m_window(rw)
	, m_capturedPiece(nullptr)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_board[{i, j}] = false;
		}
	}
	FillDeck();
}

void Board::FillDeck()
{
	float xOffset = 500;
	float yOffset = 0;
	for (int i = 0; i < 3; i++)
	{
		auto p = std::make_unique<Piece>(i);
		p->GeneratePiece();
		p->SetPosition(sf::Vector2i(xOffset, yOffset));
		p->SetStockPosition(sf::Vector2i(xOffset, yOffset));
		m_deck.emplace_back(std::move(p));
		yOffset += 210;
	}
}

bool Board::CapturePiece(sf::Vector2i vi)
{
	m_capturedPiece = GetPiece(vi);
	if (m_capturedPiece)
	{
		SetCapturedOffset(vi);
	}
	return m_capturedPiece;
}

void Board::MovePiece(sf::Vector2i vi)
{
	if (m_capturedPiece)
	{
		m_capturedPiece->SetPosition(vi - m_captureOffset);
	}
}

void Board::ReleasePiece(sf::Vector2i vi)
{
	ApplyPiece();
	m_capturedPiece = nullptr;
}

void Board::ApplyPiece()
{
	if (!m_capturedPiece)
	{
		return;
	}
	// apply piece on board
	sf::Vector2i currentPos = GetCapturedPiecePos();
	

	for (const auto& v : m_capturedPiece->GetCells())
	{
		sf::Vector2i shiftedLocalPos;
		shiftedLocalPos.x = currentPos.x + v.first;
		shiftedLocalPos.y = currentPos.y + v.second;

		// out of the border
		if (shiftedLocalPos.x > 7 || 
			shiftedLocalPos.y > 7 || 
			shiftedLocalPos.y < 0 || 
			shiftedLocalPos.x < 0)
		{
			// revert piece's position
			m_capturedPiece->SetPosition(m_capturedPiece->GetStockPosition());
			return;
		}

		// block is busy
		if (m_board[{shiftedLocalPos.x, shiftedLocalPos.y}] == true)
		{
			// revert piece's position
			m_capturedPiece->SetPosition(m_capturedPiece->GetStockPosition());
			return;
		}
	}

	// apply piece
	for (const auto& v : m_capturedPiece->GetCells())
	{
		sf::Vector2i shiftedLocalPos;
		shiftedLocalPos.x = currentPos.x + v.first;
		shiftedLocalPos.y = currentPos.y + v.second;
		
		m_board[{shiftedLocalPos.x, shiftedLocalPos.y}] = true;
	}

	ReleasePiece();
	UpdateBoard();
}

sf::Vector2i Board::GetCapturedPiecePos() const
{
	sf::Vector2i currentPos(50,50);
	if (m_capturedPiece)
	{
		for (const auto& [key, value] : m_board)
		{
			sf::Vector2f positionL(50 + key.first * 50, 50 + key.second * 50);
			sf::Vector2f positionR(50 + key.first * 50 + 50, 50 + key.second * 50 + 50);
			if (m_capturedPiece->GetPosition().x + 25 > positionL.x &&
				m_capturedPiece->GetPosition().x + 25 < positionR.x &&
				m_capturedPiece->GetPosition().y + 25 > positionL.y &&
				m_capturedPiece->GetPosition().y + 25 < positionR.y)
			{
				currentPos = sf::Vector2i(key.first, key.second);
			}
		}
	}
	return currentPos;
}

void Board::ReleasePiece()
{
	m_deck.erase(std::remove_if(m_deck.begin(), m_deck.end(),
		[this](const std::unique_ptr<Piece>& piece) { return piece.get() == m_capturedPiece; }),
		m_deck.end());
	m_capturedPiece = nullptr;
}

void Board::UpdateBoard()
{
	std::vector<int> removeI;
	std::vector<int> removeJ;

	for (int i = 0; i < 8; i++)
	{
		bool jState = true;
		for (int j = 0; j < 8; j++)
		{
			if (m_board[{i, j}] == false)
			{
				jState = false;
			}
		}
		if (jState)
		{
			removeI.push_back(i);
		}
	}
	
	for (int i = 0; i < 8; i++)
	{
		bool iState = true;
		for (int j = 0; j < 8; j++)
		{
			if (m_board[{j, i}] == false)
			{
				iState = false;
			}
		}
		if (iState)
		{
			removeJ.push_back(i);
		}
	}

	for (int n : removeI)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if(i == n)
				{
					m_board[{i, j}] = false;
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
					m_board[{i, j}] = false;
				}
			}
		}
	}

	if (m_deck.empty())
	{
		FillDeck();
	}
}

void Board::Draw()
{
	// draw playground
	for (const auto& [key, value] : m_board)
	{
		sf::RectangleShape rs;
		rs.setSize(sf::Vector2f(50, 50));
		sf::Vector2f position(50 + key.first * 50, 50 + key.second * 50);
		rs.setPosition(position);

		bool selectedCell = false;
		if (m_capturedPiece)
		{
			sf::Vector2i currentPos = GetCapturedPiecePos();
			for (const auto& v : m_capturedPiece->GetCells())
			{
				sf::Vector2i shiftedLocalPos;
				shiftedLocalPos.x = currentPos.x + v.first;
				shiftedLocalPos.y = currentPos.y + v.second;
				if (shiftedLocalPos.x == key.first && shiftedLocalPos.y == key.second)
				{
					selectedCell = true;
				}
			}
		}
		
		if (selectedCell)
		{
			rs.setOutlineThickness(3);
			if (m_board[{key.first, key.second}])
			{
				rs.setOutlineColor(sf::Color::Red);
			}
			else
			{
				rs.setOutlineColor(sf::Color::Green);
			}
		}
		else
		{
			rs.setOutlineThickness(1);
			rs.setOutlineColor(sf::Color::White);
		}

		if (value)
		{
			rs.setFillColor(sf::Color::Green);
			
		}
		else
		{
			rs.setFillColor(sf::Color::Transparent);
		}


		m_window.draw(rs);
	}

	// draw deck
	for (const auto& p : m_deck)
	{
		for (const auto& v : p->GetCells())
		{
			sf::RectangleShape rs;
			rs.setSize(sf::Vector2f(50, 50));
			sf::Vector2f position(p->GetPosition().x + v.first * 50, p->GetPosition().y + v.second * 50);
			rs.setPosition(position);
			rs.setOutlineThickness(1);
			rs.setFillColor(sf::Color::Green);
			rs.setOutlineColor(sf::Color::White);
			m_window.draw(rs);
		}
	}
}

void Board::SetCapturedOffset(sf::Vector2i vi)
{
	if (m_capturedPiece)
	{
		m_captureOffset = vi - m_capturedPiece->GetPosition();
	}
}

Piece* Board::GetPiece(sf::Vector2i vi)
{
	for (auto& p : m_deck)
	{
		for (const auto& v : p->GetCells())
		{
			sf::Vector2f positionL(p->GetPosition().x + v.first * 50, p->GetPosition().y + v.second * 50);
			sf::Vector2f positionR(p->GetPosition().x + v.first * 50 + 50, p->GetPosition().y + v.second * 50 + 50);
			if (vi.x > positionL.x &&
				vi.x < positionR.x &&
				vi.y > positionL.y &&
				vi.y < positionR.y)
			{
				return p.get();
			}
		}
	}

	return nullptr;
}
