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

    bool Deck::toStep(Point endP)
    { // 0 - empty  1 - enemy
        bool isAnyBodyOutThere = false;
        if (deck[endP.row][endP.col] != empty)
            isAnyBodyOutThere = true;
        deck[endP.row][endP.col] = deck[begP.row][begP.col];
        deck[begP.row][begP.col] = empty;
        return isAnyBodyOutThere;
    }

    void Deck::logicOperation(Point initialPoint)
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

    void Deck::clearPoints()
    {
        points.clear();
    }

    std::vector<Point> Deck::takePoints()
    {
        return points;
    }
}