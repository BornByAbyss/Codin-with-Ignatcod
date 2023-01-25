#include <iostream>
#include <iomanip>
#include <vector>
#include "point.h"
#include "figures.h"
#include "deck.h"

namespace chesslogix
{
    Deck::Deck()
    {
        pawnB.set(false, "pB");
        pawnW.set(true, "pW");
        rookB.set(false, "rB");
        rookW.set(true, "rW");
        knightB.set(false, "kB");
        knightW.set(true, "kW");
        bishopB.set(false, "bB");
        bishopW.set(true, "bW");
        queenB.set(false, "QB");
        queenW.set(true, "QW");
        kingB.set(false, "KB");
        kingW.set(true, "KW");
    }

    void Deck::makeAstep(Point endP)
    {
        deck[endP.row][endP.col] = deck[begP.row][begP.col];
        deck[begP.row][begP.col] = empty;
    }

    void Deck::logicOperation(std::string currentPos)
    {
        Point step{0, 0, 0};
        bool last = false;
        int col_, row_;
        int c, r;
        int column = currentPos[0] - 'a'; //
        int row = '8' - currentPos[1];    //      deck notation into massive notation
                                          //      deck notation into massive notation

        begP.col = column;
        begP.row = row;
        begP.isAttack = false;

        Figures *elem = deck[row][column];
        if (elem != empty)
        {
            elem->move(row, column, points); //      take all possible points of figures
            for (int i = 0; i < points.size(); ++i)
            {
                col_ = points[i].col;
                row_ = points[i].row;

                if ((col_ >= 8) || (col_ < 0) || (row_ >= 8) || (row_ < 0))
                { /*Check for range*/
                    points.erase(points.begin() + i);
                    --i;
                    continue;
                }

                if ((points[i].isAttack) && (deck[row_][col_] != empty) && (deck[row_][col_]->showColor() != elem->showColor()))
                {
                    /*if isAttack and we have an enemy*/
                    if (col_ != 0)
                        step.col = ((col_ - column) / abs(col_ - column));
                    if (row_ != 0)
                        step.row = ((row_ - row) / abs(row_ - row));

                    c = col_;
                    r = row_;
                    while ((c < 8) && (c >= 0) && (r < 8) && (r >= 0))
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

                        if ((points[i].col == c && points[i].row == r) || ((col_ >= 8) || (col_ < 0) || (row_ >= 8) || (row_ < 0)))
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
                    if (col_ != 0)
                        step.col = ((col_ - column) / abs(col_ - column));
                    if (row_ != 0)
                        step.row = ((row_ - row) / abs(row_ - row));

                    c = col_;
                    r = row_;

                    while ((c < 8) && (c >= 0) && (r < 8) && (r >= 0))
                    {
                        if ((points[i].col == c && points[i].row == r) || ((col_ >= 8) || (col_ < 0) || (row_ >= 8) || (row_ < 0)))
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

    void Deck::clearPoints()
    {
        points.clear();
    }

    std::vector<Point> Deck::takeVpoints()
    {
        return points;
    }
}