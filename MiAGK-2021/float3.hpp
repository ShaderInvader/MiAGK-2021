#pragma once

#include <ostream>
#include <string>

class float4;

class float3
{
public:
	float x, y, z;

	/// <summary>
	/// Create zero vector
	/// </summary>
	float3();

	/// <summary>
	/// Create vector assigning same value to all components
	/// </summary>
	/// <param name="value">initial value of all components</param>
	float3(float value);

	/// <summary>
	/// Create vector assigning different value to each component
	/// </summary>
	/// <param name="x">initial value of x component</param>
	/// <param name="y">initial value of y component</param>
	/// <param name="z">initial value of z component</param>
	float3(float x, float y, float z);

	/// <summary>
	/// Create copy of given vector
	/// </summary>
	/// <param name="vector">original vector</param>
	float3(const float3& vector);

	float3(float4 vector);

	static float3 Zero();
	static float3 One();
	static float3 Up();
	static float3 Right();
	static float3 Forward();

	/// <summary>
	/// Compute vector magnitude,
	/// slower than squareMagnitude()
	/// </summary>
	/// <returns>vector magnitude</returns>
	float magnitude() const;

	/// <summary>
	/// Compute square of vector magnitude
	/// </summary>
	/// <returns>vector magnitude^2</returns>
	float squareMagnitude() const;

	/// <summary>
	/// Normalize vector
	/// </summary>
	void normalize();

	/// <summary>
	/// Create normalized copy of vector
	/// </summary>
	float3 normalized() const;

	/// <summary>
	/// Check if all components are equal zero
	/// </summary>
	bool isZero();

	/// <summary>
	/// Create std::string from given vector in format "[ {x}, {y}, {z} ]"
	/// </summary>
	std::string to_string() const;

	/// <summary>
	/// Compute scalar product of two vectors
	/// </summary>
	static float dot(const float3& v1, const float3& v2);

	/// <summary>
	/// Compute vector product of two vectors
	/// </summary>
	static float3 cross(const float3& v1, const float3& v2);

	/// <summary>
	/// Compute sum of two vectors
	/// </summary>
	float3 operator+(const float3& v) const;

	/// <summary>
	/// Compute difference of two vectors
	/// </summary>
	float3 operator-(const float3& v) const;

	/// <summary>
	/// Compute componentwise product of two vectors
	/// </summary>
	float3 operator*(const float3& v) const;

	/// <summary>
	/// Compute product of vector and scalar
	/// </summary>
	float3 operator*(float f) const;

	/// <summary>
	/// Compute quotient of vector and scalar
	/// </summary>
	float3 operator/(float f) const;

	/// <summary>
	/// Create copy of vector with negated components
	/// </summary>
	float3 operator-() const;

	/// <summary>
	/// Add vector to another
	/// </summary>
	float3& operator+=(const float3& v);

	/// <summary>
	/// Subtract vector from another
	/// </summary>
	float3& operator-=(const float3& v);

	/// <summary>
	/// Multiply vector by another componentwise
	/// </summary>
	float3& operator*=(const float3& v);

	/// <summary>
	/// Multiply vector by scalar
	/// </summary>
	float3& operator*=(float f);

	/// <summary>
	/// Divide vector by scalar
	/// </summary>
	float3& operator/=(float f);

	float& operator[](int i);
};


/// <summary>
/// Compute product of scalar and vector
/// </summary>
float3 operator*(float f, const float3& v);

/// <summary>
/// Put string representation of Vector3 into output stream 
/// </summary>
std::ostream& operator<<(std::ostream& os, const float3& vector);