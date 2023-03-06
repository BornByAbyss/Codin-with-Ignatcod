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

    olc::Sprite *sprKnightBlack = nullptr;
    olc::Sprite *sprKnightWhite = nullptr;

    olc::Sprite *sprBishopBlack = nullptr;
    olc::Sprite *sprBishopWhite = nullptr;

    olc::Decal *decBishopBlack = nullptr;
    olc::Decal *decBishopWhite = nullptr;

    olc::Decal *decKnightBlack = nullptr;
    olc::Decal *decKnightWhite = nullptr;

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
    bool isSelectorWhiteOn = false;
    bool isSelectorBlackOn = false;

    int x = -1;

    Point initialPoint;
    Point checkPosition;

private:
    std::vector<std::vector<std::vector<Figures *>>> deckNotation;

    std::vector<std::vector<Figures *>> tempBoard = {{empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty},
                                                     {empty, empty, empty, empty, empty, empty, empty, empty}};

    Pawn pawnB1, pawnB2, pawnB3, pawnB4, pawnB5, pawnB6, pawnB7, pawnB8;
    Pawn pawnW1, pawnW2, pawnW3, pawnW4, pawnW5, pawnW6, pawnW7, pawnW8;

    Queen queenW, queenB;

    std::vector<Point> prevInitialPoints;

    Bishop bishopW1, bishopW2, bishopB1, bishopB2;

    Knight knightW1, knightW2, knightB1, knightB2;

    Rook rookW1, rookW2;
    Rook rookB1, rookB2;

    King kingW, kingB;

    Figures *empty = nullptr;

    std::vector<std::vector<Figures *>> deck;

public:
    ChessGame();
    void getPossibleCells(const Point, std::vector<Point> &);

    void checkAnalisysPoints();
    bool isCheckOnBoard();
    bool isWhiteCheck();
    bool isBlackCheck();

    bool isCheckMate();

    void whiteCastling();
    void blackCastling();

    void saveBoard();

    void toStep(Point, Point);
    void stepBack();

    void clearPoints(std::vector<Point> &);

    virtual bool OnUserCreate() override;
    virtual bool OnUserUpdate(float fElapsedTime) override;
};

#endif