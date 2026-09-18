#pragma once
#include <PxPhysicsAPI.h>

class Vector3D
{
public:
	float x, y, z;

	Vector3D() :x(0), y(0), z(0) {};
	Vector3D(float x, float y, float z) :x(x), y(y), z(z) {};
	Vector3D(physx::PxVec3 v) : x(v.x), y(v.y), z(v.z) {};

	float magnitude() const;
	Vector3D normalize() const;
	float dot(const Vector3D& v) const;
	Vector3D cross(const Vector3D& v) const;

	Vector3D operator=(const Vector3D& other) {
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	bool operator==(const Vector3D& other) {
		return x == other.x && y == other.y && z == other.z;
	}
	Vector3D operator+(const Vector3D& other) {
		return Vector3D(x + other.x, y + other.y, z + other.z);
	}
	Vector3D operator+=(const Vector3D& other) {
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	Vector3D operator-(const Vector3D& other) {
		return Vector3D(x - other.x, y - other.y, z - other.z);
	}
	Vector3D operator-=(const Vector3D& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vector3D operator*(float escalar) {
		return Vector3D(x * escalar, y * escalar, z * escalar);
	}
	Vector3D operator*=(float escalar) {
		x *= escalar;
		y *= escalar;
		z *= escalar;
		return *this;
	}
	Vector3D operator/(float escalar) {
		return Vector3D(x / escalar, y / escalar, z / escalar);
	}
	Vector3D operator/=(float escalar) {
		x /= escalar;
		y /= escalar;
		z /= escalar;
		return *this;
	}
	operator physx::PxVec3() const {
		return physx::PxVec3(x, y, z);
	}
};