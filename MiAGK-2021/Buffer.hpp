#pragma once

#include "float3.hpp"
#include "Triangle.hpp"
#include "Color.hpp"

class Buffer
{
public:
	Buffer(unsigned width, unsigned height, unsigned data[] = nullptr);

	void setPixels(unsigned data[]);
	void setPixel(float x, float y, Color color);
	unsigned* getPixels();

	void clearColor(Color color);
	void draw(Triangle& tri);

	unsigned getWidth() { return width; }
	unsigned getHeight() { return height; }

private:
	unsigned floatToInt(float value);
	float toCanonical(unsigned value, unsigned dimensionRes);
	float toNormalized(float canonical);
	
	unsigned width, height;
	unsigned* data;
	float* depth;
};
