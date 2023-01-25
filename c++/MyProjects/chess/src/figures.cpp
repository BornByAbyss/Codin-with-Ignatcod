#include <iostream>
#include <vector>
#include "point.h"
#include "figures.h"

namespace chesslogix
{

    void Figures::set(bool bl, std::string str)
    {
        isWhite = bl;
        type = str;
    }
    bool Figures::showColor() const
    {
        return isWhite;
    }
    std::string Figures::showType() const
    {
        return type;
    }

    std::ostream &operator<<(std::ostream &out, Figures &fig)
    {
        out << fig.type;
        return out;
    }

    void Pawn::move(int c1, int c2, std::vector<Point> &points)
    {
        Point point;
        Point point2;
        Point point3A;
        Point point4A;
        Point point5A;
        Point point6A;
        if (c1 == 6 && isWhite)
        {
            point.row = c1 - 1;
            point.col = c2;
            point.isAttack = (false);
            point2.row = c1 - 2;
            point2.col = c2;
            point2.isAttack = (false);
            points.push_back(point);
            points.push_back(point2);
        }
        else if (c1 == 1 && !isWhite)
        {
            point.row = c1 + 1;
            point.col = c2;
            point.isAttack = (false);
            point2.row = c1 + 2;
            point2.col = c2;
            point2.isAttack = (false);
            points.push_back(point);
            points.push_back(point2);
        }
        else if (c1 != 1 && !isWhite)
        {
            point.row = c1 + 1;
            point.col = c2;
            point.isAttack = (false);
            points.push_back(point);
        }
        else if (c1 != 6 && isWhite)
        {
            point.row = c1 - 1;
            point.col = c2;
            point.isAttack = (false);
            points.push_back(point);
        }
        if (isWhite)
        {

            point3A.row = c1 - 1;
            point3A.col = c2 - 1;
            point4A.row = c1 - 1;
            point4A.col = c2 + 1;
            point3A.isAttack = (true);
            point4A.isAttack = (true);
            points.push_back(point3A);
            points.push_back(point4A);
        }
        if (!isWhite)
        {
            Point point4A;
            point5A.row = c1 + 1;
            point5A.col = c2 + 1;
            point5A.isAttack = (true);
            points.push_back(point5A);
            point6A.row = c1 + 1;
            point6A.col = c2 - 1;
            point6A.isAttack = (true);
            points.push_back(point6A);
        }
        else if (c1 == 1 && !isWhite)
        {
            point.row = c1 + 1;
            point.col = c2;
            point.isAttack = (false);
            point2.row = c1 + 2;
            point2.col = c2;
            point2.isAttack = (false);
            points.push_back(point);
            points.push_back(point2);
        }
        else if (c1 != 1 && !isWhite)
        {
            point.row = c1 + 1;
            point.col = c2;
            point.isAttack = (false);
            points.push_back(point);
        }
        else if (c1 != 6 && isWhite)
        {
            point.row = c1 - 1;
            point.col = c2;
            point.isAttack = (false);
            points.push_back(point);
        }
    }
    void Rook::move(int c1, int c2, std::vector<Point> &points)
    {
    }
    void Knight::move(int c1, int c2, std::vector<Point> &points)
    {
    }
    void Bishop::move(int c1, int c2, std::vector<Point> &points)
    {
    }
    void Queen::move(int c1, int c2, std::vector<Point> &points)
    {
    }
    void King::move(int c1, int c2, std::vector<Point> &points)
    {
    }
}