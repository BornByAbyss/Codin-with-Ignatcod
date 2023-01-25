#include <iostream>
#include <vector>

class Point
{
private:
    int m_x, m_y, m_z;

public:
    Point(int x, int y, int z) : m_x(x), m_y(y), m_z(z)
    {
    }
    friend std::ostream &operator<<(std::ostream &out, const Point &p)
    {
        out << "Point(" << p.m_x << ", " << p.m_y << ", " << p.m_z << ")";
        return out;
    }
};

class Shape
{
public:
    Shape(/* args */);
    virtual ~Shape() {}

public:
    friend std::ostream &operator<<(std::ostream &out, Shape &sh)
    {
        return sh.print(out);
    }

    virtual std::ostream &print(std::ostream &out) const = 0;
};

Shape::Shape(/* args */)
{
}

class Triangle : public Shape
{
private:
    Point m_x, m_y, m_z;

public:
    Triangle(Point, Point, Point);
    ~Triangle();

public:
    virtual std::ostream &print(std::ostream &out) const override
    {
        out << "Triangle(" << m_x << ", " << m_y << ", " << m_z << ')';
        return out;
    }
};

Triangle::Triangle(Point x, Point y, Point z) : m_x(x), m_y(y), m_z(z)
{
}

Triangle::~Triangle()
{
}

class Circle : public Shape
{
private:
    int radius;
    Point center;

public:
    Circle(Point, int);
    ~Circle();

    virtual std::ostream &print(std::ostream &out) const
    {
        out << "Circle(" << center << ", "
            << "radius " << radius << ")";
        return out;
    }

public:
    int getRadius() { return radius; }
};

Circle::Circle(Point c, int r) : center(c), radius(r)
{
}

Circle::~Circle()
{
}

int getLargestRadius(std::vector<Shape *> v)
{
    int LargestRadius{0};

    for (auto const &element : v)
    {
        if (Circle *c = dynamic_cast<Circle *>(element))
        {
            if (c->getRadius() > LargestRadius)
                LargestRadius = c->getRadius();
        }
    }

    return LargestRadius;
}

int main(int argc, char const *argv[])
{
    std::vector<Shape *> v;
    v.push_back(new Circle(Point(1, 2, 3), 7));
    v.push_back(new Triangle(Point(1, 2, 3), Point(4, 5, 6), Point(7, 8, 9)));
    v.push_back(new Circle(Point(4, 5, 6), 3));

    std::cout << "The largest radius is: " << getLargestRadius(v) << '\n';
}
