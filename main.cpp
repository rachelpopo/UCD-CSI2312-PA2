#include <iostream>
#include "Point.h"
#include "Cluster.h"


int main()
{
    //Access our functions all defined within Clustering namespace
    using namespace Clustering;
    int dimensions = 3;

    // 3 dimensional point
    double* pValues = new double[dimensions]{1, 2, 3};

    //initialize new point
    Point* n = new Point(dimensions, pValues);
    Point* m = new Point(dimensions, pValues);

    // Test Assignment & copy ctr
    Point c = *n;
    Point d = *m;
    //Uses assignent operator - Point e has already
    //been declared (it used the default constructor)
    Point e;
    e = *n;

    //print our points
    std::cout << c << std::endl << e << std::endl;



    return 0;
}
