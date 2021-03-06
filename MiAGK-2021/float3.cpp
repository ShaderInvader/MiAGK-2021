#include "float3.hpp"


#include <algorithm>
#include <cmath>


#include "Color.hpp"
#include "float4.hpp"

float3::float3()
{
	x = 0;
	y = 0;
	z = 0;
}

float3::float3(float value)
{
	x = value;
	y = value;
	z = value;
}

float3::float3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float3::float3(const float3& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

float3::float3(float4 vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

float3::float3(Color color)
{
	constexpr float div = 1.0f / 255.0f;
	x = color.r * div;
	y = color.g * div;
	z = color.b * div;
}

float3 float3::Zero()
{
	return { 0.0f, 0.0f, 0.0f };
}

float3 float3::One()
{
	return { 1.0f, 1.0f, 1.0f };
}

float3 float3::Up()
{
	return { 0.0f, 1.0f, 0.0f };
}

float3 float3::Right()
{
	return { 1.0f, 0.0f, 0.0f };
}

float3 float3::Forward()
{
	return { 0.0f, 0.0f, 1.0f };
}

float float3::magnitude() const
{
	return std::sqrt(x * x + y * y + z * z);
}

float float3::squareMagnitude() const
{
	return x * x + y * y + z * z;
}

void float3::normalize()
{
	if (!isZero())
		*this /= magnitude();
}

float3 float3::normalized() const
{
	if (!isZero())
		return float3(x, y, z) / magnitude();
	else
		return float3(0.0f);
}

bool float3::isZero() const
{
	return std::fpclassify(x) == FP_ZERO
		&& std::fpclassify(y) == FP_ZERO
		&& std::fpclassify(z) == FP_ZERO;
}

std::string float3::to_string() const
{
	return std::string("[") + std::to_string(x)
		+ ", " + std::to_string(y)
		+ ", " + std::to_string(z) + "]";
}

float float3::dot(const float3& v1, const float3& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float3 float3::cross(const float3& v1, const float3& v2)
{
	return {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};
}

float3 float3::clamp01()
{
	float3 output;
	output.x = std::clamp(x, 0.0f, 1.0f);
	output.y = std::clamp(y, 0.0f, 1.0f);
	output.z = std::clamp(z, 0.0f, 1.0f);
	return output;
}

float3 float3::operator+(const float3& v) const
{
	return { x + v.x, y + v.y, z + v.z };
}

float3 float3::operator-(const float3& v) const
{
	return { x - v.x, y - v.y, z - v.z };
}

float3 float3::operator*(const float3& v) const
{
	return { x * v.x, y * v.y, z * v.z };
}

float3 float3::operator*(float f) const
{
	return { x * f, y * f, z * f };
}

float3 float3::operator/(float f) const
{
	return { x / f, y / f, z / f };
}

float3 float3::operator-() const
{
	return { -x, -y, -z };
}

float3& float3::operator+=(const float3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

float3& float3::operator-=(const float3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

float3& float3::operator*=(const float3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

float3& float3::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

float3& float3::operator/=(float f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

float& float3::operator[](int i)
{
	switch (i)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default:
		throw std::out_of_range("float3 [] operator overflow");
	}
}

float3 operator*(float f, const float3& v)
{
	return float3(f * v.x, f * v.y, f * v.z);
}

std::ostream& operator<<(std::ostream& os, const float3& vector)
{
	return os << vector.to_string();
}
