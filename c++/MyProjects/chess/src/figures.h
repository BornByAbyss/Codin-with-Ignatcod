#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <vector>
#include "point.h"
#include "olcPixelGameEngine.h"

class Figures
{
protected:
    bool isWhite;
    bool isInit = true;
    std::string type;

public:
    void set(bool, std::string, float, float);
    void setInitial(bool);
    olc::vf2d olcPos;

public:
    bool isInitial() const;
    bool showColor() const;
    std::string showType() const;
    virtual void move(int, int, std::vector<Point> &) = 0;
};

class Pawn : public Figures
{
public:
    virtual void move(int, int, std::vector<Point> &) override;
};
class Bishop : public Figures
{
public:
    virtual void move(int, int, std::vector<Point> &) override;
};

class Knight : public Figures
{
public:
    virtual void move(int, int, std::vector<Point> &) override;
};

class Rook : public Figures
{
public:
    virtual void move(int, int, std::vector<Point> &) override;
};

class Queen : public Figures
{
public:
    virtual void move(int, int, std::vector<Point> &) override;
};

class King : public Figures
{
public:
    virtual void move(int, int, std::vector<Point> &) override;
};

#endif