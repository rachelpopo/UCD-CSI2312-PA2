
//
// Created by Rachel Popo on 9/21/15.
//

#include "Point.h"
#include "Cluster.h"
#include <cmath>
#include <iostream>

namespace Clustering
{
    //Point member functions
    Point::Point()
    {
    }

    Point::Point(int newDim)
    {
        dim = newDim;
    }

    Point::Point(int newDim, double *newValues)
    {
        dim = newDim;
        values = new double[dim];
        for (int i = 0; i < dim; ++i)
        {
            values[i] = newValues[i];
        }
    }

    // Big three: cpy ctor, overloaded operator=, dtor
    Point::Point(const Point &toCopy)
    {
        dim = toCopy.dim;
        values = new double[dim];

        for (int i = 0; i < dim; ++i)
            values[i] = toCopy.values[i];
    }

    Point& Point::operator=(const Point &toAssign)
    {
        if (toAssign == *this)
              return *this;

        dim = toAssign.dim;
        values = new double[dim];

        for (int i = 0; i < dim; ++i)
            values[i] = toAssign.values[i];

        return *this;
    }

    Point::~Point()
    {
        delete [] values;
    }

    Point& Point::operator *= (double n)
    {
        for (int i = 0; i < dim; ++i)
            values[i] *= n;

        return *this;
    }

    Point& Point::operator /= (double n)
    {
        for (int i = 0; i < dim; ++i)
            values[i] /= n;

        return *this;
    }

    const Point Point::operator*(double n) const
    {
        Point a(dim);
        for (int i = 0; i < dim; ++i)
            a.values[i] = values[i] * n;

        return a;

    }

    const Point Point::operator/(double n) const
    {
        Point a(dim);
        for (int i = 0; i < dim; ++i)
            a.values[i] = values[i] / n;

        return a;
    }


    void Point::setValue(int index, double aDouble)
    {
        if (index >= 0 && index < dim)
            values [index] = aDouble;
    }

    double Point::getValue(int index) const
    {
        if (index >= 0 && index < dim)
            return values[index];
        else
            return 0;
    }

    double Point::distanceTo(const Point &aPoint) const
    {
        if (aPoint.dim == dim)
        {
            double sum = 0;
            for (int i = 0; i < dim; ++i)
                sum += ((aPoint.values[i] - values[i]) * (aPoint.values[i] - values[i]));

            return sqrt(sum);
        }
        else
            return 0;
    }

    /////////////////////////////
    // Non Member functions
    //Notice they don't need to have te class specififer Point:: infront
    //because they are not member functions of class Point

    Point& operator+=(Point &a, const Point &b)
    {
        for (int i = 0; i < a.dim; ++i)
            a.values[i] += b.values[i];
        return a;
    }

    Point& operator-=(Point &a, const Point &b)
    {
        for (int i = 0; i < a.dim; ++i)
            a.values[i] -= b.values[i];
        return a;
    }

    const Point operator+(const Point &a, const Point &b)
    {
        const Point temp(a.dim);
        for (int i = 0; i < a.dim; ++i)
            temp.values[i] = a.values[i] + b.values[i];

        return temp;
    }

    const Point operator-(const Point &a, const Point &b)
    {
        const Point temp(a.dim);
        for (int i = 0; i < a.dim; ++i)
            temp.values[i] = a.values[i] - b.values[i];

        return temp;
    }

    bool operator==(const Point &a, const Point &b)
    {
        bool compare = true;

        for (int i = 0; i < a.dim; ++i)
        {
            if (a.values[i] != b.values[i])
                compare = false;
        }

        return compare;
    }

    bool operator!=(const Point &a, const Point &b)
    {
        bool compare = false;

        for (int i = 0; i < a.dim; ++i)
        {
            if (a.values[i] != b.values[i])
                compare = true;
        }

        return compare;
    }

    bool operator<(const Point &a, const Point &b)
    {
        bool compare = false;

        for (int i = 0; i < a.dim; ++i)
        {
            if (a.values[i] < b.values[i])
                compare = true;
        }

        return compare;
    }

    bool operator>(const Point &a, const Point &b)
    {
        bool compare = false;

        for (int i = 0; i < a.dim; ++i)
        {
            if (a.values[i] > b.values[i])
                compare = true;
        }

        return compare;
    }

    bool operator<=(const Point &a, const Point &b)
    {
        bool compare = false;

        for (int i = 0; i < a.dim; ++i)
        {
            if (a.values[i] <= b.values[i])
                compare = true;
        }

        return compare;
    }

    bool operator>=(const Point &a, const Point &b)
    {
        bool compare = false;

        for (int i = 0; i < a.dim; ++i)
        {
            if (a.values[i] >= b.values[i])
                compare = true;
        }

        return compare;
    }

 std::ostream &operator<<(std::ostream &out, const Point &p)
   {
   //     for (int i = 0; i < p.dim - 1; ++i)
   //         out << p.values[i] << ", ";
   //     out << p.values[p.dim - 1]; //prints our the last value without a comma at the end
   //     out << std::endl; //print new line
   //     return out;
    }

    std::istream &operator>>(std::istream &in, Point &p)
    {

      //  for (int i = 0; i < p.dim - 1; ++i)
        //    in >> p.values[i] >> ", ";
        //in >> p.values[p.dim - 1]; //prints our the last value without a comma at the end
        //in >> std::endl; //print new line

        //return in;
    }

}
