/*
File: ex1.cc
Author: Adam Rudzinski

A simple example documenting the use of PhysUnits.

Use it as you wish, at your own risk.
*/


#include <iostream>
#include "../PhysUnits/Area.hpp"
#include "../PhysUnits/Length.hpp"

using namespace std;
#ifdef PHYSUNITS_NAMESPACE
using PHYSUNITS_NAMESPACE;
#endif

int main()
{
    Length l1(Length::Unit::cm(2.54));
    Length l2 = Length::Unit::mils(100);

    cout << "l1 = " << l1.mm() << "mm ; l2 = " << l2.mm() << "mm\n";

    Area a = l1 * l2;
    cout << "a = " << a.cm2() << " cm2\n";
    Length l3 = sqrt(a);
    cout << "sqrt(a) = " << l3.cm() << " cm\n";

    double r = l1 / l2;
    cout << "l1/l2 = " << r << '\n';

    cout << "9 * l1 = " << (9 * l1).mils() << " mils\n";

    return 0;
}
