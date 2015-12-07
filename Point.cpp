//
// Created by Rachel Popo
//

#include "Point.h"
#include "Cluster.h"
#include <cmath>
#include <iostream>

namespace Clustering {
    //Point member functions
    Point::Point() {
        dim = 0;
        values = NULL;

    }

    Point::Point(int newDim) {
        dim = newDim;
        values = new double[dim];
        for (int i = 0; i < dim; ++i) {
            values[i] = 0;
        }

    }

    Point::Point(int newDim, double *newValues) {
        dim = newDim;
        values = new double[dim];

        for (int i = 0; i < dim; ++i) {
            values[i] = newValues[i];
        }

    }

    // Big three: cpy ctor, overloaded operator=, dtor
    Point::Point(const Point &point) {
        dim = point.dim;
        values = new double[dim];

        for (int i = 0; i < dim; ++i) {
            values[i] = point.values[i];
        }
    }

    Point &Point::operator=(const Point &point) {
        if (this == &point) {
            return *this;
        }

        if (values != NULL) {
            delete values;
        }

        dim = point.dim;
        values = new double[dim];

        for (int i = 0; i < dim; ++i) {
            values[i] = point.values[i];
        }

        return *this;
    }

    Point::~Point() {
        delete values;
    }

    Point &Point::operator*=(double n) {
        for (int i = 0; i < dim; ++i) {
            values[i] *= n;
        }

        return *this;
    }

    Point &Point::operator/=(double n) {
        if (n == 0) {
            std::cout << "Can not divide by zero." << std::endl;
            return *this;
        }

        for (int i = 0; i < dim; ++i) {
            values[i] /= n;
        }

        return *this;
    }

    const Point Point::operator*(double n) const {
        Point a(dim);
        for (int i = 0; i < dim; ++i) {
            a.values[i] = values[i] * n;
        }

        return a;

    }

    const Point Point::operator/(double n) const {
        if (n == 0) {
            std::cout << "Can not divide by zero." << std::endl;
            return 0;
        }

        Point a(dim);
        for (int i = 0; i < dim; ++i) {
            a.values[i] = values[i] / n;
        }

        return a;
    }


    //Sort function
    void lSort(int dim, double *values){
        double temp;

        for (int i = 0; i < dim - 1; i++){

            if (values[i] > values [i + 1]){
                temp = values [i];
                values [i] = values [i + 1];
                values [i + 1] = temp;
            }
        }
        return;
    }


    void Point::setValue(int index, double n) {
        if (index >= 0 && index < dim) {
            values[index] = n;
        }
    }

    double Point::getValue(int index) const {
        if (index >= 0 && index < dim) {
            return values[index];
        }

        else {
            return 0;
        }
    }

    void Point::clear () {
        if (values != NULL) {
            delete values;
        }
        values = NULL;
        dim = 0;
    }


    void Point::append(double v){
        if (values == NULL){
            dim = 1;
            values = new double [dim];
            values[0] = v;
            return;
        }

        dim++;
        double *values2 = new double [dim];

        for (int i = 0; i < dim - 1; i++){
            values2[i] = values[i];
        }

        values2[dim-1] = v;
        delete values;
        values = values2;
        return;

    }


    double Point::distanceTo(const Point &point) const {
        if (point.dim == dim) {
            double sum = 0;
            for (int i = 0; i < dim; ++i) {
                double temp = point.values[i] - values[i];
                sum += temp * temp;
            }

            return sqrt(sum);
        }

        else {
            return 0;
        }
    }

    /////////////////////////////
    // Non Member functions
    //Notice they don't need to have te class specififer Point:: infront
    //because they are not member functions of class Point

    Point &operator+=(Point &a, const Point &b) {
        for (int i = 0; i < a.dim; ++i)
            a.values[i] += b.values[i];
        return a;
    }

    Point &operator-=(Point &a, const Point &b) {
        for (int i = 0; i < a.dim; ++i)
            a.values[i] -= b.values[i];
        return a;
    }

    const Point operator+(const Point &a, const Point &b) {
        const Point temp(a.dim);
        for (int i = 0; i < a.dim; ++i)
            temp.values[i] = a.values[i] + b.values[i];

        return temp;
    }

    const Point operator-(const Point &a, const Point &b) {
        const Point temp(a.dim);
        for (int i = 0; i < a.dim; ++i)
            temp.values[i] = a.values[i] - b.values[i];

        return temp;
    }

    bool operator==(const Point &a, const Point &b) {
        bool compare = true;

        for (int i = 0; i < a.dim; ++i) {
            if (a.values[i] != b.values[i])
                compare = false;
        }

        return compare;
    }

    bool operator!=(const Point &a, const Point &b) {
        bool compare = false;

        for (int i = 0; i < a.dim; ++i) {
            if (a.values[i] != b.values[i])
                compare = true;
        }

        return compare;
    }

    bool operator<(const Point &a, const Point &b) {
        bool compare = false;

        for (int i = 0; i < a.dim && i < b.dim; ++i) {
            if (a.values[i] < b.values[i])
                compare = true;
        }

        return compare;
    }

    bool operator>(const Point &a, const Point &b) {
        bool compare = false;

        for (int i = 0; i < a.dim; ++i) {
            if (a.values[i] > b.values[i])
                compare = true;
        }

        return compare;
    }

    bool operator<=(const Point &a, const Point &b) {
        bool compare = false;

        for (int i = 0; i < a.dim; ++i) {
            if (a.values[i] <= b.values[i])
                compare = true;
        }

        return compare;
    }

    bool operator>=(const Point &a, const Point &b) {
        bool compare = false;

        for (int i = 0; i < a.dim; ++i) {
            if (a.values[i] >= b.values[i])
                compare = true;
        }

        return compare;
    }


    std::ostream &operator<<(std::ostream &out, const Point &point) {

        out << "(";

        for (int i = 0; i < point.dim; ++i) {
            if (i < point.dim - 1) {
                out << point.values[i] << ",";
            }
            else {
                out << point.values[i];
            }
        }

        out << ")";

        out << std::endl; //print new line

        return out;

    }


    std::istream &operator>>(std::istream &in, Point &point) {

        point.clear();

       char openParen;
       in >> openParen;

       double value;
       char c = in.peek();

       while (c != ')'){
           in >> value;
           point.append(value);
           in >> c;
       }

        return in;
    }

}

