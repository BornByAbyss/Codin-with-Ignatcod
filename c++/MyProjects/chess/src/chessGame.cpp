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
    pawnW1.set(true, "pB", 0.0f, 480.0);
    pawnW2.set(true, "pB", 80.0f, 480.0);
    pawnW3.set(true, "pB", 160.0f, 480.0);
    pawnW4.set(true, "pB", 240.0f, 480.0);
    pawnW5.set(true, "pB", 320.0f, 480.0);
    pawnW6.set(true, "pB", 400.0f, 480.0);
    pawnW7.set(true, "pB", 480.0f, 480.0);
    pawnW8.set(true, "pB", 560.0f, 480.0);

    pawnB1.set(false, "pB", 0.0f, 80.0);
    pawnB2.set(false, "pB", 80.0f, 80.0);
    pawnB3.set(false, "pB", 160.0f, 80.0);
    pawnB4.set(false, "pB", 240.0f, 80.0);
    pawnB5.set(false, "pB", 320.0f, 80.0);
    pawnB6.set(false, "pB", 400.0f, 80.0);
    pawnB7.set(false, "pB", 480.0f, 80.0);
    pawnB8.set(false, "pB", 560.0f, 80.0);
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
    Point step{0, 0, 0};
    bool last = false;
    int col_, row_;
    int c, r;

    begP.col = initialPoint.col;
    begP.row = initialPoint.row;
    begP.isAttack = false;

    Figures *elem = deck[initialPoint.row][initialPoint.col];

    if (elem != empty)
    {
        elem->move(initialPoint.row, initialPoint.col, points); //      take all possible points of figures
        for (int i = 0; i < points.size(); ++i)
        {
            col_ = points[i].col;
            row_ = points[i].row; // take column and row fo everu point

            if ((col_ >= 8) || (col_ < 0) || (row_ >= 8) || (row_ < 0))
            { /*Check for range*/
                points.erase(points.begin() + i);
                --i;
                continue;
            }

            if ((points[i].isAttack) && (deck[row_][col_] != empty) && (deck[row_][col_]->showColor() != elem->showColor()))
            {
                /*if isAttack and we have an enemy*/
                if ((col_ - initialPoint.col) != 0)
                    step.col = ((col_ - initialPoint.col) / abs(col_ - initialPoint.col));
                if ((row_ - initialPoint.row) != 0)
                    step.row = ((row_ - initialPoint.row) / abs(row_ - initialPoint.row));

                c = col_;
                r = row_;
                while (true)
                {
                    c += step.col;
                    r += step.row;
                    if (i < (points.size() - 1))
                    {
                        ++i;
                    }
                    else
                    {
                        last = true;
                        break;
                    }

                    if ((i >= 0) && (i < points.size()) && (points[i].col == c && points[i].row == r) || ((col_ >= 8) || (col_ < 0) || (row_ >= 8) || (row_ < 0)))
                        points.erase(points.begin() + i);
                    else
                        break;
                }
                if (!last)
                    --i;
                continue;
            }
            else if ((points[i].isAttack) && (deck[row_][col_] == empty) && ('p' == elem->showType()[0]))
            {
                points.erase(points.begin() + i); // special for pawn and empty space
                --i;
                continue;
            }

            // if isAttack = true or false and the same colors
            // i suppose it can work for Knight too
            if (deck[row_][col_] != empty)
            {
                if ((col_ - initialPoint.col) != 0)
                    step.col = ((col_ - initialPoint.col) / abs(col_ - initialPoint.col));
                if ((row_ - initialPoint.row) != 0)
                    step.row = ((row_ - initialPoint.row) / abs(row_ - initialPoint.row));

                c = col_;
                r = row_;

                while (true)
                {
                    if ((i >= 0) && (i < points.size()) && ((points[i].col == c && points[i].row == r) || ((col_ >= 8) || (col_ < 0) || (row_ >= 8) || (row_ < 0))))
                        points.erase(points.begin() + i);
                    else
                        break;
                    c += step.col;
                    r += step.row;
                }
                --i;
            }
        }
    }
}

bool ChessGame::OnUserCreate()
{
    sprDeck = new olc::Sprite("./images/deck.png");

    sprPawnWhite = new olc::Sprite("./images/pawn.png");
    sprPawnBlack = new olc::Sprite("./images/pawnBlack.png");

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
            if ((deck[i][j] != empty) && deck[i][j]->showColor()) // ret 1 if white else black 0
            {
                if (pSelected == &(deck[i][j]->olcPos))
                {
                    iTempIndex = i;
                    jTempIndex = j;
                    continue;
                }
                
                DrawDecal(deck[i][j]->olcPos, decPawnWhite);
            }
            else if (deck[i][j] != empty)
            {
                if (pSelected == &(deck[i][j]->olcPos))
                {
                    iTempIndex = i;
                    jTempIndex = j;
                    continue;
                }
                DrawDecal(deck[i][j]->olcPos, decPawnBlack);
            }
        }
    }
    if ((iTempIndex >= 0) && (jTempIndex >= 0))
    {
        if (deck[iTempIndex][jTempIndex]->showColor())
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decPawnWhite);
        else
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decPawnBlack);

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
            DrawRect(points[i].col * 80 + 2, points[i].row * 80 + 2, 75, 75, olc::VERY_DARK_CYAN);
            DrawRect(points[i].col * 80 + 3, points[i].row * 80 + 3, 73, 73, olc::CYAN);
        }
        *pSelected = (mouse - olc::vf2d{40.0f, 40.0f});
    }

    return true;
}

void ChessGame::clearPoints()
{
    points.clear();
}
