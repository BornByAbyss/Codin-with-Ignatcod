

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

    bishopB1.set(false, "bishop", 160.0f, 0.0f);
    bishopB2.set(false, "bishop", 400.0f, 0.0f);
    bishopW1.set(true, "bishop", 160.0f, 560.0f);
    bishopW2.set(true, "bishop", 400.0f, 560.0f);

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

    knightB1.set(false, "knight", 80.0f, 0.0f);
    knightB2.set(false, "knight", 480.0f, 0.0f);
    knightW1.set(true, "knight", 80.0f, 560.0f);
    knightW2.set(true, "knight", 480.0f, 560.0f);
}

void ChessGame::toStep(Point initialPosition, Point finalPosition, bool bl)
{
    if (bl)
        prevInitialPoint = initialPosition;
    if (deck[initialPosition.row][initialPosition.col]->showType() == "king" && deck[initialPosition.row][initialPosition.col]->showColor() && deck[initialPosition.row][initialPosition.col]->isInitial() && finalPosition.row == 7 && finalPosition.col == 7)
    {

        deck[7][6] = deck[initialPosition.row][initialPosition.col];
        deck[7][6]->olcPos.x = 480.0f;
        deck[7][6]->olcPos.y = 560.0f;

        deck[7][5] = deck[finalPosition.row][finalPosition.col];
        deck[7][5]->olcPos.x = 400.0f;
        deck[7][5]->olcPos.y = 560.0f;

        deck[initialPosition.row][initialPosition.col] = empty;
        deck[finalPosition.row][finalPosition.col] = empty;
        saveBoard();
        if (bl)
        {
            deck[7][6]->setInitial(false);
            deck[7][5]->setInitial(false);
        }

        return;
    }
    else if (deck[initialPosition.row][initialPosition.col]->showType() == "king" && deck[initialPosition.row][initialPosition.col]->showColor() && deck[initialPosition.row][initialPosition.col]->isInitial() && finalPosition.row == 7 && finalPosition.col == 0)
    {
        deck[7][2] = deck[initialPosition.row][initialPosition.col];
        deck[7][2]->olcPos.x = 160.0f;
        deck[7][2]->olcPos.y = 560.0f;

        deck[7][3] = deck[finalPosition.row][finalPosition.col];
        deck[7][3]->olcPos.x = 240.0f;
        deck[7][3]->olcPos.y = 560.0f;

        deck[initialPosition.row][initialPosition.col] = empty;
        deck[finalPosition.row][finalPosition.col] = empty;
        saveBoard();
        if (bl)
        {
            deck[7][3]->setInitial(false);
            deck[7][2]->setInitial(false);
        }

        return;
    }
    else if (deck[initialPosition.row][initialPosition.col]->showType() == "king" && !deck[initialPosition.row][initialPosition.col]->showColor() && deck[initialPosition.row][initialPosition.col]->isInitial() && finalPosition.row == 0 && finalPosition.col == 7)
    {

        deck[0][6] = deck[initialPosition.row][initialPosition.col];
        deck[0][6]->olcPos.x = 480.0f;
        deck[0][6]->olcPos.y = 0.0f;

        deck[0][5] = deck[finalPosition.row][finalPosition.col];
        deck[0][5]->olcPos.x = 400.0f;
        deck[0][5]->olcPos.y = 0.0f;

        deck[initialPosition.row][initialPosition.col] = empty;
        deck[finalPosition.row][finalPosition.col] = empty;
        saveBoard();
        if (bl)
        {
            deck[0][6]->setInitial(false);
            deck[0][5]->setInitial(false);
        }

        return;
    }
    else if (deck[initialPosition.row][initialPosition.col]->showType() == "king" && !deck[initialPosition.row][initialPosition.col]->showColor() && deck[initialPosition.row][initialPosition.col]->isInitial() && finalPosition.row == 0 && finalPosition.col == 0)
    {

        deck[0][2] = deck[initialPosition.row][initialPosition.col];
        deck[0][2]->olcPos.x = 160.0f;
        deck[0][2]->olcPos.y = 0.0f;

        deck[0][3] = deck[finalPosition.row][finalPosition.col];
        deck[0][3]->olcPos.x = 240.0f;
        deck[0][3]->olcPos.y = 0.0f;

        deck[initialPosition.row][initialPosition.col] = empty;
        deck[finalPosition.row][finalPosition.col] = empty;
        saveBoard();
        if (bl)
        {
            deck[0][3]->setInitial(false);
            deck[0][2]->setInitial(false);
        }

        return;
    }
    else if (deck[initialPosition.row][initialPosition.col]->showType() == "pawn" && initialPosition.row == 3 && deck[initialPosition.row][initialPosition.col]->showColor() && finalPosition.isAttack && deck[finalPosition.row][finalPosition.col] == empty)
        deck[finalPosition.row + 1][finalPosition.col] = empty;

    else if (deck[initialPosition.row][initialPosition.col]->showType() == "pawn" && initialPosition.row == 4 && !deck[initialPosition.row][initialPosition.col]->showColor() && finalPosition.isAttack && deck[finalPosition.row][finalPosition.col] == empty)
        deck[finalPosition.row - 1][finalPosition.col] = empty;

    deck[finalPosition.row][finalPosition.col] = deck[initialPosition.row][initialPosition.col];
    deck[initialPosition.row][initialPosition.col] = empty;

    saveBoard();
    if (bl)
        deck[finalPosition.row][finalPosition.col]->setInitial(false);
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
                else if (deck[i][j]->showType() == "knight")
                    tempBoard[i][j] = new Knight;
                else if (deck[i][j]->showType() == "bishop")
                    tempBoard[i][j] = new Bishop;

                *tempBoard[i][j] = *deck[i][j];
            }
            else
            {
                tempBoard[i][j] = empty;
            }
        }
    }
    deckNotation.push_back(tempBoard);
    deck = deckNotation[deckNotation.size() - 1];
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
                deck[i][j]->setInitial(deckNotation[deckNotation.size() - 2][i][j]->isInitial());
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
                if ((deck[points[i].row + 1][points[i].col] != empty) && deck[points[i].row + 1][points[i].col]->showType() == "pawn" && Point{points[i].row - 1, points[i].col} == prevInitialPoint)
                    continue;
            }
            else if ((deck[points[i].row][points[i].col] == empty && !elem->showColor() && initialPoint.row == 4))
            {
                if ((deck[points[i].row - 1][points[i].col] != empty) && deck[points[i].row - 1][points[i].col]->showType() == "pawn" && Point{points[i].row + 1, points[i].col} == prevInitialPoint)
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

void ChessGame::blackCastling()
{
    bool rightWing = true;
    bool leftWing = true;

    std::vector<Point> tempPoints;
    if (deck[0][4] != nullptr && deck[0][4]->showType() == "king" && deck[0][4]->isInitial() && !deck[0][4]->showColor() && deck[0][7] != empty && deck[0][7]->showType() == "rook" && deck[0][7]->isInitial())
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (deck[i][j] != empty && deck[i][j]->showColor())
                {
                    if ((deck[i][j]->showType() == "pawn" && i == 1 && j > 2))
                    {
                        rightWing = false;
                    }
                    if ((deck[i][j]->showType() == "pawn" && i == 1 && j < 6))
                    {
                        leftWing = false;
                    }

                    getPossibleCells(Point{i, j}, tempPoints);
                    for (int k = 0; k < tempPoints.size(); k++)
                    {

                        for (int f = 1; f < 4; f++)
                        {
                            if (deck[0][f] != empty)
                            {
                                leftWing = false;
                            }
                        }

                        for (int f = 5; f < 7; f++)
                        {
                            if (deck[0][f] != empty)
                            {
                                rightWing = false;
                            }
                        }
                        for (int f = 0; f < 5; f++)
                        {
                            if ((tempPoints[k].row == 0 && tempPoints[k].col == f && tempPoints[k].isAttack))
                            {
                                leftWing = false;
                            }
                        }

                        for (int f = 4; f < 8; f++)
                        {
                            if ((tempPoints[k].row == 0 && tempPoints[k].col == f && tempPoints[k].isAttack))
                            {
                                rightWing = false;
                            }
                        }
                    }
                    clearPoints(tempPoints);
                }
            }
        }
        if (rightWing)
            points.push_back(Point{0, 7, false});
        if (leftWing)
            points.push_back(Point{0, 0, false});
    }
}
void ChessGame::whiteCastling()
{
    bool rightWing = true;
    bool leftWing = true;

    std::vector<Point> tempPoints;
    if (deck[7][4] != nullptr && deck[7][4]->showType() == "king" && deck[7][4]->isInitial() && deck[7][4]->showColor() && ((deck[7][7] != empty && deck[7][7]->showType() == "rook" && deck[7][7]->isInitial()) || (deck[7][0] != empty && deck[7][0]->showType() == "rook" && deck[7][0]->isInitial())))
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                if (deck[i][j] != empty && !deck[i][j]->showColor())
                {
                    if ((deck[i][j]->showType() == "pawn" && i == 6 && j > 2))
                    {
                        rightWing = false;
                    }
                    if ((deck[i][j]->showType() == "pawn" && i == 6 && j < 6))
                    {
                        leftWing = false;
                    }

                    getPossibleCells(Point{i, j}, tempPoints);
                    for (int k = 0; k < tempPoints.size(); k++)
                    {

                        for (int f = 1; f < 4; f++)
                        {
                            if (deck[7][f] != empty)
                            {
                                leftWing = false;
                            }
                        }

                        for (int f = 5; f < 7; f++)
                        {
                            if (deck[7][f] != empty)
                            {
                                rightWing = false;
                            }
                        }
                        for (int f = 0; f < 5; f++)
                        {
                            if ((tempPoints[k].row == 7 && tempPoints[k].col == f && tempPoints[k].isAttack))
                            {
                                leftWing = false;
                            }
                        }

                        for (int f = 4; f < 8; f++)
                        {
                            if ((tempPoints[k].row == 7 && tempPoints[k].col == f && tempPoints[k].isAttack))
                            {
                                rightWing = false;
                            }
                        }
                    }
                    clearPoints(tempPoints);
                }
            }
        }
    }
    else
    {
        rightWing = false;
        leftWing = false;
    }
    if (rightWing)
        points.push_back(Point{7, 7, false});
    if (leftWing)
        points.push_back(Point{7, 0, false});
}

void ChessGame::checkAnalisysPoints()
{
    for (int i = 0; i < points.size(); i++)
    {
        toStep(initialPoint, points[i], false);

        if ((deck[points[i].row][points[i].col]->showColor() && isWhiteCheck()) || (!deck[points[i].row][points[i].col]->showColor() && isBlackCheck()))
        {
            points.erase(points.begin() + i);
            --i;
        }
        stepBack();
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
                getPossibleCells(Point{i, j}, blackPossibleSteps);

                for (int k = 0; k < blackPossibleSteps.size(); k++)
                {
                    if ((deck[blackPossibleSteps[k].row][blackPossibleSteps[k].col] != empty) && blackPossibleSteps[k].isAttack && deck[blackPossibleSteps[k].row][blackPossibleSteps[k].col]->showColor() != deck[i][j]->showColor() && (deck[blackPossibleSteps[k].row][blackPossibleSteps[k].col]->showType() == "king"))
                    {
                        checkPosition = blackPossibleSteps[k];
                        return true;
                    }
                }
                clearPoints(blackPossibleSteps);
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
                getPossibleCells(Point{i, j}, whitePossibleSteps);

                for (int k = 0; k < whitePossibleSteps.size(); k++)
                {
                    if ((deck[whitePossibleSteps[k].row][whitePossibleSteps[k].col] != empty) && whitePossibleSteps[k].isAttack && deck[whitePossibleSteps[k].row][whitePossibleSteps[k].col]->showColor() != deck[i][j]->showColor() && (deck[whitePossibleSteps[k].row][whitePossibleSteps[k].col]->showType() == "king"))
                    {
                        checkPosition = whitePossibleSteps[k];
                        return true;
                    }
                }
                clearPoints(whitePossibleSteps);
            }
        }
    }
    return false;
}

bool ChessGame::isCheckMate()
{
    std::vector<Point> PossibleSteps;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (deck[i][j] != empty)
            {
                getPossibleCells(Point{i, j}, PossibleSteps);

                for (int k = 0; k < PossibleSteps.size(); k++)
                {
                    toStep(Point{i, j}, PossibleSteps[k], false);

                    if ((deck[PossibleSteps[k].row][PossibleSteps[k].col]->showColor() && isWhiteCheck()) || (!deck[PossibleSteps[k].row][PossibleSteps[k].col]->showColor() && isBlackCheck()))
                    {
                        PossibleSteps.erase(PossibleSteps.begin() + i);
                        --i;
                    }
                    stepBack();
                }
                if (PossibleSteps.size() > 0)
                    return false;
            }
        }
    }
    return true;
}

bool ChessGame::isCheckOnBoard()
{
    return (isBlackCheck() || isWhiteCheck());
}

void ChessGame::selector(const olc::vf2d posSelector)
{
}

bool ChessGame::OnUserCreate()
{
    deck = {{&rookB1, &knightB1, &bishopB1, &queenB, &kingB, &bishopB2, &knightB2, &rookB2},
            {&pawnB1, &pawnB2, &pawnB3, &pawnB4, &pawnB5, &pawnB6, &pawnB7, &pawnB8},
            {empty, empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty, empty},
            {empty, empty, empty, empty, empty, empty, empty, empty},
            {&pawnW1, &pawnW2, &pawnW3, &pawnW4, &pawnW5, &pawnW6, &pawnW7, &pawnW8},
            {&rookW1, &knightW1, &bishopW1, &queenW, &kingW, &bishopW2, &knightW2, &rookW2}};
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

    sprKnightWhite = new olc::Sprite("./images/knightWhite.png");
    sprKnightBlack = new olc::Sprite("./images/knightBlack.png");

    sprBishopWhite = new olc::Sprite("./images/bishopWhite.png");
    sprBishopBlack = new olc::Sprite("./images/bishopBlack.png");

    decBishopBlack = new olc::Decal(sprBishopBlack);
    decBishopWhite = new olc::Decal(sprBishopWhite);

    decKnightBlack = new olc::Decal(sprKnightBlack);
    decKnightWhite = new olc::Decal(sprKnightWhite);

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

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (isSelectorWhiteOn && deck[i][j] != empty && deck[i][j]->olcPos.x == (*pSelected).x && deck[i][j]->olcPos.y >= 0.0f && deck[i][j]->olcPos.y <= 320.0f)
                continue;
            else if (isSelectorBlackOn && deck[i][j] != empty && deck[i][j]->olcPos.x == (*pSelected).x && deck[i][j]->olcPos.y >= 320.0f && deck[i][j]->olcPos.y <= 640.0f)
                continue;

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

            else if (deck[i][j] != empty && deck[i][j]->showType() == "knight" && deck[i][j]->showColor())
                DrawDecal(deck[i][j]->olcPos, decKnightWhite);

            else if (deck[i][j] != empty && deck[i][j]->showType() == "knight")
                DrawDecal(deck[i][j]->olcPos, decKnightBlack);

            else if (deck[i][j] != empty && deck[i][j]->showType() == "bishop" && deck[i][j]->showColor())
                DrawDecal(deck[i][j]->olcPos, decBishopWhite);

            else if (deck[i][j] != empty && deck[i][j]->showType() == "bishop")
                DrawDecal(deck[i][j]->olcPos, decBishopBlack);
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

        else if (deck[iTempIndex][jTempIndex]->showType() == "knight" && deck[iTempIndex][jTempIndex]->showColor())
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decKnightWhite);

        else if (deck[iTempIndex][jTempIndex]->showType() == "knight")
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decKnightBlack);

        else if (deck[iTempIndex][jTempIndex]->showType() == "bishop" && deck[iTempIndex][jTempIndex]->showColor())
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decBishopWhite);

        else if (deck[iTempIndex][jTempIndex]->showType() == "bishop")
            DrawDecal(deck[iTempIndex][jTempIndex]->olcPos, decBishopBlack);

        iTempIndex = -1;
        jTempIndex = -1;
    }
    olc::vf2d mouse = {float(GetMouseX()), float(GetMouseY())};

    if (isSelectorWhiteOn)
    {
        FillRect((*pSelected).x, 0.0f, 80.0f, 320.0f, olc::GREY);
        DrawDecal(olc::vf2d{(*pSelected).x, (*pSelected).y}, decQueenWhite, {(0.5f), (0.5f)});
        DrawDecal(olc::vf2d{(*pSelected).x, (*pSelected).y + 80.0f}, decRookWhite);
        DrawDecal(olc::vf2d{(*pSelected).x, (*pSelected).y + 160.0f}, decKnightWhite);
        DrawDecal(olc::vf2d{(*pSelected).x, (*pSelected).y + 240.0f}, decBishopWhite);

        if (GetMouse(0).bPressed)
        {
            if (((mouse.x > (*pSelected).x) && (mouse.x < (*pSelected).x + 80.0f)) && ((mouse.y > (*pSelected).y) && (mouse.y < (*pSelected).y + 80.0f)))
            {
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80] = new Queen;
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80]->set(true, "queen", (*pSelected).x, (*pSelected).y);
                isSelectorWhiteOn = false;
                saveBoard();
            }
            else if (((mouse.x > (*pSelected).x) && (mouse.x < (*pSelected).x + 80.0f)) && ((mouse.y > (*pSelected).y + 80.0f) && (mouse.y < (*pSelected).y + 160.0f)))
            {
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80] = new Rook;
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80]->set(true, "rook", (*pSelected).x, (*pSelected).y);
                isSelectorWhiteOn = false;
                saveBoard();
            }
            else if (((mouse.x > (*pSelected).x) && (mouse.x < (*pSelected).x + 80.0f)) && ((mouse.y > (*pSelected).y + 160.0f) && (mouse.y < (*pSelected).y + 240.0f)))
            {
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80] = new Knight;
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80]->set(true, "knight", (*pSelected).x, (*pSelected).y);
                isSelectorWhiteOn = false;
                saveBoard();
            }
            else if (((mouse.x > (*pSelected).x) && (mouse.x < (*pSelected).x + 80.0f)) && ((mouse.y > (*pSelected).y + 240.0f) && (mouse.y < (*pSelected).y + 320.0f)))
            {
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80] = new Bishop;
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80]->set(true, "bishop", (*pSelected).x, (*pSelected).y);
                isSelectorWhiteOn = false;
                saveBoard();
            }

            else
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    else if (isSelectorBlackOn)
    {
        FillRect((*pSelected).x, 320.0f, 80.0f, 320.0f, olc::GREY);
        DrawDecal(olc::vf2d{(*pSelected).x, (*pSelected).y}, decQueenBlack, {(0.5f), (0.5f)});
        DrawDecal(olc::vf2d{(*pSelected).x, (*pSelected).y - 80.0f}, decRookBlack);
        DrawDecal(olc::vf2d{(*pSelected).x, (*pSelected).y - 160.0f}, decKnightBlack);
        DrawDecal(olc::vf2d{(*pSelected).x, (*pSelected).y - 240.0f}, decBishopBlack);

        if (GetMouse(0).bPressed)
        {
            if (((mouse.x > (*pSelected).x) && (mouse.x < (*pSelected).x + 80.0f)) && ((mouse.y < (*pSelected).y + 80.0f) && (mouse.y > (*pSelected).y)))
            {
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80] = new Queen;
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80]->set(false, "queen", (*pSelected).x, (*pSelected).y);
                isSelectorBlackOn = false;
                saveBoard();
            }
            else if (((mouse.x > (*pSelected).x) && (mouse.x < (*pSelected).x + 80.0f)) && ((mouse.y < (*pSelected).y) && (mouse.y > (*pSelected).y - 80.0f)))
            {
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80] = new Rook;
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80]->set(false, "rook", (*pSelected).x, (*pSelected).y);
                isSelectorBlackOn = false;
                saveBoard();
            }
            else if (((mouse.x > (*pSelected).x) && (mouse.x < (*pSelected).x + 80.0f)) && ((mouse.y < (*pSelected).y - 80.0f) && (mouse.y > (*pSelected).y - 160.0f)))
            {
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80] = new Knight;
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80]->set(false, "knight", (*pSelected).x, (*pSelected).y);
                isSelectorBlackOn = false;
                saveBoard();
            }
            else if (((mouse.x > (*pSelected).x) && (mouse.x < (*pSelected).x + 80.0f)) && ((mouse.y < (*pSelected).y - 160.0f) && (mouse.y > (*pSelected).y - 240.0f)))
            {
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80] = new Bishop;
                deck[((int)(*pSelected).y) / 80][((int)(*pSelected).x) / 80]->set(false, "bishop", (*pSelected).x, (*pSelected).y);
                isSelectorBlackOn = false;
                saveBoard();
            }

            else
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }

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
                        initialPoint = Point{i, j};
                        clearPoints(points);
                        getPossibleCells(initialPoint, points);

                        checkAnalisysPoints();

                        if (deck[i][j]->showType() == "king" && deck[i][j]->showColor())
                            whiteCastling();
                        else if (deck[i][j]->showType() == "king" && !deck[i][j]->showColor())
                            blackCastling();

                        pSelected = &deck[i][j]->olcPos;
                        temp = deck[i][j]->olcPos;

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

                turn = !turn;

                if (deck[initialPoint.row][initialPoint.col]->showType() == "pawn" && deck[initialPoint.row][initialPoint.col]->showColor() && points[k].row == 0)
                {
                    deck[initialPoint.row][initialPoint.col] = empty;
                    isSelectorWhiteOn = true;
                    return true;
                }
                else if (deck[initialPoint.row][initialPoint.col]->showType() == "pawn" && !deck[initialPoint.row][initialPoint.col]->showColor() && points[k].row == 7)
                {
                    deck[initialPoint.row][initialPoint.col] = empty;
                    isSelectorBlackOn = true;
                    return true;
                }

                toStep(initialPoint, points[k], true);
                isFind = true;
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

    if (GetKey(olc::LEFT).bPressed)
    {
        if (deckNotation.size() > 1)
        {
            turn = !turn;
            stepBack();
            isSelectorWhiteOn = false;
            isSelectorBlackOn = false;
        }
    }

    return true;
}

void ChessGame::clearPoints(std::vector<Point> &points)
{
    points.clear();
}
