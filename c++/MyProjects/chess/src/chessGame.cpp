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

    queenW.set(true, "queen", 240.0f, 560.0f);
    queenB.set(false, "queen", 240.0f, 0.0f);

    rookW1.set(true, "rook", 0.0f, 560.0f);
    rookW2.set(true, "rook", 560.0f, 560.0f);

    rookB1.set(false, "rook", 0.0f, 0.0f);
    rookB2.set(false, "rook", 560.0f, 0.0f);

    kingW.set(true, "king", 320.0f, 560.0f);
    kingB.set(false, "king", 320.0f, 0.0f);
}
// Return 0 if step to empty else 1
void ChessGame::toStep(Point endP)
{

    if (deck[begP.row][begP.col]->showType() == "pawn" && deck[begP.row][begP.col]->showColor() && deck[begP.row][begP.col] && endP.isAttack && deck[endP.row][endP.col] == empty)
        deck[endP.row + 1][endP.col] = empty;
    else if (deck[begP.row][begP.col]->showType() == "pawn" && !deck[begP.row][begP.col]->showColor() && deck[begP.row][begP.col] && endP.isAttack && deck[endP.row][endP.col] == empty)
        deck[endP.row - 1][endP.col] = empty;

    prevStep = begP;

    deck[endP.row][endP.col] = deck[begP.row][begP.col];
    deck[begP.row][begP.col] = empty;
}

void ChessGame::logicOperation(Point initialPoint)
{
    Point step{0, 0, false};
    Point tempPoint{0, 0, true};

    begP.col = initialPoint.col;
    begP.row = initialPoint.row;
    begP.isAttack = false;

    Figures *elem = deck[initialPoint.row][initialPoint.col];

    elem->move(initialPoint.row, initialPoint.col, points); //      take all possible points of figures

    for (int i = 0; i < points.size(); i++)
    {
        if (elem->showType() == "pawn" && points[i].isAttack && (deck[points[i].row][points[i].col] == empty || ((deck[points[i].row][points[i].col] != empty) && (elem->showColor() == deck[points[i].row][points[i].col]->showColor()))))
        {
            if (deck[points[i].row][points[i].col] == empty && elem->showColor() && initialPoint.row == 3)
            {
                if ((deck[points[i].row + 1][points[i].col] != empty) && deck[points[i].row + 1][points[i].col]->showType() == "pawn" && Point{points[i].row - 1, points[i].col} == prevStep)
                    continue;
            }
            else if ((deck[points[i].row][points[i].col] == empty && !elem->showColor() && initialPoint.row == 4))
            {
                if ((deck[points[i].row - 1][points[i].col] != empty) && deck[points[i].row - 1][points[i].col]->showType() == "pawn" && Point{points[i].row + 1, points[i].col} == prevStep)
                    continue;
            }

            points.erase(points.begin() + i);
            --i;
            continue;
        }
        else if (deck[points[i].row][points[i].col] != empty && ((elem->showType() == "pawn" && !points[i].isAttack) || (elem->showType() != "pawn" && points[i].isAttack)))
        {
            if ((points[i].row - initialPoint.row) != 0)
                step.row = ((points[i].row - initialPoint.row) / abs(points[i].row - initialPoint.row));
            if ((points[i].col - initialPoint.col) != 0)
                step.col = ((points[i].col - initialPoint.col) / abs(points[i].col - initialPoint.col));

            tempPoint = points[i];

            if (elem->showColor() != deck[points[i].row][points[i].col]->showColor() && deck[points[i].row][points[i].col]->showType() != "king" && elem->showType() != "pawn")
            {
                tempPoint += step;
                i++;
            }
            while ((i < points.size()) && (tempPoint == points[i]))
            {
                points.erase(points.begin() + i);
                tempPoint += step;
            }
            step = {0, 0, true};
            i--;
        }
    }
}

bool ChessGame::OnUserCreate()
{
    sprDeck = new olc::Sprite("./images/deck.png");

    sprPawnWhite = new olc::Sprite("./images/pawnWhite.png");
    sprPawnBlack = new olc::Sprite("./images/pawnBlack.png");

    sprQueenWhite = new olc::Sprite("./images/queenWhite.png");
    sprQueenBlack = new olc::Sprite("./images/queenBlack.png");

    sprRookWhite = new olc::Sprite("./images/rookWhite.png");
    sprRookBlack = new olc::Sprite("./images/rookBlack.png");

    sprKingWhite = new olc::Sprite("./images/kingWhite.png");
    sprKingBlack = new olc::Sprite("./images/kingBlack.png");

    decQueenBlack = new olc::Decal(sprQueenBlack);
    decQueenWhite = new olc::Decal(sprQueenWhite);

    decRookBlack = new olc::Decal(sprRookBlack);
    decRookWhite = new olc::Decal(sprRookWhite);

    decPawnWhite = new olc::Decal(sprPawnWhite);
    decPawnBlack = new olc::Decal(sprPawnBlack);

    decKingWhite = new olc::Decal(sprKingWhite);
    decKingBlack = new olc::Decal(sprKingBlack);

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
            if (pSelected == &(deck[i][j]->olcPos))
            {
                iTempIndex = i;
                jTempIndex = j;
            }
            else if (deck[i][j] != empty && deck[i][j]->showType() == "pawn" && deck[i][j]->showColor())
                DrawDecal(deck[i][j]->olcPos, decPawnWhite);

            else if (deck[i][j] != empty && deck[i][j]->showType() == "pawn")
                DrawDecal(deck[i][j]->olcPos, decPawnBlack);

            else if (deck[i][j] != empty && deck[i][j]->showType() == "queen" && deck[i][j]->showColor())
                DrawDecal(deck[i][j]->olcPos, decQueenWhite, {(0.5f), (0.5f)});

            else if (deck[i][j] != empty && deck[i][j]->showType() == "queen")
                DrawDecal(deck[i][j]->olcPos, decQueenBlack, {(0.5f), (0.5f)});

            else if (deck[i][j] != empty && deck[i][j]->showType() == "rook" && deck[i][j]->showColor())
                DrawDecal(deck[i][j]->olcPos, decRookWhite);

            else if (deck[i][j] != empty && deck[i][j]->showType() == "rook")
                DrawDecal(deck[i][j]->olcPos, decRookBlack);

            else if (deck[i][j] != empty && deck[i][j]->showType() == "king" && deck[i][j]->showColor())
                DrawDecal(deck[i][j]->olcPos, decKingWhite);

            else if (deck[i][j] != empty && deck[i][j]->showType() == "king")
                DrawDecal(deck[i][j]->olcPos, decKingBlack);
        }
    }
    if ((iTempIndex >= 0) && (jTempIndex >= 0))
    {
        if (deck[iTempIndex][jTempIndex]->showType() == "pawn" && deck[iTempIndex][jTempIndex]->showColor())
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decPawnWhite);

        else if (deck[iTempIndex][jTempIndex]->showType() == "pawn")
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decPawnBlack);

        else if (deck[iTempIndex][jTempIndex]->showType() == "queen" && deck[iTempIndex][jTempIndex]->showColor())
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decQueenWhite, {(0.5f), (0.5f)});

        else if (deck[iTempIndex][jTempIndex]->showType() == "queen")
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decQueenBlack, {(0.5f), (0.5f)});

        else if (deck[iTempIndex][jTempIndex]->showType() == "rook" && deck[iTempIndex][jTempIndex]->showColor())
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decRookWhite);

        else if (deck[iTempIndex][jTempIndex]->showType() == "rook")
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decRookBlack);

        else if (deck[iTempIndex][jTempIndex]->showType() == "king" && deck[iTempIndex][jTempIndex]->showColor())
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decKingWhite);

        else if (deck[iTempIndex][jTempIndex]->showType() == "king")
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decKingBlack);

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
                toStep(points[k]);
                *pSelected = {(float)points[k].col * 80.0f, (float)points[k].row * 80.0f};
                isFind = true;
                break;
            }
        }
        if (!isFind)
            *pSelected = temp;

        isFind = false;
        pSelected = nullptr;
        clearPoints();
    }

    if (pSelected != nullptr)
    {
        for (unsigned i = 0; i < points.size(); i++)
        {
            DrawRect(points[i].col * 80 + 2, points[i].row * 80 + 2, 75, 75, olc::VERY_DARK_YELLOW);
            DrawRect(points[i].col * 80 + 3, points[i].row * 80 + 3, 73, 73, olc::YELLOW);
        }
        *pSelected = (mouse - olc::vf2d{40.0f, 40.0f});
    }

    return true;
}

void ChessGame::clearPoints()
{
    points.clear();
}
