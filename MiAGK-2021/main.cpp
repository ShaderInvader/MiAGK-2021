#include <iostream>

#include "Buffer.hpp"
#include "float4x4.hpp"
#include "Triangle.hpp"
#include "VertexProcessor.hpp"

int main(int argc, char* argv[])
{
	VertexProcessor vp;
	vp.projection = VertexProcessor::makePerspectiveMatrix(120, 1.0f, 0.1f, 100.0f);
	Buffer img(512, 512);
	img.vp = &vp;
	Triangle tri(
		{ -0.5f, 0.5f, 0.5f },
		{ 0.0f, 1.0f, 0.5f },
		{ 0.5f, -0.5f, 0.5f },
		Color(1.0f, 0.0f, 0.0f),
		Color(0.0f, 1.0f, 0.0f),
		Color(0.0f, 0.0f, 1.0f)
	);
	Triangle tri2(
		{-1.3f, 0.35f, 0.0f},
		{0.75f, 0.3f, 1.0f},
		{0.0f, -0.2f, 0.0f},
		Color(0.0f, 1.0f, 0.0f),
		Color(0.0f, 0.5f, 0.5f),
		Color(0.0f, 0.0f, 1.0f)
	);
	Triangle tri3(
		{ 0.0f, 1.0f, 0.5f},
		{0.5f, 0.5f, 0.5f},
		{0.5f, -0.5f, 0.5f},
		Color(1.0f, 0.0f, 0.0f),
		Color(0.0f, 1.0f, 0.0f),
		Color(0.0f, 0.0f, 1.0f)
	);
	img.clearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
	img.draw(tri2);
	img.draw(tri);
	img.draw(tri3);

	img.saveToFile("generated/xd.png");

	float4x4 testMat = 
	{
		{2, 3, 4, 5},
		{2, 3, 4, 5},
		{2, 3, 4, 5},
		{2, 3, 4, 5}
	};
	float4x4 testMat2 =
	{
		{3, 4, 5, 6},
		{3, 4, 5, 6},
		{3, 4, 5, 6},
		{3, 4, 5, 6}
	};
	float4 testVec = { 1, 2, 3, 4 };
	std::cout << float4x4::mul(testMat, testMat2).to_string();
	std::cout << "Vector x matrix:\n";
	std::cout << float4x4::mul(testVec, testMat2).to_string();
}
