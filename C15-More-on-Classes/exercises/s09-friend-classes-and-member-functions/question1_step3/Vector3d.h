// Header file that defines the Vector3d class

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Point3d.h" // for declaring Point3d::moveByVector() as a friend

class Vector3d
{
    private:
        double m_x{};
        double m_y{};
        double m_z{};

    public:
        Vector3d(double x, double y, double z);

        void print() const;
        friend void Point3d::moveByVector(const Vector3d& v);
};

#endif