$ git tag -1 "version 3.0"
$ git tag -1 "version 2.0"

//
// Created by Rachel Popo
//

#include "Point.h"
#include "Cluster.h"

namespace Clustering {

/////////////////////////////
// Cluster
// Member Functions
/////////////////////////////


//Copy constructor
    Cluster::Cluster(const Cluster &cluster) { //copy reference toCopy's values into our clusters values
        __size = cluster.__size;
        __points = NULL;
        valid = cluster.valid;
        __ID = cluster.__ID;
        __centroid = cluster.__centroid;

        LNodePtr last = NULL;

        for (LNodePtr p = cluster.__points; p != NULL; p = p->next) {

            LNodePtr node = new LNode(new Point(*p->p), NULL);

            if (__points == NULL) {
                __points = node;
            }
            else {
                last->next = node;
            }

            last = node;
        }

    }


    Cluster &Cluster::operator=(const Cluster &cluster) {
        if (cluster == *this) {
            return *this;
        }

        __centroid=cluster.__centroid;
        valid = cluster.valid;
        __ID = cluster.__ID;
        __size = cluster.__size;
        __points = NULL;

        LNodePtr last = NULL;

        for (LNodePtr p = cluster.__points; p != NULL; p = p->next) {

            LNodePtr node = new LNode(new Point(*p->p), NULL);

            if (__points == NULL) {
                __points = node;
            }
            else {
                last->next = node;
            }

            last = node;
        }

        return *this;

    }


    Cluster::~Cluster() {

        LNodePtr next = NULL;

        for (LNodePtr p = __points; p != NULL; p = next) {
            next = p->next;
            delete p;
        }

        __points = NULL;
        __size = 0;
    }


//// Set functions: They allow calling c1.add(c2.remove(p));

////add point to cluster
    void Cluster::add(const PointPtr &point)  //add point
    {

        LNodePtr p = __points;

        if (__points == NULL) {
            __size++;
            LNodePtr node = new LNode(point, NULL);
            __points = node;
            valid=false;
            return;
        }

        if (*point < *__points->p) {
            __size++;
            LNodePtr node = new LNode(point, NULL);
            node->next = __points;
            __points = node;
            valid=false;
            return;
        }

        LNodePtr prev = NULL;

        while (p != NULL && *p->p <= *point) {

            if (*p->p == *point) {
                return;
            }

            else {
                prev = p;
                p = p->next;
            }

        }

        __size++;
        LNodePtr node = new LNode(point, NULL);
        prev->next = node;
        node->next = p;

        valid=false;
        return;
    }


////remove point from cluster
    const PointPtr &Cluster::remove(const PointPtr &point) // remove point and return it so we can add it to another cluster
    {
        LNodePtr prev = NULL;

        if (*__points->p == *point) {
            LNodePtr p = __points;
            __points = p->next;
            delete p;
            __size--;
            valid = false;
            return point;

        }

        for (LNodePtr p = __points; p != NULL; p = p->next) {

            if (*point == *p->p) {
                prev->next = p->next;
                delete p;
                __size--;
                valid = false;
                return point;
            }

        }
        valid = false;
        return point;

    }


///////// Member Functions

//// add point to cluster
    Cluster &Cluster::operator+=(const PointPtr &rhs) {

        if (__points == NULL) {
            __size++;
            LNodePtr node = new LNode(rhs, NULL);
            __points = node;
            return *this;
        }

        if (*rhs < *__points->p) {
            __size++;
            LNodePtr node = new LNode(rhs, NULL);
            node->next = __points;
            __points = node;
            return *this;
        }

        LNodePtr p = __points;
        LNodePtr prev = NULL;

        while (p != NULL && *p->p <= *rhs) {

            if (*p->p == *rhs) {
                return *this;
            }

            else {
                prev = p;
                p = p->next;
            }

        }

        __size++;
        LNodePtr node = new LNode(rhs, NULL);
        prev->next = node;
        node->next = p;

        valid = false;
        return *this;

    }

//// remove point from cluster
    Cluster &Cluster::operator-=(const Point &rhs) {


        LNodePtr prev = NULL;

        for (LNodePtr p = __points; p != NULL; p = p->next) {

            if (rhs == *p->p) {
                if (prev == NULL) {
                    LNodePtr temp = __points;
                    __points = p->next;
                    delete temp;
                    __size--;
                    return *this;
                }

                prev->next = p->next;
                delete p;
                __size--;
                return *this;
            }

            if (prev == NULL) {
                prev = __points;
            }
            else {
                prev = prev->next;
            }

        }
        valid = false;
        return *this;
    }


//// union: add cluster(rhs) to cluster
    Cluster &Cluster::operator+=(const Cluster &rhs) {

        if (rhs == *this) {
            return *this;
        }

        if (__points == NULL) {
            *this = rhs;
            return *this;
        }


        LNodePtr prev = NULL;
        LNodePtr p1 = __points;

        for (LNodePtr p2 = rhs.__points; p2 != NULL; p2 = p2->next) {

            while (p1 != NULL && *p1->p < *p2->p) {
                prev = p1;
                p1 = p1->next;
            }


            if (p1 != NULL && *p1->p == *p2->p) {
                prev = p1;
                p1 = p1->next;
                continue;
            }

            __size++;
            LNodePtr node = new LNode(p2->p, NULL);

            if (prev == NULL) {
                __points = node;
            }
            else {
                prev->next = node;
            }

            node->next = p1;
            prev = node;
        }

        valid = false;
        return *this;


    }


//// remove cluster (rhs) from cluster

    Cluster &Cluster::operator-=(const Cluster &rhs) {

        if (__points == NULL || rhs.__points == NULL) {
            return *this;
        }

        LNodePtr prev = NULL;
        LNodePtr p1 = __points;

        for (LNodePtr p2 = rhs.__points; p2 != NULL; p2 = p2->next, p1 = __points) {

            while (p1 != NULL && *p1->p != *p2->p) {
                prev = p1;
                p1 = p1->next;
            }

            if (prev == NULL) {
                __points = p1->next;
                __size--;
                continue;
            }

            if (*p1->p == *p2->p) {
                prev->next = p1->next;
                __size--;
                continue;
            }

        }
        valid = false;
        return *this;

    }

///////////////////////////////
//// Non Member Functions
///////////////////////////////

//// IO
    std::ostream &operator<<(std::ostream &out, const Cluster &cluster) {       /*should put on the stream all its points with its id at the end of each point line,
                                                                               delimited by colon (':') from the Point values. Note: operator<< for Point and Cluster
                                                                               have to be compatible for this to work. Use a static constant for the delimiter character.
                                                                               See the file format snippets above.*/

        LNodePtr c = cluster.__points;

        for (int i=0;i< cluster.__size;i++) {
            if (i == 0){
                out << "Cluster:" << "\n";
            }

            out << *c->p;
            c = c->next;
        }

        return out;
    }

    std::istream &operator>>(std::istream &in, Cluster &cluster) {          /*should use getline on the stream, and pass a stringstream for each line to the
                                                                           operator>> of Point, thus reading in all the points into itself. Note 1: operator>>
                                                                           for Point and Cluster have to be compatible for this to work. Use the basic IO code we
                                                                           saw in class to accomplish this. Note 2: This operator also has to discover the dimensionality
                                                                           of the points that are being read in. */

        return in;
    }


//// Set-preserving operators (do not duplicate points in the space)
//// - Friends

    bool operator==(const Cluster &lhs, const Cluster &rhs) {

        bool compare = false;

        LNodePtr c1 = lhs.__points;
        LNodePtr c2 = rhs.__points;

       if (lhs.__size != rhs.__size) {
            return compare;
       }

        while(c1 != nullptr)
           {
               if(*c1->p != *c2->p){
                   return compare;
               }
               c1 = c1->next;
               c2 = c2->next;
           }

           compare = true;
           return compare;
    }

//// Set-destructive operators (duplicate points in the space)
//// - Friends

    const Cluster operator+(const Cluster &lhs, const Cluster &rhs) {

        Cluster *sum = new Cluster(lhs);

        // if (lhs == rhs || rhs == NULL){
        //    return *sum;
        //}


        if (lhs.__points == NULL) {
            *sum = rhs;
            return *sum;
        }

        LNodePtr prev = NULL;
        LNodePtr p1 = sum->__points;

        for (LNodePtr p2 = rhs.__points; p2 != NULL; p2 = p2->next, p1 = sum->__points, prev = NULL) {

            while (p1 != NULL && *p1->p < *p2->p) {
                prev = p1;
                p1 = p1->next;
            }


            if (p1 != NULL && *p1->p == *p2->p) {
                continue;
            }

            sum->__size++;
            LNodePtr node = new LNode(p2->p, NULL);

            if (prev == NULL) {
                sum->__points = node;

            }
            else {
                prev->next = node;
            }

            node->next = p1;

        }


        return *sum;
    }


    const Cluster operator-(const Cluster &lhs, const Cluster &rhs) {

        Cluster *difference = new Cluster(lhs);

        if (rhs.__points == NULL) {
            return *difference;
        }

        LNodePtr prev = NULL;
        LNodePtr p1 = difference->__points;

        for (LNodePtr p2 = rhs.__points; p2 != NULL; p2 = p2->next, p1 = difference->__points, prev = NULL) {

            while (p1 != NULL && *p1->p != *p2->p) {
                prev = p1;
                p1 = p1->next;
            }

            if (prev == NULL) {
                difference->__points = p1->next;
                difference->__size--;
                continue;
            }

            if (*p1->p == *p2->p) {
                prev->next = p1->next;
                difference->__size--;
                continue;
            }

        }

        return *difference;
    }


    const Cluster operator+(const Cluster &lhs, const PointPtr &rhs) {       //add pt to cluster
        Cluster *c = new Cluster(lhs);

        LNodePtr p = c->__points;
        LNodePtr prev = NULL;

        if (c->__points == NULL){
            c->__size++;
            LNodePtr node = new LNode (new Point(*rhs), NULL);
            c->__points = node;
            return *c;
        }

        while (p != NULL && *p->p <= *rhs) {

            if (*p->p == *rhs) {
                return *c;
            }

            else {
                prev = p;
                p = p->next;
            }

        }

        if (prev == NULL){
            c->__size++;
            LNodePtr node = new LNode(rhs, NULL);
            node->next = p;
            c->__points = node;
            return *c;
        }

        c->__size++;
        LNodePtr node = new LNode(rhs, NULL);
        prev->next = node;
        node->next = p;
        c->valid=false;
        return *c;

    }


    const Cluster operator-(const Cluster &lhs, const PointPtr &rhs) {       //remove pt from cluster
        LNodePtr prev = NULL;
        Cluster *c = new Cluster(lhs);

        if (c->__points == NULL) {
            return *c;
        }

        for (LNodePtr p = c->__points; p != NULL; p = p->next) {

            if (*rhs == *p->p) {
                if (prev == NULL) {
                    LNodePtr temp = c->__points;
                    c->__points = p->next;
                    delete temp;
                    c->__size--;
                    return *c;
                }

                prev->next = p->next;
                delete p;
                c->__size--;
                return *c;
            }

            if (prev == NULL) {
                prev = c->__points;
            }
            else {
                prev = prev->next;
            }

        }

        c->valid = false;
        return *c;

    }




///CENTROID FUNCTIONS


    const Point Cluster::computeCentroid(const Point &point){

        if (__points==NULL){
            return 0;
        }

        Point *average = new Point(__points->p->getDim());
        double total = 0;

        for (LNodePtr p = __points; p != NULL; p = p->next){
            *average = *average + *p->p;
            total++;
        }

        *average = *average / total;

        __centroid = *average;
        valid = true;

        return *average;

    }



    //Pick k points
    void Cluster::pickPoints(int k, PointPtr *pointArray) {

       if (__points==NULL || k == 0){
           return;
       }

       if (__size <= k){
            int i = 0;

            for (LNodePtr p = __points; p != NULL; p = p->next ){

                *pointArray[i] = *p->p;
                i++;
            }
           return;
       }

        int spread = __size / k;
        int count = 1;
        int i = 0;

        for (LNodePtr p = __points; p!=NULL; p = p->next){
            if (count != spread){
                count++;
                continue;
            }

            else {
                *pointArray[i] = *p->p;
                i++;
                count = 1;
                continue;
            }
        }


    }

    //Distance between every 2 pts in cluster
    double Cluster::intraClusterDistance() const{

      double sum = 0.0;

       if (__points == NULL){
           return sum;
       }

        LNodePtr p2 = __points;

       for (LNodePtr p1 = __points; p2!=NULL; p1=p1->next){
           p2 = p1->next;
           sum = sum + p1->p->distanceTo(*p2->p);
       }
        return sum;
    }


    //Distance between 2 clusters
    double interClusterDistance(const Cluster &c1, const Cluster &c2){

        double distance = 0.0;

        if (c1.__points == NULL || c2.__points == NULL){
            return distance;
        }


        LNodePtr p2 = c2.__points;

        for (LNodePtr p1 = c1.__points; p1 != NULL && p2 != NULL; p1 = p1->next) {
            distance = distance + p1->p->distanceTo(*p2->p);
            p2 = p2->next;
        }

        return distance;

    }

    //Edges between 2 clusters
    double interClusterEdges(const Cluster &c1, const Cluster &c2){
        double distance = 0.0;

        if (c1.__points == NULL || c2.__points == NULL){
            return distance;
        }

        distance = c1.__size * c2.__size;
        return distance;

    }


    //Get Edges of cluster
    int Cluster::getClusterEdges(){
        int distance;
        distance = (__size - 1) * (__size / 2);
        return distance;
    }


    //Move Function
    void Cluster::Move::perform() {
        if (fromCluster->__points==NULL){
            return;
        }

        fromCluster->remove(point);
        toCluster->add(point);
    }

}
