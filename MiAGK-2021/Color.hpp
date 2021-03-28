#pragma once
#include <cstdint>

struct Color
{
	uint8_t b, g, r, a;

	Color()
	{
		b = 0;
		g = 0;
		r = 0;
		a = 0;
	}
	
	Color(uint8_t r, uint8_t g, uint8_t b)
	{
		this->b = b;
		this->g = g;
		this->r = r;
		this->a = 255;
	}
	
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
	{
		this->b = b;
		this->g = g;
		this->r = r;
		this->a = a;
	}
	
	Color(float r, float g, float b)
	{
		this->b = static_cast<uint8_t>(b * 255);
		this->g = static_cast<uint8_t>(g * 255);
		this->r = static_cast<uint8_t>(r * 255);
		this->a = 255;
	}
	
	Color(float r, float g, float b, float a)
	{
		this->b = static_cast<uint8_t>(b * 255);
		this->g = static_cast<uint8_t>(g * 255);
		this->r = static_cast<uint8_t>(r * 255);
		this->a = static_cast<uint8_t>(a * 255);
	}

	
	/// <summary>
	/// A safe way of getting the 32 bit color representation
	/// </summary>
	/// <returns>32bit little endian color representation</returns>
	unsigned getEncoded()
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

	Color operator*(float val) const
	{
		Color col;
		col.r = static_cast<uint8_t>(val * (float)r);
		col.g = static_cast<uint8_t>(val * (float)g);
		col.b = static_cast<uint8_t>(val * (float)b);
		col.a = a;
		return col;
	}

	Color operator+(Color col) const
	{
		Color out;
		out.r = static_cast<uint8_t>((unsigned)col.r + (unsigned)r);
		out.g = static_cast<uint8_t>((unsigned)col.g + (unsigned)g);
		out.b = static_cast<uint8_t>((unsigned)col.b + (unsigned)b);
		out.a = static_cast<uint8_t>((unsigned)col.a + (unsigned)a);
		return out;
	}
};