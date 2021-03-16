#pragma once

#include "float3.hpp"
#include "Triangle.hpp"

class Image
{
public:
	Image(unsigned width, unsigned height, unsigned data[] = nullptr);

	void setPixels(unsigned data[]);
	void setPixel(float x, float y, float3 value);
	unsigned* getPixels();

	void colorFill(unsigned r, unsigned g, unsigned b, unsigned a);
	void colorFill(Triangle& tri);

	unsigned getWidth() { return width; }
	unsigned getHeight() { return height; }

private:
	unsigned makeColor(unsigned r, unsigned g, unsigned b, unsigned a);
	unsigned floatToInt(float value);
	float toCanonical(unsigned value);
	
	unsigned width, height;
	unsigned* data;
};
