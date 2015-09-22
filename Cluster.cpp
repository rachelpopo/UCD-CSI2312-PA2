//
// Created by Rachel Popo on 9/21/15.
//

#include "Cluster.h"

namespace Clustering
{
    Cluster::Cluster() //Default constructor
    {
        size = 0;
        points = nullptr;
    }


    Cluster::Cluster(const Cluster &clust) //Copy constructor
    {
        size = clust.size;
        points = clust.points;

    }

    Cluster& Cluster:: operator=(const Cluster &clust)
    {
        if (this == &clust)
        {
            return *this;
        }
        else
        {
            size = clust.size;
            points = clust.points;
        }
    }
}
