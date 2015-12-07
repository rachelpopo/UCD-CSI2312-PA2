//
// Created by Rachel Popo on 11/23/15.
//

#include <iostream>
#include <cassert>
#include "Point.h"
#include "Cluster.h"

using namespace Clustering;

void testConstructors(){

    double values1 [] = {1,2,3};
    Point p1 = Point (3, values1);
    double values2 [] = {2,4,5};
    Point p2 = Point (3, values2);
    double values3 [] = {4,5,6};
    Point p3 = Point (3, values3);
    Cluster *c = new Cluster();     // default constructor
    c->add(&p1);
    c->add(&p2);
    c->add(&p3);
    assert ( p1 == *c->getPoints()->p);                 //test making sure they were added in order
    assert ( p2 == *c->getPoints()->next->p);           //test getPoints
    assert ( p3 == *c->getPoints()->next->next->p);
    Cluster *c2 = new Cluster();
    c2 = c;                                             //test assignment operator
    assert ( p1 == *c2->getPoints()->p);
    assert ( p2 == *c2->getPoints()->next->p);
    assert ( p3 == *c2->getPoints()->next->next->p);
    Cluster *c3 = new Cluster(*c);                       //test copy constructor
    assert ( p1 == *c3->getPoints()->p);
    assert ( p2 == *c3->getPoints()->next->p);
    assert ( p3 == *c3->getPoints()->next->next->p);
}


void testClusterPtOps(){                    //test operators with cluster and point
    double values1 [] = {1,2,3};
    Point p1 = Point (3, values1);
    double values2 [] = {2,4,5};
    Point p2 = Point (3, values2);
    double values3 [] = {4,5,6};
    Point p3 = Point (3, values3);
    Cluster *c = new Cluster();
    c->add(&p1);                            //test add
    assert ( 1 == c->getSize());            //test getSize
    assert ( p1 == *c->getPoints()->p);
    c->add(&p2);
    assert ( 2 == c->getSize());
    assert ( p1 == *c->getPoints()->p);     //test getPoints
    assert ( p2 == *c->getPoints()->next->p);
    c->remove(&p1);                         //test remove
    assert ( 1 == c->getSize());
    assert ( p2 == *c->getPoints()->p);
    c->add(&p1);
    *c -= p2;                              //test -=
    assert (1 == c->getSize());
    assert (p1 == *c->getPoints()->p);
    *c += &p2;                              //test +=
    assert (p1 == *c->getPoints()->p);
    assert (p2 == *c->getPoints()->next->p);
    *c = *c - &p1;                          //test -
    assert (1 == c->getSize());
    assert (p2 == *c->getPoints()->p);
    *c = *c + &p1;                          //test +
    assert (2 == c->getSize());
    assert (p1 == *c->getPoints()->p);
    assert (p2 == *c->getPoints()->next->p);
    *c = *c + &p1;                          // assure doesn't add duplicate pts
    assert (2 == c->getSize());
    assert (p1 == *c->getPoints()->p);
    assert (p2 == *c->getPoints()->next->p);
    Cluster *c2 = new Cluster();
//    *c2 = *c2 + &p1;                        //test + with empty cluster
//    assert (1 == c2->getSize());
//    assert (p1 == *c2->getPoints()->p);



}

void testClusterClusterOps(){               //test operators with two clusters
    double values1 [] = {1,2,3};
    Point p1 = Point (3, values1);
    double values2 [] = {2,4,5};
    Point p2 = Point (3, values2);
    double values3 [] = {4,5,6};
    Point p3 = Point (3, values3);
    Cluster *c1 = new Cluster();            // c1
    c1->add(&p1);
    c1->add(&p2);
    c1->add(&p3);
    double values4 [] = {1,3,3};
    Point p4 = Point (3, values4);
    double values5 [] = {2,4,5};
    Point p5 = Point (3, values5);
    double values6 [] = {4,5,7};
    Point p6 = Point (3, values6);
    Cluster *c2 = new Cluster();            // c2
    c2->add(&p4);
    c2->add(&p5);
    c2->add(&p6);
    *c1 += *c2;                             // cluster += cluster
    assert ( 5 == c1->getSize());           //test size to make sure it didn't add duplicate pts
    assert ( p1 == *c1->getPoints()->p);
    assert ( p4 == *c1->getPoints()->next->p);
    assert ( p2 == *c1->getPoints()->next->next->p);
    assert ( p3 == *c1->getPoints()->next->next->next->p);
    assert ( p6 == *c1->getPoints()->next->next->next->next->p);
    *c1 -= *c2;                             //cluster -= cluster
    assert ( 2 == c1->getSize());
    assert ( p1 == *c1->getPoints()->p);
    assert ( p3 == *c1->getPoints()->next->p);
   Cluster *c3 = new Cluster();
    *c1 = *c1 + *c2;                        // cluster + cluster
    assert ( 5 == c1->getSize());
    assert ( p1 == *c1->getPoints()->p);
    assert ( p4 == *c1->getPoints()->next->p);
    assert ( p2 == *c1->getPoints()->next->next->p);
    assert ( p3 == *c1->getPoints()->next->next->next->p);
    assert ( p6 == *c1->getPoints()->next->next->next->next->p);
    *c1 = *c1 - *c2;                       // cluster - cluster
    assert ( 2 == c1->getSize());
    assert ( p1 == *c1->getPoints()->p);
    assert ( p3 == *c1->getPoints()->next->p);

}


void testCompareClusters(){
    double values1 [] = {1,2,3};
    Point p1 = Point (3, values1);
    double values2 [] = {2,4,5};
    Point p2 = Point (3, values2);
    double values3 [] = {4,5,6};
    Point p3 = Point (3, values3);
    Cluster *c1 = new Cluster();     // c1
    c1->add(&p1);
    c1->add(&p2);
    c1->add(&p3);
    Cluster *c2 = new Cluster(*c1);     // c2
//    assert ( true == (*c1==*c2));     // ==

}

void testClusterCoutCin(){
    double values1 [] = {1,2,3};
    Point p1 = Point (3, values1);
    double values2 [] = {2,4,5};
    Point p2 = Point (3, values2);
    double values3 [] = {4,5,6};
    Point p3 = Point (3, values3);
    Cluster *c1 = new Cluster();     // c1
    c1->add(&p1);
    c1->add(&p2);
    c1->add(&p3);
    std::cout << *c1;
}



int testCluster(){

    testConstructors();
    testClusterClusterOps();
    testClusterPtOps();
    testCompareClusters();
    testClusterCoutCin();
    std::cout << "All tests passed!\n";

    return 0;
}
