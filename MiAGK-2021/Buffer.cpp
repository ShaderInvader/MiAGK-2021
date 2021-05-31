#include "Buffer.hpp"
#include <algorithm>
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image.h"

Buffer::Buffer(unsigned width, unsigned height)
{
	this->width = width;
	this->height = height;
	channels = 4;
	this->pixels = new Color[width * height];
	this->depth = new float[width * height];
	for (int i = 0; i < width * height; ++i)
	{
		depth[i] = 1.0f;
	}
}

Buffer::Buffer(Buffer& buffer)
{
	width = buffer.width;
	height = buffer.height;
	channels = buffer.channels;
	pixels = new Color[width * height];
	for (int i = 0; i < width * height; ++i)
	{
		pixels[i] = buffer.getPixel(i);
	}
	depth = new float[width * height];
	for (int i = 0; i < width * height; ++i)
	{
		depth[i] = buffer.getDepth(i);
	}
}

Buffer::Buffer(std::string filePath)
{
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);

	pixels = new Color[width * height];
	depth = nullptr;

	const int range = width * height;
	for (int i = 0, j = 0; j < range; i += channels, ++j)
	{
		switch (channels)
		{
		case 1:
			pixels[j] = Color(static_cast<int>(data[i]), static_cast<int>(data[i]), static_cast<int>(data[i]));
			break;
		case 2:
			pixels[j] = Color(static_cast<int>(data[i]), static_cast<int>(data[i]), static_cast<int>(data[i]), data[i + 1]);
			break;
		case 3:
			pixels[j] = Color(static_cast<int>(data[i]), static_cast<int>(data[i + 1]), static_cast<int>(data[i + 2]));
			break;
		case 4:
			pixels[j] = Color(static_cast<int>(data[i]), data[i + 1], data[i + 2], data[i + 3]);
			break;
		default:
			break;
		}
	}

	stbi_image_free(data);
}

void Buffer::setPixel(float x, float y, Color color) const
{
	pixels[calculateIndex(x, y)] = color;
}

void Buffer::setPixel(int x, int y, Color color) const
{
	pixels[calculateIndex(x, y)] = color;
}

Color* Buffer::getPixels() const
{
	return pixels;
}

Color Buffer::getPixel(int index) const
{
	return pixels[index];
}

Color Buffer::getPixel(int x, int y) const
{
	return pixels[calculateIndex(x, y)];
}

Color Buffer::getPixel(float x, float y) const
{
	return pixels[calculateIndex((int)std::floor(x * width), (int)std::floor(y * height))];
}

float Buffer::getDepth(int x, int y) const
{
	return depth[calculateIndex(x, y)];
}

float Buffer::getDepth(int index) const
{
	return depth[index];
}

void Buffer::clearColor(Color color) const
{
	for (unsigned i = 0; i < width * height; ++i)
	{
		this->pixels[i] = color;
	}
}

void Buffer::saveToFile(std::string path) const
{
	stbi_write_png(path.c_str(), width, height, channels, pixels, width * channels * sizeof(uint8_t));
}

void Buffer::draw(Triangle& tri)
{
	if (vp != nullptr)
	{
		vp->transformTriangle(tri);
	}
	float3 minBounds = { -1.0f, -1.0f, 0.0f }, maxBounds = {1.0f, 1.0f, 0.0f};
	tri.calculateBounds(minBounds, maxBounds);
	int minX = std::clamp(canonicalToNormalized(minBounds.x), 0.0f, 1.0f) * width;
	int maxX = std::clamp(canonicalToNormalized(maxBounds.x), 0.0f, 1.0f) * width;
	int minY = std::clamp(canonicalToNormalized(minBounds.y), 0.0f, 1.0f) * height;
	int maxY = std::clamp(canonicalToNormalized(maxBounds.y), 0.0f, 1.0f) * height;
	
	for (int y = minY; y < maxY; ++y)
	{
		for (int x = minX; x < maxX; ++x)
		{
			int index = y * height + x;
			Color outColor = tri.rasterize(pixelsToCanonical(x, width), pixelsToCanonical(y, height), this->depth[index]);
			if (outColor.a > 0.0001f)
			{
				this->pixels[index] = outColor;
			}
		}
	}
}

unsigned Buffer::calculateIndex(int x, int y) const
{
	return y * width + x;
}

unsigned Buffer::calculateIndex(float x, float y) const
{
	return canonicalToPixels(-y, height) * width + canonicalToPixels(x, width);
}

float Buffer::pixelsToCanonical(int value, int resolution)
{
	return normalizedToCanonical(static_cast<float>(value) / static_cast<float>(resolution));
}

float Buffer::pixelsToNormalized(int value, int resolution)
{
	return static_cast<float>(value) / static_cast<float>(resolution);
}

unsigned Buffer::canonicalToPixels(float value, unsigned resolution)
{
	return static_cast<unsigned>(canonicalToNormalized(value) * static_cast<float>(resolution));
}

float Buffer::canonicalToNormalized(float canonical)
{
	return canonical * 0.5f + 0.5f;
}

float Buffer::normalizedToCanonical(float normalized)
{
	return normalized * 2.0f - 1.0f;
}