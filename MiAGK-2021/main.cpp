#include <iostream>

#include "Buffer.hpp"
#include "float4x4.hpp"
#include "Triangle.hpp"
#include "VertexProcessor.hpp"

int main(int argc, char* argv[])
{
	VertexProcessor vp;
	vp.projection = VertexProcessor::makePerspective(120, 1.0f, 0.01f, 100.0f);
	vp.view = VertexProcessor::lookAt({ 0.0f, 0.0f, 1.25f }, { -0.25f, 0.0f, 0.0f }, float3::Up());
	Buffer img(512, 512);
	img.vp = &vp;

	float4x4 modelMatrix = float4x4::identity();
	VertexProcessor::translate(modelMatrix, { 0.0f, 0.0f, 0.0f });
	VertexProcessor::rotate(modelMatrix, -25.0f, {0.0f, 0.0f, 1.0f});
	VertexProcessor::scale(modelMatrix, { 1.25f, 1.25f, 1.25f });
	
	vp.model = modelMatrix;
	
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
		{0.75f, 0.5f, 0.75f},
		{0.2f, 0.2f, 0.2f},
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
	img.draw(tri);
	img.draw(tri2);
	img.draw(tri3);

	img.saveToFile("generated/xd.png");
}
