#include "float4.hpp"

#include <cmath>
#include <exception>

#include "float3.hpp"

float4::float4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{}

float4::float4(float value) : x(value), y(value), z(value), w(value)
{}

float4::float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{}

float4::float4(float3 v, float w) : x(v.x), y(v.y), z(v.z), w(w)
{}

float float4::magnitude() const
{
	return std::sqrtf(x * x + y * y + z * z + w * w);
}

float float4::squareMagnitude() const
{
	return x * x + y * y + z * z + w * w;
}

void float4::normalize()
{
	*this /= magnitude();
}

float4 float4::normalized() const
{
	return float4(*this) / magnitude();
}

bool float4::isZero()
{
	return std::fpclassify(x) == FP_ZERO
		&& std::fpclassify(y) == FP_ZERO
		&& std::fpclassify(z) == FP_ZERO
		&& std::fpclassify(w) == FP_ZERO;
}

std::string float4::to_string() const
{
	return std::string("[") + std::to_string(x)
		+ ", " + std::to_string(y)
		+ ", " + std::to_string(z)
		+ ", " + std::to_string(w) + "]";
}

float float4::dot(const float4& v1, const float4& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}

float4 float4::operator+(const float4& v) const
{
	return { x + v.x, y + v.y, z + v.z, w + v.w };
}

float4 float4::operator-(const float4& v) const
{
	return { x - v.x, y - v.y, z - v.z, w - v.w };
}

float4 float4::operator*(const float4& v) const
{
	return { x * v.x, y * v.y, z * v.z, w * v.w };
}

float4 float4::operator*(float f) const
{
	return { x * f, y * f, z * f, w * f };
}

float4 float4::operator/(float f) const
{
	return { x / f, y / f, z / f, w / f };
}

float4 float4::operator-() const
{
	return { -x, -y, -z, -w };
}

float4& float4::operator+=(const float4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}

float4& float4::operator-=(const float4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}

float4& float4::operator*=(const float4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
	return *this;
}

float4& float4::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;
	return *this;
}

float4& float4::operator/=(float f)
{
	x /= f;
	y /= f;
	z /= f;
	w /= f;
	return *this;
}

float& float4::operator[](int i)
{
	switch (i)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default:
		throw std::out_of_range("float4 [] operator overflow");
	}
}

float4 operator*(float f, const float4& v)
{
	return float4(f * v.x, f * v.y, f * v.z, f * v.w);
}

std::ostream& operator<<(std::ostream& os, const float4& vector)
{
	return os << vector.to_string();
}
