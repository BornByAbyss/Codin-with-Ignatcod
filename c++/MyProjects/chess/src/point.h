#ifndef POINT_H
#define POINT_H

struct Point
{
    int row;
    int col;
    bool isAttack;

    Point operator+(Point &pot)
    {
        Point tempPoint = {(row + pot.row), (col + pot.col), isAttack};
        return tempPoint;
    }
    Point operator+=(Point &rod)
    {
        Point tempPoint = {(row += rod.row), (col += rod.col), isAttack};
        return tempPoint;
    }

    bool operator==(Point &rod)
    {
        if ((row == rod.row) && (col == rod.col))
            return 1;
        else
            return 0;
    }
};

#endif