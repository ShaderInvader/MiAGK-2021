#pragma once
#include <ostream>

class float3;

class float4
{
public:
	float x{}, y{}, z{}, w{};

	/// <summary>
	/// Create zero vector
	/// </summary>
	float4();

	/// <summary>
	/// Create vector assigning same value to all components
	/// </summary>
	/// <param name="value">initial value of all components</param>
	float4(float value);

	/// <summary>
	/// Create vector assigning different value to each component
	/// </summary>
	float4(float x, float y, float z, float w);
	
	/// <summary>
	/// Create vector assigning different value to each component
	/// </summary>
	float4(float3 v, float w);

	/// <summary>
	/// Create copy of given vector
	/// </summary>
	/// <param name="vector">original vector</param>
	float4(const float4& vector) = default;

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
	float4 normalized() const;

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
	static float dot(const float4& v1, const float4& v2);

	/// <summary>
	/// Compute sum of two vectors
	/// </summary>
	float4 operator+(const float4& v) const;

	/// <summary>
	/// Compute difference of two vectors
	/// </summary>
	float4 operator-(const float4& v) const;

	/// <summary>
	/// Compute componentwise product of two vectors
	/// </summary>
	float4 operator*(const float4& v) const;

	/// <summary>
	/// Compute product of vector and scalar
	/// </summary>
	float4 operator*(float f) const;

	/// <summary>
	/// Compute quotient of vector and scalar
	/// </summary>
	float4 operator/(float f) const;

	/// <summary>
	/// Create copy of vector with negated components
	/// </summary>
	float4 operator-() const;

	/// <summary>
	/// Add vector to another
	/// </summary>
	float4& operator+=(const float4& v);

	/// <summary>
	/// Subtract vector from another
	/// </summary>
	float4& operator-=(const float4& v);

	/// <summary>
	/// Multiply vector by another componentwise
	/// </summary>
	float4& operator*=(const float4& v);

	/// <summary>
	/// Multiply vector by scalar
	/// </summary>
	float4& operator*=(float f);

	/// <summary>
	/// Divide vector by scalar
	/// </summary>
	float4& operator/=(float f);

	float& operator[](int i);
};


/// <summary>
/// Compute product of scalar and vector
/// </summary>
float4 operator*(float f, const float4& v);

/// <summary>
/// Put string representation of Vector3 into output stream 
/// </summary>
std::ostream& operator<<(std::ostream& os, const float4& vector);