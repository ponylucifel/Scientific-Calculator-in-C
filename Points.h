#ifndef POINTS_H
#define POINTS_H
#include <iostream>
using namespace std;

class Points{
public:
    Points();
    Points(double x, double y);
    double getX();
    double getY();
    void setX(double x);
    void setY(double y);
    friend ostream& operator <<(ostream& outs, const Points& t);
private:
    double _x;
    double _y;
};
Points::Points():_x(0), _y(0)
{
    //left blank
}

Points::Points(double x, double y = 0):_x(x), _y(y)
{
    //left blank
}

double Points::getX()
{
    return _x;
}

double Points::getY()
{
    return _y;
}

void Points::setX(double x)
{
    _x = x;
}

void Points::setY(double y)
{
    _y = y;
}

ostream& operator <<(ostream &outs, const Points &t)
{
    outs << "("<< t._x<<","<< t._y<<")";
    return outs;
}
#endif // POINTS_H



