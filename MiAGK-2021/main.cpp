#include <iostream>

#include "Buffer.hpp"
#include "float4x4.hpp"
#include "Triangle.hpp"
#include "VertexProcessor.hpp"

constexpr int WINDOW_HEIGHT = 1920;
constexpr int WINDOW_WIDTH = 1920;

int main(int argc, char* argv[])
{
	VertexProcessor vp;
	vp.projection = VertexProcessor::makePerspective(80, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.01f, 100.0f);
	vp.view = VertexProcessor::lookAt({ 0.5f, -0.5f, 2.5f }, { 0.75f, -0.75f, 0.5f }, float3::Up());
	Buffer img(WINDOW_WIDTH, WINDOW_HEIGHT);
	img.vp = &vp;

	float4x4 modelMatrix = float4x4::identity();
	VertexProcessor::translate(modelMatrix, { 0.0f, 0.0f, 0.0f });
	//VertexProcessor::rotate(modelMatrix, -35.0f, { 0.0f, 0.0f, 1.0f });
	//VertexProcessor::scale(modelMatrix, { 1.25f, 1.25f, 1.25f });

	vp.model = modelMatrix;

	Color c1 = { 0.211f, 0.592f, 0.909f };
	Color c0 = { 0.0f, 0.09f, 0.529f };
	Color c2 = { 0.027f, 0.219f, 0.588f };
	
	Triangle tri0(
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f },
		c0, c1, c2
	);

	Triangle tri1(
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f },
		c0, c1, c2
	);

	Triangle tri2(
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ -1.0f, 0.0f, 0.0f },
		c0, c1, c2
	);

	Triangle tri3(
		{ -1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, -1.0f, 0.0f },
		c0, c1, c2
	);

	Triangle tri4(
		{ 0.0f, -1.0f, 0.0f },
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, -1.0f },
		c0, c1, c2
	);

	Triangle tri5(
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, -1.0f },
		c0, c1, c2
	);

	Triangle tri6(
		{ 0.0f, 1.0f, 0.0f },
		{ -1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, -1.0f },
		c0, c1, c2
	);

	Triangle tri7(
		{ -1.0f, 0.0f, 0.0f },
		{ 0.0f, -1.0f, 0.0f },
		{ 0.0f, 0.0f, -1.0f },
		c0, c1, c2
	);
	
	img.clearColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
	img.draw(tri0);
	img.draw(tri1);
	img.draw(tri2);
	img.draw(tri3);
	img.draw(tri4);
	img.draw(tri5);
	img.draw(tri6);
	img.draw(tri7);

	img.saveToFile("generated/xd.png");
}