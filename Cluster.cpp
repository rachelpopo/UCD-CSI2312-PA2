//
// Created by Rachel Popo on 9/21/15.
//

#include "Point.h"
#include "Cluster.h"

namespace Clustering {

/////////////////////////////
// Cluster
// Member Functions
/////////////////////////////

//Copy constructor
Cluster::Cluster(const Cluster &toCopy) {
        //copy reference toCopy's values into our clusters values
        size = toCopy.size;
        points = toCopy.points;
    }


Cluster& Cluster::operator=(const Cluster &toAssign)
{
    if (toAssign == *this)
        return *this;

        size = toAssign.size;
        points = toAssign.points;

    for (int i = 0; i < size; ++i)
        points[i] = toAssign.points[i];

    return *this;

}


Cluster::~Cluster()
{
    if (points != nullptr)
    {
        LNodePtr remove = points;
        points = nullptr;
        LNodePtr next = remove->next;

//        if (remove != nullptr)
            delete remove->p;
        next = remove;
        delete remove;


//        if (next != nullptr)
            next = next->next;
    }
}


//// Set functions: They allow calling c1.add(c2.remove(p));
void Cluster::add(const PointPtr &)
{

}

const PointPtr& Cluster::remove(const PointPtr &)
{
}
    

//// add point
Cluster& Cluster::operator+=(const Point &rhs)
{
}

//// remove point
Cluster& Cluster::operator-=(const Point &rhs)
{
}

///////////////////////////////
//// Non Member Functions
///////////////////////////////

//// IO
std::ostream& operator<<(std::ostream &, const Cluster &)
{
}

std::istream &operator>>(std::istream &, Cluster &)
{
}


//// Set-preserving operators (do not duplicate points in the space)
//// - Friends

bool operator==(const Cluster &lhs, const Cluster &rhs)
{
}

//// Set-destructive operators (duplicate points in the space)
//// - Friends

const Cluster operator+(const Cluster &lhs, const Cluster &rhs)
{
}

const Cluster operator-(const Cluster &lhs, const Cluster &rhs)
{
}


