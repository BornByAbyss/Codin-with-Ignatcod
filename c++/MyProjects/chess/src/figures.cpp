#include <iostream>
#include <vector>
#include "point.h"
#include "figures.h"
#include "olcPixelGameEngine.h"

void Figures::set(bool bl, std::string str, float x, float y)
{
    //    pawnW1.set(true, "pB", 0.0f, 480.0);
    olcPos.x = x;
    olcPos.y = y;
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

void Pawn::move(int c1, int c2, std::vector<Point> &points)
{
    Point tempPoint = {c1, c2};
    if (isWhite)
        points = {{-1, -1, true}, {-1, 1, true}, {-1, 0, false}};

    if (!isWhite)
        points = {{1, 1, true}, {1, -1, true}, {1, 0, false}};

    for (int i = 0; i < points.size(); i++)
        points[i] += tempPoint;

    if (isWhite && (c1 == 6))
        points.push_back(Point{-2, 0, false} + tempPoint);

    if (!isWhite && (c1 == 1))
        points.push_back(Point{2, 0, false} + tempPoint);
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
