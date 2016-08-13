#include <iostream>
#include "mytime0.h"

Time::Time()
{
    hour = minutes = 0;
}

Time::Time(int h, int m)
{
    hour = h;
    minutes = m;
}

void Time::AddMin(int m)
{
    minutes = minutes + m;
    hour += minutes / 60;
    minutes %= 60;
}

void Time::AddHr(int h)
{
    hour += h;
}

void Time::Reset(int h, int m)
{
    hour = h;
    minutes = m;
}

Time Time::Sum(const Time & t) const
{
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hour = hour + t.hour + sum.minutes / 60;
    sum.minutes %= 60;
    return sum;
}

/*************************************************
Time & Time::Sum(const Time & t) const
{
    this -> minutes += t.minutes;
    this -> hour = t.hour + this -> minutes / 60;
    this -> minutes %= 60;

    return *this;
}

不可以这样，因为*this里的东西const
**************************************************/
void Time::show() const
{
    std::cout << hour << " hours, " << minutes << " minutes";
}
