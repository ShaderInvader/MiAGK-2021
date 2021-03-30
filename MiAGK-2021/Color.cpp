#include "Color.hpp"

Color::Color()
{
	r = g = b = 0;
}

Color::Color(int r, int g, int b) : Color(r, g, b, 255)
{}

Color::Color(int r, int g, int b, int a)
{
	this->r = static_cast<uint8_t>(r);
	this->g = static_cast<uint8_t>(g);
	this->b = static_cast<uint8_t>(b);
	this->a = static_cast<uint8_t>(a);
}

Color::Color(float r, float g, float b) : Color(r, g, b, 1.0f)
{}

Color::Color(float r, float g, float b, float a)
{
	this->b = static_cast<uint8_t>(b * 255.0f);
	this->g = static_cast<uint8_t>(g * 255.0f);
	this->r = static_cast<uint8_t>(r * 255.0f);
	this->a = static_cast<uint8_t>(a * 255.0f);
}

unsigned Color::getEncoded() const
{
	unsigned color = 0;
	color |= a;
	color <<= 8;
	color |= b;
	color <<= 8;
	color |= g;
	color <<= 8;
	color |= r;
	return color;
}

Color Color::operator+(Color c) const
{
	const size_t newR = r + c.r;
	const size_t newG = g + c.g;
	const size_t newB = b + c.b;
	return Color(static_cast<uint8_t>(newR),
		static_cast<uint8_t>(newG),
		static_cast<uint8_t>(newB));
}

Color Color::operator-(Color c) const
{
	const size_t newR = r - c.r;
	const size_t newG = g - c.g;
	const size_t newB = b - c.b;
	return Color(static_cast<uint8_t>(newR),
		static_cast<uint8_t>(newG),
		static_cast<uint8_t>(newB));
}

Color Color::operator*(Color c) const
{
	const size_t newR = r * c.r;
	const size_t newG = g * c.g;
	const size_t newB = b * c.b;
	return Color(static_cast<uint8_t>(newR),
		static_cast<uint8_t>(newG),
		static_cast<uint8_t>(newB));
}

Color Color::operator*(float mul) const
{
	const size_t newR = r * mul;
	const size_t newG = g * mul;
	const size_t newB = b * mul;
	return Color(static_cast<uint8_t>(newR),
		static_cast<uint8_t>(newG),
		static_cast<uint8_t>(newB));
}

Color Color::operator/(float mul) const
{
	const size_t newR = r / mul;
	const size_t newG = g / mul;
	const size_t newB = b / mul;
	return Color(static_cast<uint8_t>(newR),
		static_cast<uint8_t>(newG),
		static_cast<uint8_t>(newB));
}

std::string Color::to_string() const
{
	return std::string("[ r: ") + std::to_string(r) +
		", g: " + std::to_string(g) +
		", b: " + std::to_string(b) + " ]";
}

Color operator*(float mul, Color c)
{
	const size_t newR = c.r * mul;
	const size_t newG = c.g * mul;
	const size_t newB = c.b * mul;
	return Color(static_cast<uint8_t>(newR),
		static_cast<uint8_t>(newG),
		static_cast<uint8_t>(newB));
}

std::ostream& operator<<(std::ostream& os, Color c)
{
	return os << c.to_string();
}