#include "VertexProcessor.hpp"

#include <cmath>

constexpr float PI = 3.14159265358979f;

VertexProcessor::VertexProcessor()
{
	model = float4x4::identity();
	view = float4x4::identity();
	projection = float4x4::identity();
}

float4 VertexProcessor::transformVertex(float4 vertex)
{
	return float4x4::mul(vertex, projection);
}

void VertexProcessor::transformTriangle(Triangle& tri)
{
	tri.tv1.pos = transformVertex(float4(tri.v1.pos, 1.0f));
	tri.tv2.pos = transformVertex(float4(tri.v2.pos, 1.0f));
	tri.tv3.pos = transformVertex(float4(tri.v3.pos, 1.0f));
}

float4x4 VertexProcessor::makePerspectiveMatrix(float fovy, float aspectRatio, float nearPlane, float farPlane)
{
	fovy *= PI / 360.0f;
	float f = std::cos(fovy) / std::sin(fovy);
	float4x4 mat =
	{
		{f / aspectRatio, 0.0f, 0.0f, 0.0f},
		{0.0f, f, 0.0f, 0.0f},
		{0.0f, 0.0f, (farPlane + nearPlane)/(nearPlane - farPlane), -1.0f},
		{0.0f, 0.0f, (2.0f * farPlane * nearPlane)/(nearPlane * farPlane), 0.0f}
	};
	return mat;
}

float4x4 VertexProcessor::makeLookAtMatrix()
{
	return float4x4::identity();
}
