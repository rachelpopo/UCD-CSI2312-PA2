#include <iostream>
#include <cassert>
#include "Point.h"
#include "Cluster.h"
#include <cmath>


using namespace Clustering;

void testPointConstructors(){
    Point p = Point();                  //default
    assert (0 == p.getDim());
    assert (0.0 == p.getValue(0));
    p = Point(5);                      //constructor with dim only
    assert (5 == p.getDim());
    assert (0.0 == p.getValue(0));
    double values[] = {1,2,3,4,5};
    p = Point(5, values);               //constructor with dim and values
    assert (5 == p.getDim());
    assert (4 == p.getValue(3));
    p.setValue(2,2.5);                  //test setValue
    assert (2.5 == p.getValue(2));

}

//////Test Member Operators

void testPointOperatorsDouble() {              //Test operators with a point and a double
    double values[] = {1, 2, 3};
    Point p1 = Point(3, values);
    p1 *= 2.0;                          // *=
    assert (2 == p1.getValue(0));
    assert (4 == p1.getValue(1));
    assert (6 == p1.getValue(2));
    assert (3 == p1.getDim());          //getDim test
    p1 = Point(3, values);
    p1 /= 2.0;                          // /=
    assert (0.5 == p1.getValue(0));
    assert (1.0 == p1.getValue(1));
    assert (1.5 == p1.getValue(2));
    assert (3 == p1.getDim());
    p1 = Point(3, values);
    p1 = p1 * 2.0;                      // *
    assert (2 == p1.getValue(0));
    assert (4 == p1.getValue(1));
    assert (6 == p1.getValue(2));
    p1 = Point(3, values);
    p1 = p1 / 2.0;                      // /
    assert (0.5 == p1.getValue(0));
    assert (1.0 == p1.getValue(1));
    assert (1.5 == p1.getValue(2));

}

void testPointOperatorsPoint() {             //Test operators with two points
    double values[] = {1, 2, 3};
    Point p1 = Point(3, values);
    Point p2 = Point(p1);               // copy constructor
    Point p3 = p1 + p2;                 // +
    assert (2 == p3.getValue(0));
    assert (4 == p3.getValue(1));
    assert (6 == p3.getValue(2));
    p1 += p2;                           // +=
    assert (2 == p1.getValue(0));
    assert (4 == p1.getValue(1));
    assert (6 == p1.getValue(2));
    p1 = Point(3, values);
    p1 *= 2.0;
    p3 = p1 - p2;                       // -
    assert (1 == p3.getValue(0));
    assert (2 == p3.getValue(1));
    assert (3 == p3.getValue(2));
    p1 -= p2;                           // -=
    assert (1 == p1.getValue(0));
    assert (2 == p1.getValue(1));
    assert (3 == p1.getValue(2));
}

void testComparePoints(){               //Test comparison operators w/ 2 points
    double values [] = {1,2,3};
    Point p1 = Point (3, values);
    double values2 [] = {5,7,9};
    Point p2 = Point (3, values2);
    assert (std::abs(p1.distanceTo(p2) - 8.77496) < 0.00001);  //distance between 2 pts
    assert ( false == (p1 == p2));        // ==
    assert ( true == (p1 != p2));         // !=
    p2 = p1;
    assert ( true == (p1 == p2));         // ==
    assert ( false == (p1 != p2));        // !=
    p2 = Point (3, values2);
    assert ( true == (p1 < p2));          // <
    assert ( false == (p2 < p1));
    assert ( true == (p2 > p1));          // >
    assert ( false == (p1 > p2));
    assert ( true == (p1 <= p2));         // <=
    assert ( true == (p2 >= p1));         // >=
    p2 = Point(p1);
    assert ( true == (p1 <= p2));
    assert ( true == (p2 >= p1));
}

void testCoutCin(){
    double values [] = {1,2,3};
    Point p1 = Point (3, values);
    std::cout << p1;
    std::cout << "Please enter your point";
    std::cin >> p1;
    std::cout << p1;
}
 

int testCluster();

int main()
{

    testCoutCin();
    testPointConstructors();
    testPointOperatorsDouble();
    testPointOperatorsPoint();
    testComparePoints();
    testCluster();
    std::cout << "All tests passed!\n";

    return 0;
}
