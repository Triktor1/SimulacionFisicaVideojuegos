#include "Vector3D.h"
float Vector3D::magnitude() const {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector3D Vector3D::normalize() const {
	Vector3D norm;
	norm.x = x / magnitude();
	norm.y = y / magnitude();
	norm.z = z / magnitude();
	return norm;
}

float Vector3D::dot(const Vector3D& v) const {
	return x * v.x + y * v.y + z * v.z;
}

Vector3D Vector3D::cross(const Vector3D& v) const {
	Vector3D crs;
	crs.x = y * v.z - z * v.y;
	crs.y = z * v.x - x * v.z;
	crs.z = x * v.y - y * v.x;
	return crs;
}