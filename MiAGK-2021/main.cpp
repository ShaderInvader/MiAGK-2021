#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "Image.hpp"
#include "Triangle.hpp"

int main(int argc, char* argv[])
{
	Image img(512, 512);
	Triangle tri(
		{ -0.5f, 0.5f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.5f, -0.5f, 0.0f }
	);
	img.colorFill(tri);

	stbi_write_tga("generated/xd.tga", img.getWidth(), img.getHeight(), 4, img.getPixels());
}
