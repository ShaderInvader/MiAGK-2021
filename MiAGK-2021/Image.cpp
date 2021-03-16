#include "Image.hpp"

Image::Image(unsigned width, unsigned height, unsigned data[])
{
	this->width = width;
	this->height = height;
	this->data = new unsigned[width * height];
	setPixels(data);
}

void Image::setPixels(unsigned data[])
{
	if (data != nullptr)
	{
		for (unsigned i = 0; i < width * height; ++i)
		{
			this->data[i] = data[i];
		}
	}
}

void Image::setPixel(float x, float y, float3 value)
{
	unsigned index = (static_cast<unsigned>(x) * width + static_cast<unsigned>(y) * height) * 4;
	data[index] = makeColor(floatToInt(value.x), floatToInt(value.y), floatToInt(value.z), 255);
}

unsigned* Image::getPixels()
{
	return data;
}

void Image::colorFill(unsigned r, unsigned g, unsigned b, unsigned a)
{
	unsigned color = makeColor(r, g, b, a);
	for (unsigned i = 0; i < width * height; ++i)
	{
		this->data[i] = color;
	}
}

void Image::colorFill(Triangle& tri)
{
	unsigned color = makeColor(255, 0, 0, 255);
	unsigned color1 = makeColor(0, 255, 255, 255);
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			this->data[j * height + i] = (tri.rasterize(toCanonical(i), toCanonical(j)) == 0.0f ? color : color1);
		}
	}
}


unsigned Image::makeColor(unsigned r, unsigned g, unsigned b, unsigned a)
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

unsigned Image::floatToInt(float value)
{
	return static_cast<unsigned>(value * 255);
}

float Image::toCanonical(unsigned value)
{
	return ((float)value / width) * 2.0f - 1.0f;
}

