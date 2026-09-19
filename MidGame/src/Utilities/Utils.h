#pragma once
#include "../stdafx.h"

using Cell = std::pair<int, int>;
using PieceTemplate = std::vector<Cell>;

enum Direction
{
	NONE,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

enum PieceType
{
	SQUARE,
	LINE,
	LTYPE,
	SPARK,
};


class RandomGenerator
{
public:
	static RandomGenerator& GetInstance()
	{
		static RandomGenerator instance;
		return instance;
	}

private:
	RandomGenerator()
		: rd()
		, gen(rd())
		, dist3(0, 3)
		, dist4(0, 4)
		, dist7(0, 7)
	{
	}

public:
	int GetRandom3()
	{
		return dist3(gen);
	}

	int GetRandom4()
	{
		return dist4(gen);
	}

	int GetRandom7()
	{
		return dist7(gen);
	}

private:
	std::uniform_int_distribution<int> dist3;
	std::uniform_int_distribution<int> dist4;
	std::uniform_int_distribution<int> dist7;
	std::random_device rd;
	std::mt19937 gen;
};