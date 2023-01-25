#ifndef DECK_H
#define DECK_H

#include <iostream>
#include "point.h"
#include "figures.h"

namespace chesslogix
{
    class Deck
    {
    private:
        Point begP;
        std::vector<Point> points; //     massive of all possible steps include deck position
        Pawn pawnB, pawnW;
        Rook rookB, rookW;
        Knight knightB, knightW;
        Bishop bishopB, bishopW;
        Queen queenB, queenW;
        King kingB, kingW;
        Figures *empty = nullptr;
        Figures *deck[8][8] = {{&rookB, &knightB, &bishopB, &queenB, &kingB, &bishopB, &knightB, &rookB},
                               {&pawnB, &pawnB, &pawnB, &pawnB, &pawnB, &pawnB, &pawnB, &pawnB},
                               {empty, empty, empty, empty, empty, empty, empty, empty},
                               {empty, empty, empty, empty, empty, empty, empty, empty},
                               {empty, empty, empty, empty, empty, empty, empty, empty},
                               {empty, empty, empty, empty, empty, empty, empty, empty},
                               {&pawnW, &pawnW, &pawnW, &pawnW, &pawnW, &pawnW, &pawnW, &pawnW},
                               {&rookW, &knightW, &bishopW, &queenW, &kingW, &bishopW, &knightW, &rookW}};

    public:
        Deck();
        void makeAstep(Point);
        void logicOperation(std::string);
        void clearPoints();
        std::vector<Point> takeVpoints();
    };
}

#endif