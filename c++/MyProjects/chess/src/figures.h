#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <vector>
#include "point.h"

namespace chesslogix
{
    class Figures
    {
    protected:
        bool isWhite;
        std::string type;

    public:
        void set(bool, std::string);

    public:
        bool showColor() const;
        std::string showType() const;
        friend std::ostream &operator<<(std::ostream &, Figures &);
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
}
#endif