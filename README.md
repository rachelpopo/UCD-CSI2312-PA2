// Rachel Popo
# UCD-CSI2312-PA2
Intermediate Programming, Programming Assignment 2

In this program we implement a Point class, which holds 3-dimensional points, and a Cluster class, which is capable of holding a large number of Point objects. 

Point.h & Point.cpp 
Each point object contains a certain number of dimensions (dim) and values of each of the point's dimensions (*values).
With our Point member and friend functions we are able to compare points, add/subtract points, get the distance from one point to the other, etc. 

Cluster.h & Cluster.cpp
Cluster contains two private variables, size and points (points to struct.) The Cluster member and friend functions allow us to easily add and remove points to clusters, compare clusters, etc. 

main.cpp 
Used to test functions.
