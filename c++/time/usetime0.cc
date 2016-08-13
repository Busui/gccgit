#include <iostream>
#include "mytime0.h"

int main(void)
{
    using std::cout;
    using std::endl;
    
    Time planing;
    Time coding(2, 40);
    Time fixing(5, 55);
    Time total;

    cout << "planing time: ";
    planing.show();
    cout << endl;

    cout << "coding time: " ;
    coding.show();
    cout << endl;

    cout << "Fixing time: ";
    fixing.show();
    cout << endl;

    total = coding.Sum(fixing);
    cout << "coding.Sum(fixing): ";
    total.show();
    cout << endl;

    return 0;
}
