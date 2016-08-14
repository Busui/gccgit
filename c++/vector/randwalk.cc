#include <iostream>
#include <cstdlib>
#include <ctime>
#include "vector.h"

int main()
{
    using namespace std;
    using VECTOR::Vector;

    srand(time(0));  // seed random-number generator
    double direction;
    Vector step;
    Vector result(0.0, 0.0);
    unsigned long steps = 0;
    double target;
    double dstep;

    cout << "Enter target distance (q to quit): ";
    while (cin >> target){
        cout << "Enter step length: ";
        if (!(cin >> dstep))
            break;

        while (result.magval() < target){
            direction = rand() % 360; // 360 degree
            step.reset(dstep, direction, Vector::POL);
            result = result + step; //invalid in : result += step.
            steps++;
        }

        cout << "After " << steps << " steps, the object " 
            "has the following location: \n";
        cout << result << endl;
        result.polar_mode();
        cout << " or\n" << result << endl;
        cout << "Averagr outward distance per step = "
            << result.magval() / steps << endl; //note: steps not step!!!!
        steps = 0;
        result.reset(0.0, 0.0);
        cout << "Enter target distance (q to quit): ";
    }
    cout << "Bye!\n";
    cin.clear();
    while (cin.get() != '\n')
        continue;

    return 0;
}
