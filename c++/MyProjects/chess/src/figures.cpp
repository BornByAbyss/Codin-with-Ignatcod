#include <iostream>
#include <vector>
#include "point.h"
#include "figures.h"
#include "olcPixelGameEngine.h"

void Figures::set(bool bl, std::string str, float x, float y)
{
    olcPos.x = x;
    olcPos.y = y;
    isWhite = bl;
    type = str;
}

bool Figures::isInitial() const
{
    return isInit;
}

void Figures::setInitial(bool bl)
{
    isInit = bl;
}

bool Figures::showColor() const
{
    return isWhite;
}
std::string Figures::showType() const
{
    return type;
}
Figures Figures::operator=(Figures fig)
{
    olcPos.x = fig.olcPos.x;
    olcPos.y = fig.olcPos.y;

    type = fig.type;
    isWhite = fig.isWhite;
    isInit = fig.isInit;
    return *this;
}
void Figures::move(int c1, int c2, std::vector<Point> &points)
{
}

void Pawn::move(int c1, int c2, std::vector<Point> &points)
{
    Point tempPoint = {c1, c2};
    if (isWhite)
        points = {{-1, -1, true}, {-1, 1, true}, {-1, 0, false}};

    if (!isWhite)
        points = {{1, 1, true}, {1, -1, true}, {1, 0, false}};

    for (int i = 0; i < points.size(); i++)
    {
        points[i] += tempPoint;
        if (points[i].col < 0 || points[i].col >= 8 || points[i].row >= 8 || points[i].row < 0)
        {
            points.erase(points.begin() + i);
            --i;
        }
    }

    if (isWhite && (c1 == 6))
        points.push_back(Point{-2, 0, false} + tempPoint);

    if (!isWhite && (c1 == 1))
        points.push_back(Point{2, 0, false} + tempPoint);
}
void Rook::move(int c1, int c2, std::vector<Point> &points)
{
    Point tempPoint;
    std::vector<Point> movements = {{-1, 0, true}, {0, -1, true}, {1, 0, true}, {0, 1, true}};

    for (int i = 0; i < movements.size(); i++)
    {
        tempPoint = {c1, c2, true};
        while (true)
        {
            tempPoint += movements[i];
            if (tempPoint.col < 0 || tempPoint.col >= 8 || tempPoint.row < 0 || tempPoint.row >= 8)
                break;
            points.push_back(tempPoint);
        }
    }
}
void Knight::move(int c1, int c2, std::vector<Point> &points)
{
    Point tempPoint;
    std::vector<Point> movements = {{-2, 1, true}, {-2, -1, true}, {1, -2, true}, {-1, 2, true}, {-1, -2, true}, {2, -1, true}, {2, 1, true}, {1, 2, true}};

    for (int i = 0; i < movements.size(); i++)
    {
        tempPoint = {c1, c2, true};
        tempPoint += movements[i];
        if (tempPoint.col < 0 || tempPoint.col >= 8 || tempPoint.row < 0 || tempPoint.row >= 8)
            continue;
        points.push_back(tempPoint);
    }
}
void Bishop::move(int c1, int c2, std::vector<Point> &points)
{
    Point tempPoint;
    std::vector<Point> movements = {{-1, 1, true}, {1, -1, true}, {1, 1, true}, {-1, -1, true}};

    for (int i = 0; i < movements.size(); i++)
    {
        tempPoint = {c1, c2, true};
        while (true)
        {
            tempPoint += movements[i];
            if (tempPoint.col < 0 || tempPoint.col >= 8 || tempPoint.row < 0 || tempPoint.row >= 8)
                break;
            points.push_back(tempPoint);
        }
    } 
} 
void Queen::move(int c1, int c2, std::vector<Point> &points)
{
    Point tempPoint;
    std::vector<Point> movements = {{-1, 0, true}, {1, 1, true}, {-1, -1, true}, {1, 0, true}, {0, 1, true}, {0, -1, true}, {1, -1, true}, {-1, 1, true}};

    for (int i = 0; i < movements.size(); i++)
    {
        tempPoint = {c1, c2, true};
        while (true)
        {
            tempPoint += movements[i];
            if (tempPoint.col < 0 || tempPoint.col >= 8 || tempPoint.row < 0 || tempPoint.row >= 8)
                break;
            points.push_back(tempPoint);
        }
    }
}
void King::move(int c1, int c2, std::vector<Point> &points)
{
    Point tempPoint = {c1, c2, true};
    points = {{-1, 0, true}, {1, 1, true}, {-1, -1, true}, {1, 0, true}, {0, 1, true}, {0, -1, true}, {1, -1, true}, {-1, 1, true}};

    for (int i = 0; i < points.size(); i++)
    {
        points[i] += tempPoint;
        if (points[i].col < 0 || points[i].col >= 8 || points[i].row >= 8 || points[i].row < 0)
        {
            points.erase(points.begin() + i);
            --i;
        }
    }
}
