// Header file that defines the Point3d class
// Here we only provide the declarations of the member functions (that are defined in Point3d.cpp)

#ifndef POINT3D_H
#define POINT3D_H

class Vector3d; // forward declaration for class Vector3d for function moveByVector()

class Point3d
{
private:
	double m_x{};
	double m_y{};
	double m_z{};

public:
	Point3d(double x, double y, double z);

	void print() const;
    // forward declaration of friend member function
    // here it is not fully defined because Vector3d is not fully defined yet
	void moveByVector(const Vector3d& v);
};

#endif