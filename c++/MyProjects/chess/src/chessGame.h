#ifndef DECK_H
#define DECK_H

#include <iostream>
#include "point.h"
#include "figures.h"
#include "olcPixelGameEngine.h"

class ChessGame : public olc::PixelGameEngine
{
public:
    olc::Sprite *sprDeck = nullptr;
    int nLayerBackground = 0;
    int iTempIndex = -1;
    int jTempIndex = -1;

private:
    olc::vf2d *pSelected = nullptr;
    olc::vf2d temp = {0.0f, 0.0f};

private:
    olc::Sprite *sprPawnBlack = nullptr;
    olc::Sprite *sprPawnWhite = nullptr;

    olc::Sprite *sprQueenBlack = nullptr;
    olc::Sprite *sprQueenWhite = nullptr;

    olc::Decal *decQueenBlack = nullptr;
    olc::Decal *decQueenWhite = nullptr;

    olc::Decal *decPawnBlack = nullptr;
    olc::Decal *decPawnWhite = nullptr;

private:
    Point initialPoint;
    bool isFind = false;
    bool notFound = true;
    std::vector<Point> points; //     massive of all possible steps include deck position

private:
    Point begP;
    Pawn pawnB1, pawnB2, pawnB3, pawnB4, pawnB5, pawnB6, pawnB7, pawnB8;
    Pawn pawnW1, pawnW2, pawnW3, pawnW4, pawnW5, pawnW6, pawnW7, pawnW8;

    Queen queenW, queenB;

    Figures *empty = nullptr;
    Figures *deck[8][8] = {{empty, empty, empty, &queenB, empty, empty, empty, empty},
                           {&pawnB1, &pawnB2, &pawnB3, &pawnB4, &pawnB5, &pawnB6, &pawnB7, &pawnB8},
                           {empty, empty, empty, empty, empty, empty, empty, empty},
                           {empty, empty, empty, empty, empty, empty, empty, empty},
                           {empty, empty, empty, empty, empty, empty, empty, empty},
                           {empty, empty, empty, empty, empty, empty, empty, empty},
                           {&pawnW1, &pawnW2, &pawnW3, &pawnW4, &pawnW5, &pawnW6, &pawnW7, &pawnW8},
                           {empty, empty, empty, &queenW, empty, empty, empty, empty}};

public:
    ChessGame();
    bool toStep(Point);
    void logicOperation(Point);
    void clearPoints();
    virtual bool OnUserCreate() override;
    virtual bool OnUserUpdate(float fElapsedTime) override;
};

#endif