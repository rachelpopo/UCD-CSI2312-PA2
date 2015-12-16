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
        int __size;
        LNodePtr __points;
        bool __release_points;
        bool __greedy;

        void __del();
        void __cpy(LNodePtr pts);

    public:
        Cluster() :
                __size(0),
                __points(nullptr),
                __release_points(false),
                __greedy(false)
        {};
        Cluster(bool rp) :
                __size(0),
                __points(nullptr),
                __release_points(rp),
                __greedy(true)
        {};
        Cluster(bool rp, bool gdy) :
                __size(0),
                __points(nullptr),
                __release_points(rp),
                __greedy(gdy)
        {};

        // The big three: cpy ctor, overloaded operator=, dtor
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster();

        // Set functions: They allow calling c1.add(c2.remove(p));
        void add(const PointPtr &);
        const PointPtr &remove(const PointPtr &);

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

        LNodePtr getPoints(){
            return __points;
        }

        int getSize(){
            return __size;
        }
    };

}
#endif //CLUSTERING_CLUSTER_H
