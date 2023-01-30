#include <iostream>
#include <iomanip>
#include <vector>
#include "point.h"
#include "figures.h"
#include "chessGame.h"
#include "olcPixelGameEngine.h"

ChessGame::ChessGame()
{
    sAppName = "Chess";
    pawnW1.set(true, "pawn", 0.0f, 480.0);
    pawnW2.set(true, "pawn", 80.0f, 480.0);
    pawnW3.set(true, "pawn", 160.0f, 480.0);
    pawnW4.set(true, "pawn", 240.0f, 480.0);
    pawnW5.set(true, "pawn", 320.0f, 480.0);
    pawnW6.set(true, "pawn", 400.0f, 480.0);
    pawnW7.set(true, "pawn", 480.0f, 480.0);
    pawnW8.set(true, "pawn", 560.0f, 480.0);

    pawnB1.set(false, "pawn", 0.0f, 80.0);
    pawnB2.set(false, "pawn", 80.0f, 80.0);
    pawnB3.set(false, "pawn", 160.0f, 80.0);
    pawnB4.set(false, "pawn", 240.0f, 80.0);
    pawnB5.set(false, "pawn", 320.0f, 80.0);
    pawnB6.set(false, "pawn", 400.0f, 80.0);
    pawnB7.set(false, "pawn", 480.0f, 80.0);
    pawnB8.set(false, "pawn", 560.0f, 80.0);

    queenB.set(false, "queen", 240.0f, 0.0f);
    queenW.set(true, "queen", 240.0f, 560.0f);
}

bool ChessGame::toStep(Point endP)
{ // 0 - empty  1 - enemy
    bool isAnyBodyOutThere = false;
    if (deck[endP.row][endP.col] != empty)
        isAnyBodyOutThere = true;
    deck[endP.row][endP.col] = deck[begP.row][begP.col];
    deck[begP.row][begP.col] = empty;
    return isAnyBodyOutThere;
}

void ChessGame::logicOperation(Point initialPoint)
{
    Point step{0, 0, false};
    Point tempPoint{0, 0, true};

    bool isFirst = true;

    begP.col = initialPoint.col;
    begP.row = initialPoint.row;
    begP.isAttack = false;

    Figures *elem = deck[initialPoint.row][initialPoint.col];

    elem->move(initialPoint.row, initialPoint.col, points); //      take all possible points of figures

    for (int i = 0; i < points.size(); i++)
    {
        if ((deck[points[i].row][points[i].col] == empty || (elem->showColor() == deck[points[i].row][points[i].col]->showColor())) && elem->showType() == "pawn" && points[i].isAttack)
        {
            points.erase(points.begin() + i);
            --i;
            continue;
        }
        else if (deck[points[i].row][points[i].col] != empty && ((elem->showType() == "pawn" && !points[i].isAttack) || (elem->showType() != "pawn" && points[i].isAttack))) // пешка не атакует  и цвет совпадает
        {
            if ((points[i].row - initialPoint.row) != 0)
                step.row = ((points[i].row - initialPoint.row) / abs((points[i].row - initialPoint.row)));
            if ((points[i].col - initialPoint.col) != 0)
                step.col = ((points[i].col - initialPoint.col) / abs((points[i].col - initialPoint.col)));

            tempPoint = (initialPoint + step);

            while (true)
            {
                if ((i >= 0) && (i < points.size()) && elem->showColor() == deck[points[i].row][points[i].col]->showColor() && isFirst)
                {
                    points.erase(points.begin() + i);
                    if (i >= points.size())
                        break;

                    tempPoint += step;
                    isFirst = false;
                }

                if ((i >= 0) && (i < points.size()) && (tempPoint == points[i]))
                {
                    points.erase(points.begin() + i);
                    if (i >= points.size())
                        break;
                    tempPoint += step;
                }
            }
            isFirst = true;

            --i;
            // if (elem->showColor() == deck[points[i].row][points[i].col]->showColor()
            // if (elem->showColor() != deck[points[i].row][points[i].col]->showColor()
        }
    }
}

bool ChessGame::OnUserCreate()
{
    sprDeck = new olc::Sprite("./images/deck.png");

    sprPawnWhite = new olc::Sprite("./images/pawnWhite.png");
    sprPawnBlack = new olc::Sprite("./images/pawnBlack.png");

    sprQueenWhite = new olc::Sprite("./images/queenWhite.png");

    decQueenWhite = new olc::Decal(sprQueenWhite);
    decPawnWhite = new olc::Decal(sprPawnWhite);
    decPawnBlack = new olc::Decal(sprPawnBlack);

    nLayerBackground = CreateLayer();
    SetDrawTarget(nLayerBackground);
    Clear(olc::BLANK);

    SetPixelMode(olc::Pixel::ALPHA);
    DrawSprite({0, 0}, sprDeck, 1);
    SetPixelMode(olc::Pixel::NORMAL);
    EnableLayer(nLayerBackground, true);
    SetDrawTarget(nullptr);

    return true;
}
bool ChessGame::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::BLANK);
    notFound = true;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (deck[i][j] != empty && deck[i][j]->showType() == "pawn" && deck[i][j]->showColor()) // ret 1 if white else black 0
            {
                if (pSelected == &(deck[i][j]->olcPos))
                {
                    iTempIndex = i;
                    jTempIndex = j;
                    continue;
                }

                DrawDecal(deck[i][j]->olcPos, decPawnWhite);
            }
            else if (deck[i][j] != empty && deck[i][j]->showType() == "pawn")
            {
                if (pSelected == &(deck[i][j]->olcPos))
                {
                    iTempIndex = i;
                    jTempIndex = j;
                    continue;
                }
                DrawDecal(deck[i][j]->olcPos, decPawnBlack);
            }
            else if (deck[i][j] != empty && deck[i][j]->showType() == "queen" && deck[i][j]->showColor())
            {
                if (pSelected == &(deck[i][j]->olcPos))
                {
                    iTempIndex = i;
                    jTempIndex = j;
                    continue;
                }
                DrawDecal(deck[i][j]->olcPos, decQueenWhite);
            }
        }
    }
    if ((iTempIndex >= 0) && (jTempIndex >= 0))
    {
        if (deck[iTempIndex][jTempIndex]->showType() == "pawn" && deck[iTempIndex][jTempIndex]->showColor())
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decPawnWhite);
        else if (deck[iTempIndex][jTempIndex]->showType() == "pawn")
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decPawnBlack);
        else if (deck[iTempIndex][jTempIndex]->showType() == "queen" && deck[iTempIndex][jTempIndex]->showColor())
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decQueenWhite);

        iTempIndex = -1;
        jTempIndex = -1;
    }

    olc::vf2d mouse = {float(GetMouseX()), float(GetMouseY())};

    if (GetMouse(0).bPressed)
    {
        pSelected = nullptr;

        for (int i = 0; (i < 8) && (notFound); i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if ((deck[i][j] != empty) && ((mouse.x > deck[i][j]->olcPos.x) && (mouse.x < (deck[i][j]->olcPos.x + 80.0f))) && ((mouse.y > deck[i][j]->olcPos.y) && (mouse.y < (deck[i][j]->olcPos.y + 80.0f))))
                {
                    pSelected = &deck[i][j]->olcPos;
                    temp = deck[i][j]->olcPos;
                    initialPoint = {i, j, true};

                    logicOperation(initialPoint);
                    notFound = false;
                    break;
                }
            }
        }
        notFound = true;
    }

    if (GetMouse(0).bReleased && pSelected != nullptr)
    {
        for (int k = 0; k < points.size(); k++)
        {
            if (((mouse.x > (float)points[k].col * 80.0f) && (mouse.x < ((float)points[k].col * 80.0f + 80.0f))) && ((mouse.y > (float)points[k].row * 80.0f) && (mouse.y < ((float)points[k].row * 80.0f + 80.0f))))
            {
                if (toStep(Point{points[k].row, points[k].col}))
                {
                    for (int i = 0; (i < 8) && (notFound); i++)
                    {
                        for (int j = 0; j < 8; j++)
                        {
                            if ((deck[i][j] != empty) && ((float)points[k].col * 80.0f == deck[i][j]->olcPos.x) && ((float)points[k].row * 80.0f == deck[i][j]->olcPos.y))
                            {
                                deck[i][j] = empty;
                                notFound = false;
                                break;
                            }
                        }
                    }
                }
                *pSelected = {(float)points[k].col * 80.0f, (float)points[k].row * 80.0f};
                isFind = true;
                break;
            }
        }
        if (!isFind)
            *pSelected = temp;

        notFound = true;
        isFind = false;
        pSelected = nullptr;
        clearPoints();
    }

    if (pSelected != nullptr)
    {
        for (unsigned i = 0; i < points.size(); i++)
        {
            DrawRect(points[i].col * 80 + 2, points[i].row * 80 + 2, 75, 75, olc::VERY_DARK_GREEN);
            DrawRect(points[i].col * 80 + 3, points[i].row * 80 + 3, 73, 73, olc::GREEN);
        }
        *pSelected = (mouse - olc::vf2d{40.0f, 40.0f});
    }

    return true;
}

void ChessGame::clearPoints()
{
    points.clear();
}
