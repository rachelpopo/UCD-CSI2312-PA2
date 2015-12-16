//
// Created by Rachel Popo on 12/10/15.
//

#include "kmeans.h"

namespace Clustering {

    Cluster readPoints(string *filename) {
        Cluster *c = new Cluster();

        std::ifstream file("filename");
        file.open("cluster.txt");
        file >> *c;
        file.close;

        return *c;
    }


    void Cluster::KMeans::computeClusteringScore() {

        if (__pointSpace->getSize() == 1){
            __score = 0;
            return;
        }

        double bCV;
        double dIn, dOut, pIn, pOut;


        for (int i = 0; i < __size - 1; i++) {
            dIn = dIn + __head[i].intraClusterDistance();
            pIn = pIn + __head[i].getClusterEdges();
            for (int j = i + 1; j < __size; j++) {
                dOut = dOut + interClusterDistance(__head[i], __head[j]);
                pOut = pOut + __head[i].getSize() * __head[j].getSize();
            }
        }
        for (int i = 0; i < __pointSpace->getSize(); i++) {
            dIn = dIn + __pointSpace->intraClusterDistance();
            pIn = pIn + __pointSpace->getClusterEdges();
            for (int j = 0; j < __size - 1; j++) {
                dOut = dOut + interClusterDistance(*__pointSpace, __head[j]);
                pOut = pOut + __head[j].getSize() * (__pointSpace->getSize());
            }
        }

        bCV = (dIn / pIn) / (dOut / pOut);

        __score = __bCV;

    }

}



