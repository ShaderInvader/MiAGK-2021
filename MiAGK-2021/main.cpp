#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Buffer.hpp"
#include "Triangle.hpp"

int main(int argc, char* argv[])
{
	Buffer img(512, 512);
	Triangle tri(
		{ -0.5f, 0.5f, 0.5f },
		{ 0.0f, 1.0f, 0.5f },
		{ 0.5f, -0.5f, 0.5f },
		Color(1.0f, 0.0f, 0.0f),
		Color(0.0f, 1.0f, 0.0f),
		Color(0.0f, 0.0f, 1.0f)
	);
	Triangle tri2(
		{ -1.3f, 0.35f, 0.0f },
		{ 0.75f, 0.3f, 1.0f },
		{ 0.0f, -0.2f, 0.0f },
		Color(0.0f, 1.0f, 0.0f),
		Color(0.0f, 0.5f, 0.5f),
		Color(0.0f, 0.0f, 1.0f)
	);
	Triangle tri3(
		{ 0.0f, 1.0f, 0.5f },
		{ 0.5f, 0.5f, 0.5f },
		{ 0.5f, -0.5f, 0.5f },
		Color(1.0f, 0.0f, 0.0f),
		Color(0.0f, 1.0f, 0.0f),
		Color(0.0f, 0.0f, 1.0f)
	);
	img.clearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
	img.draw(tri2);
	img.draw(tri);
	img.draw(tri3);

	stbi_write_tga("generated/xd.tga", img.getWidth(), img.getHeight(), 4, img.getPixels());
}
