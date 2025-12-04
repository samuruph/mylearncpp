#include <iostream>

class Point3d
{
    private:
        int m_x {}, m_y {}, m_z {};
    public:
        void setValues(int v1, int v2, int v3)
        {
            m_x = v1;
            m_y = v2;
            m_z = v3;
        }

        void print() const
        {
            std::cout << "< " << m_x << ", " << m_y << ", " << m_z << ">";
        }

        bool isEqual(const Point3d& p) const
        // This works since access control works on a class level, not on an object level
        // Since p is of type Point3d, we can access its private members here
        {
            return (m_x == p.m_x) && (m_y == p.m_y) && (m_z == p.m_z);
        }
};

int main()
{
	Point3d point1{};
	point1.setValues(1, 2, 3);

	Point3d point2{};
	point2.setValues(1, 2, 3);

	std::cout << "point 1 and point 2 are" << (point1.isEqual(point2) ? "" : " not") << " equal\n";

	Point3d point3{};
	point3.setValues(3, 4, 5);

	std::cout << "point 1 and point 3 are" << (point1.isEqual(point3) ? "" : " not") << " equal\n";

	return 0;
}