#pragma once
#include "Utils.h"

static const std::vector<PieceTemplate> pieceTemplates
{
    // line
    {
        {0, 0},
        {0, 1},
    },
    // line
    {
        {0, 0},
        {0, 1},
        {0, 2},
    },
    // line
    {
        {0, 0},
        {0, 1},
        {0, 2},
        {0, 3},
    },
    // square
    {
        {0, 0},
        {0, 1},
        {1, 0},
        {1, 1}
    },
    // l-type
    {
        {0, 0},
        {0, 1},
        {1, 0}
    },
    // l-type
    {
        {0, 0},
        {0, 1},
        {1, 0},
        {2, 0}
    },
    // l-type
    {
        {0, 0},
        {0, 1},
        {0, 2},
        {1, 0},
        {2, 0}
    },
    // z-type
    {
        {0, 0},
        {0, 1},
        {1, 1},
        {1, 2}
    }

};