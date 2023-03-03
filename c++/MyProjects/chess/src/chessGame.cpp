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

void ChessGame::toStep(Point inPoint, Point endP)
{
    if (deck[inPoint.row][inPoint.col]->showType() == "king" && deck[inPoint.row][inPoint.col]->isInitial() && endP.row == 7 && endP.col == 7)
    {
        deck[7][6] = deck[inPoint.row][inPoint.col];
        deck[7][6]->olcPos.x = 480.0f;
        deck[7][6]->olcPos.y = 560.0f;

        deck[7][5] = deck[endP.row][endP.col];
        deck[7][5]->olcPos.x = 400.0f;
        deck[7][5]->olcPos.y = 560.0f;

        deck[inPoint.row][inPoint.col]->setInitial(false);
        deck[inPoint.row][inPoint.col] = empty;
        deck[endP.row][endP.col] = empty;
        saveBoard();
        return;
    }
    else if (deck[inPoint.row][inPoint.col]->showType() == "pawn" && inPoint.row == 3 && deck[inPoint.row][inPoint.col]->showColor() && endP.isAttack && deck[endP.row][endP.col] == empty)
    {
        deck[endP.row + 1][endP.col] = empty;
    }
    else if (deck[inPoint.row][inPoint.col]->showType() == "pawn" && inPoint.row == 4 && !deck[inPoint.row][inPoint.col]->showColor() && endP.isAttack && deck[endP.row][endP.col] == empty)
    {
        deck[endP.row - 1][endP.col] = empty;
    }
    deck[endP.row][endP.col] = deck[inPoint.row][inPoint.col];
    deck[inPoint.row][inPoint.col]->setInitial(false);
    deck[inPoint.row][inPoint.col] = empty;

    saveBoard();
}

void ChessGame::saveBoard()
{

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (deck[i][j] != nullptr)
            {
                if (deck[i][j]->showType() == "pawn")
                    tempBoard[i][j] = new Pawn;
                else if (deck[i][j]->showType() == "rook")
                    tempBoard[i][j] = new Rook;
                else if (deck[i][j]->showType() == "queen")
                    tempBoard[i][j] = new Queen;
                else if (deck[i][j]->showType() == "king")
                    tempBoard[i][j] = new King;

                *tempBoard[i][j] = *deck[i][j];
            }
            else
            {
                tempBoard[i][j] = empty;
            }
        }
    }
    deckNotation.push_back(tempBoard);
}
void ChessGame::stepBack()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (deckNotation[deckNotation.size() - 1][i][j] != nullptr)
            {
                delete deckNotation[deckNotation.size() - 1][i][j];
            }
            if (deckNotation[deckNotation.size() - 2][i][j] != nullptr)
            {
                deck[i][j] = deckNotation[deckNotation.size() - 2][i][j];
                deck[i][j]->olcPos.x = (float)j * 80.0f;
                deck[i][j]->olcPos.y = (float)i * 80.0f;
            }
            else
            {
                deck[i][j] = empty;
            }
        }
    }

    deckNotation.pop_back();
}

void ChessGame::getPossibleCells(const Point initialPoint, std::vector<Point> &points)
{
    Point step{0, 0, false};
    Point tempPoint{0, 0, true};

    Figures *elem = deck[initialPoint.row][initialPoint.col];

    elem->move(initialPoint.row, initialPoint.col, points); //      take all possible points of figures

    for (int i = 0; i < points.size(); i++)
    {
        if (elem->showType() == "pawn" && points[i].isAttack && (deck[points[i].row][points[i].col] == empty || ((deck[points[i].row][points[i].col] != empty) && (elem->showColor() == deck[points[i].row][points[i].col]->showColor()))))
        {
            if (deck[points[i].row][points[i].col] == empty && elem->showColor() && initialPoint.row == 3)
            {
                if ((deck[points[i].row + 1][points[i].col] != empty) && deck[points[i].row + 1][points[i].col]->showType() == "pawn" /* && Point{points[i].row - 1, points[i].col} == prevInitialPoint*/)
                    continue;
            }
            else if ((deck[points[i].row][points[i].col] == empty && !elem->showColor() && initialPoint.row == 4))
            {
                if ((deck[points[i].row - 1][points[i].col] != empty) && deck[points[i].row - 1][points[i].col]->showType() == "pawn" /*&& Point{points[i].row + 1, points[i].col} == prevInitialPoint*/)
                    continue;
            }

            points.erase(points.begin() + i);
            --i;
            continue;
        }

        if (deck[points[i].row][points[i].col] != empty && ((elem->showType() == "pawn" && !points[i].isAttack) || (elem->showType() != "pawn" && points[i].isAttack)))
        {
            if ((points[i].row - initialPoint.row) != 0)
                step.row = ((points[i].row - initialPoint.row) / abs(points[i].row - initialPoint.row));
            if ((points[i].col - initialPoint.col) != 0)
                step.col = ((points[i].col - initialPoint.col) / abs(points[i].col - initialPoint.col));

            tempPoint = points[i];

            if (elem->showColor() != deck[points[i].row][points[i].col]->showColor() && elem->showType() != "pawn")
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
bool ChessGame::WhiteCastling()
{
    std::vector<Point> tempPoints;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (deck[i][j] != empty && !deck[i][j]->showColor())
            {
                getPossibleCells(Point{i, j}, tempPoints);
                for (int k = 0; k < tempPoints.size(); k++)
                {
                    for (int f = 5; f < 7; f++)
                    {
                        if (deck[7][f] != empty)
                        {
                            return false;
                        }
                    }
                    for (int f = 4; f < 8; f++)
                    {
                        if (deck[i][j]->showType() == "pawn" && i == 6 && j > 2)
                        {
                            return false;
                        }
                        if (tempPoints[k].row == 7 && tempPoints[k].col == f && tempPoints[k].isAttack)
                        {
                            return false;
                        }
                        if (isWhiteCheck())
                        {
                            return false;
                        }
                    }
                }
                clearPoints(tempPoints);
            }
        }
    }
    return true;
}

void ChessGame::checkAnalisysPoints()
{
    for (int i = 0; i < points.size(); i++)
    {
        toStep(initialPoint, points[i]);

        if ((deck[points[i].row][points[i].col]->showColor() && isWhiteCheck()) || (!deck[points[i].row][points[i].col]->showColor() && isBlackCheck()))
        {
            points.erase(points.begin() + i);
            --i;
        }
        stepBack();
        deckNotation.pop_back();
    }
}

bool ChessGame::isBlackCheck()
{
    std::vector<Point> blackPossibleSteps;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (deck[i][j] != empty && deck[i][j]->showColor())
            {
                clearPoints(blackPossibleSteps);
                getPossibleCells(Point{i, j}, blackPossibleSteps);

                for (int k = 0; k < blackPossibleSteps.size(); k++)
                {
                    if ((deck[blackPossibleSteps[k].row][blackPossibleSteps[k].col] != empty) && blackPossibleSteps[k].isAttack && deck[blackPossibleSteps[k].row][blackPossibleSteps[k].col]->showColor() != deck[i][j]->showColor() && (deck[blackPossibleSteps[k].row][blackPossibleSteps[k].col]->showType() == "king"))
                    {
                        checkPosition = blackPossibleSteps[k];
                        return true;
                    }
                }
            }
        }
    }
    return false;
}
bool ChessGame::isWhiteCheck()
{
    std::vector<Point> whitePossibleSteps;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (deck[i][j] != empty && !deck[i][j]->showColor())
            {
                clearPoints(whitePossibleSteps);
                getPossibleCells(Point{i, j}, whitePossibleSteps);

                for (int k = 0; k < whitePossibleSteps.size(); k++)
                {
                    if ((deck[whitePossibleSteps[k].row][whitePossibleSteps[k].col] != empty) && whitePossibleSteps[k].isAttack && deck[whitePossibleSteps[k].row][whitePossibleSteps[k].col]->showColor() != deck[i][j]->showColor() && (deck[whitePossibleSteps[k].row][whitePossibleSteps[k].col]->showType() == "king"))
                    {
                        checkPosition = whitePossibleSteps[k];
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool ChessGame::isCheckOnBoard()
{
    return (isBlackCheck() || isWhiteCheck());
}

bool ChessGame::OnUserCreate()
{
    saveBoard();

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

    if (GetKey(olc::LEFT).bPressed)
    {
        if (deckNotation.size() > 1)
        {
            turn = !turn;
            stepBack();
        }
    }

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

        for (int i = 0; (i < 8) && (pSelected == nullptr); i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if ((deck[i][j] != empty) && ((mouse.x > deck[i][j]->olcPos.x) && (mouse.x < (deck[i][j]->olcPos.x + 80.0f))) && ((mouse.y > deck[i][j]->olcPos.y) && (mouse.y < (deck[i][j]->olcPos.y + 80.0f))))
                {
                    if (turn == deck[i][j]->showColor())
                    {

                        pSelected = &deck[i][j]->olcPos;
                        temp = deck[i][j]->olcPos;

                        initialPoint = Point{i, j};

                        clearPoints(points);
                        getPossibleCells(initialPoint, points);
                        // checkAnalisysPoints();

                        if (deck[i][j]->showType() == "king" && deck[i][j]->isInitial() & deck[i][j]->showColor() && deck[7][7] != empty && deck[7][7]->showType() == "rook" && deck[7][7]->isInitial())
                        {
                            if (WhiteCastling())
                            {
                                points.push_back(Point{7, 7, false});
                            }
                        }

                        break;
                    }
                }
            }
        }
    }

    if (GetMouse(0).bReleased && pSelected != nullptr)
    {
        for (int k = 0; k < points.size(); k++)
        {
            if (((mouse.x > (float)points[k].col * 80.0f) && (mouse.x < ((float)points[k].col * 80.0f + 80.0f))) && ((mouse.y > (float)points[k].row * 80.0f) && (mouse.y < ((float)points[k].row * 80.0f + 80.0f))))
            {
                *pSelected = {(float)points[k].col * 80.0f, (float)points[k].row * 80.0f};

                toStep(initialPoint, points[k]);

                isFind = true;
                turn = !turn;
                break;
            }
        }
        if (!isFind)
            *pSelected = temp;

        isFind = false;
        pSelected = nullptr;
    }

    if (isCheckOnBoard())
    {
        DrawRect(checkPosition.col * 80 + 2, checkPosition.row * 80 + 2, 75, 75, olc::VERY_DARK_RED);
        DrawRect(checkPosition.col * 80 + 3, checkPosition.row * 80 + 3, 73, 73, olc::RED);
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

void ChessGame::clearPoints(std::vector<Point> &points)
{
    points.clear();
}
