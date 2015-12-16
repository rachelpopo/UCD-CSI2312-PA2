$ git tag "version 3.0"
$ git tag "version 2.0"

//
// Created by Rachel Popo
#ifndef CLUSTERING_CLUSTER_H
#define CLUSTERING_CLUSTER_H

#include "Point.h"

namespace Clustering {

    typedef Point *PointPtr;
    typedef struct LNode *LNodePtr;

    struct LNode {
        PointPtr p;
        LNodePtr next;
        LNode(PointPtr pt, LNodePtr n) : p(pt), next(n) {}
    };

    class Cluster {
        unsigned int __ID;
        int __size;
        LNodePtr __points;
        bool __greedy;
        Point __centroid;
        bool valid;

        void __del();
        void __cpy(LNodePtr pts);

    public:
        class Move{                                                             //represents motion of pt from one cluster to another
            Cluster* fromCluster;
            Cluster* toCluster;
            PointPtr point;

            Move(const PointPtr &ptr, Cluster *from, Cluster *to):
                    fromCluster(from),
                    toCluster(to),
                    point(ptr)
            {};

            void perform();
        };



        Cluster() :
                __ID(generateID()),
                __size(0),
                __points(nullptr),
                __centroid(),
                valid(false),
                __greedy(false)
        {};

        Cluster(bool rp) :
                __ID(generateID()),
                __size(0),
                __points(nullptr),
                __centroid(),
                valid(false),
                __greedy(true)
        {};
        Cluster(bool rp, bool gdy) :
                __ID(generateID()),
                __size(0),
                __points(nullptr),
                __centroid(),
                valid(false),
                __greedy(gdy)
        {};

        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const PointPtr &);
        const PointPtr &remove(const PointPtr &);

        static unsigned int generateID(){
                static unsigned int i = 0;
                ++i;
                return i;
        }

        static unsigned int getID(Cluster &cluster){
            return cluster.__ID;
        }

        // Overloaded operators

        // IO
        // - Friends
        friend std::ostream &operator<<(std::ostream &, const Cluster &);
        friend std::istream &operator>>(std::istream &, Cluster &);

        // Set-preserving operators (do not duplicate points in the space)
        // - Friends
        friend bool operator==(const Cluster &lhs, const Cluster &rhs);

        // - Members
        Cluster &operator+=(const PointPtr &rhs); // allocate point
        Cluster &operator-=(const Point &rhs); // delete point(s) (greedy)

        // Set-destructive operators (duplicate points in the space)
        // - Members
        Cluster &operator+=(const Cluster &rhs); // union
        Cluster &operator-=(const Cluster &rhs); // (asymmetric) difference



        // - Friends


        friend const Cluster operator+(const Cluster &lhs, const Cluster &rhs);
        friend const Cluster operator-(const Cluster &lhs, const Cluster &rhs);

        friend const Cluster operator+(const Cluster &lhs, const PointPtr &rhs);
        friend const Cluster operator-(const Cluster &lhs, const PointPtr &rhs);



        //Methods for scoring the clustering (used in requirements for KMeans)
        friend double interClusterDistance(const Cluster &c1, const Cluster &c2);
        friend double interClusterEdges(const Cluster &c1, const Cluster &c2);

        double intraClusterDistance() const;
        int getClusterEdges();



        LNodePtr getPoints(){
            return __points;
        }

        int getSize(){
            return __size;
        }

        //Centroid Functions
        void setCentroid(const Point &point){
            __centroid = point;
            valid = true;
        };
        const Point getCentroid(){return __centroid;};
        const Point computeCentroid(const Point &point);
        bool isCentroidValid(){ return valid;};


        //Pick points to fill array
        void pickPoints(int k, PointPtr *pointArray);





    };

}
#endif //CLUSTERING_CLUSTER_H
