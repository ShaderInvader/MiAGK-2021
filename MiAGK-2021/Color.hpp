#pragma once
#include <cstdint>
#include <string>
#include <ostream>

struct Color
{
	uint8_t r, g, b, a;

	Color();
	Color(int r, int g, int b);
	Color(int r, int g, int b, int a);
	Color(float r, float g, float b);
	Color(float r, float g, float b, float a);
	
	/// <summary>
	/// A safe way of getting the 32 bit color representation
	/// </summary>
	/// <returns>32bit little endian color representation</returns>
	unsigned getEncoded() const;

	/// <summary>
	/// Compute sum of two colors
	/// </summary>
	Color operator+(Color c) const;
	/// <summary>
	/// Compute difference of two colors
	/// </summary>
	Color operator-(Color c) const;
	/// <summary>
	/// Compute component-wise product of two colors 
	/// </summary>
	Color operator*(Color c) const;
	/// <summary>
	/// Compute product of color and scalar
	/// </summary>
	Color operator*(float mul) const;
	/// <summary>
	/// Compute quotient of color and scalar
	/// </summary>
	Color operator/(float mul) const;

	/// <summary>
	/// Create std::string from given color in format "[ r: {r}, g: {g}, b: {b} ]"
	/// </summary>
	[[nodiscard]] std::string to_string() const;
};

/// <summary>
/// Compute product of color and scalar
/// </summary>
Color operator*(float mul, Color c);

/// <summary>
/// Put string representation of color into output stream 
/// </summary>
std::ostream& operator<<(std::ostream& os, Color c);