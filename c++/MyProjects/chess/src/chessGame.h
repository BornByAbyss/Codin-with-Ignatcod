#ifndef DECK_H
#define DECK_H

#include <iostream>
#include "point.h"
#include "figures.h"
#include "olcPixelGameEngine.h"

class ChessGame : public olc::PixelGameEngine
{
public:
    int nLayerBackground = 0;
    int iTempIndex = -1;
    int jTempIndex = -1;

private:
    olc::vf2d *pSelected = nullptr;
    olc::vf2d temp = {0.0f, 0.0f};

private:
    olc::Sprite *sprDeck = nullptr;

    olc::Sprite *sprPawnBlack = nullptr;
    olc::Sprite *sprPawnWhite = nullptr;

    olc::Sprite *sprKingBlack = nullptr;
    olc::Sprite *sprKingWhite = nullptr;

    olc::Sprite *sprRookBlack = nullptr;
    olc::Sprite *sprRookWhite = nullptr;

    olc::Sprite *sprQueenBlack = nullptr;
    olc::Sprite *sprQueenWhite = nullptr;

    olc::Decal *decQueenBlack = nullptr;
    olc::Decal *decQueenWhite = nullptr;

    olc::Decal *decPawnBlack = nullptr;
    olc::Decal *decPawnWhite = nullptr;

    olc::Decal *decRookBlack = nullptr;
    olc::Decal *decRookWhite = nullptr;

    olc::Decal *decKingBlack = nullptr;
    olc::Decal *decKingWhite = nullptr;

private:
    std::vector<Point> points; //     massive of all possible steps include deck position

    bool turn = true;
    bool isCheck = false;
    bool isFind = false;
    Point prevInitialPoint;
    Point initialPoint;
    Point checkPosition;

private:
    Pawn pawnB1, pawnB2, pawnB3, pawnB4, pawnB5, pawnB6, pawnB7, pawnB8;
    Pawn pawnW1, pawnW2, pawnW3, pawnW4, pawnW5, pawnW6, pawnW7, pawnW8;

    std::vector<std::vector<std::vector<Figures *>>> deckNotation;

    std::vector<std::vector<Figures *>> tempBoard = {{empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty}};

    Queen queenW, queenB;

    Rook rookW1, rookW2;
    Rook rookB1, rookB2;

    King kingW, kingB;

    Figures *empty = nullptr;

    std::vector<std::vector<Figures *>> deck = {{&rookB1, empty, empty, &queenB, &kingB, empty, empty, &rookB2},
                                                {&pawnB1, &pawnB2, &pawnB3, &pawnB4, &pawnB5, &pawnB6, &pawnB7, &pawnB8},
                                                {empty, empty, empty, empty, empty, empty, empty, empty},
                                                {empty, empty, empty, empty, empty, empty, empty, empty},
                                                {empty, empty, empty, empty, empty, empty, empty, empty},
                                                {empty, empty, empty, empty, empty, empty, empty, empty},
                                                {&pawnW1, &pawnW2, &pawnW3, &pawnW4, &pawnW5, &pawnW6, &pawnW7, &pawnW8},
                                                {&rookW1, empty, empty, &queenW, &kingW, empty, empty, &rookW2}};

public:
    ChessGame();
    void getPossibleCells(const Point, std::vector<Point> &);

    void checkAnalisysPoints();
    bool isCheckOnBoard();
    bool isWhiteCheck();
    bool isBlackCheck();

    void whiteCastling();
    void blackCastling();

    void saveBoard();

    void toStep(Point, Point, bool);
    void stepBack();

    void clearPoints(std::vector<Point> &);

    virtual bool OnUserCreate() override;
    virtual bool OnUserUpdate(float fElapsedTime) override;
};

#endif