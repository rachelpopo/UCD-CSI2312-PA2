//
// Created by Rachel Popo on 12/10/15.
//

#ifndef CSCI2312_PA2_KMEANS_H
#define CSCI2312_PA2_KMEANS_H

#include "Cluster.h"

namespace Clustering {

    class KMeans{

    public:

        static const double SCORE_DIFF_THRESHOLD;
        Cluster *__pointSpace;
        Cluster *__head;
        std::string __filename;
        unsigned int __dims; // dimensions of points in each cluster
        unsigned int __k; //# of clusters
        double __score;
        double __scoreDiff;

        KMeans(unsigned int dim, unsigned int k, std::string filename) :
                __dims(dim),
                __k(k),
                __pointSpace(readPoints(filename)),
                __head(__pointSpace->__points)
        {};


        Cluster KMeans::readPoints(string *filename);

        void Cluster::KMeans::computeClusteringScore();


        double getScore(){
            return __score;
        }

    };
}


#endif //CSCI2312_PA2_KMEANS_H
