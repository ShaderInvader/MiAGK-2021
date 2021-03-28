#include "Buffer.hpp"
#include <algorithm>

Buffer::Buffer(unsigned width, unsigned height, unsigned data[])
{
	this->width = width;
	this->height = height;
	this->data = new unsigned[width * height];
	this->depth = new float[width * height];
	for (int i = 0; i < width * height; i++)
	{
		this->depth[i] = 1.0f;
	}
	setPixels(data);
}

void Buffer::setPixels(unsigned data[])
{
	if (data != nullptr)
	{
		for (unsigned i = 0; i < width * height; ++i)
		{
			this->data[i] = data[i];
		}
	}
}

void Buffer::setPixel(float x, float y, Color color)
{
	unsigned index = (static_cast<unsigned>(x) * width + static_cast<unsigned>(y) * height);
	data[index] = color.getEncoded();
}

unsigned* Buffer::getPixels()
{
	return data;
}

void Buffer::clearColor(Color color)
{
	for (unsigned i = 0; i < width * height; ++i)
	{
		this->data[i] = color.getEncoded();
	}
}

void Buffer::draw(Triangle& tri)
{
	float3 minBounds = tri.getMinBounds();
	float3 maxBounds = tri.getMaxBounds();
	int minX = std::clamp(toNormalized(minBounds.x), 0.0f, 1.0f) * width;
	int maxX = std::clamp(toNormalized(maxBounds.x), 0.0f, 1.0f) * width;
	int minY = std::clamp(toNormalized(minBounds.y), 0.0f, 1.0f) * height;
	int maxY = std::clamp(toNormalized(maxBounds.y), 0.0f, 1.0f) * height;
	
	for (int x = minX; x < maxX; ++x)
	{
		for (int y = minY; y < maxY; ++y)
		{
			int index = y * height + x;
			Color outColor = tri.rasterize(toCanonical(x, width), toCanonical(y, height), this->depth[index]);
			if (outColor.a != 0)
			{
				this->data[index] = outColor.getEncoded();
				// Z-buffer test
				//this->data[index] = Color(this->depth[index], this->depth[index], this->depth[index]).getEncoded();
			}
		}
	}
}

unsigned Buffer::floatToInt(float value)
{
	return static_cast<unsigned>(value * 255);
}

float Buffer::toCanonical(unsigned value, unsigned dimensionRes)
{
	return ((float)value / dimensionRes) * 2.0f - 1.0f;
}

float Buffer::toNormalized(float canonical)
{
	return canonical * 0.5f + 0.5f;
}