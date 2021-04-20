#include "VertexProcessor.hpp"

#include <cmath>

constexpr float PI = 3.14159265358979f;

VertexProcessor::VertexProcessor()
{
	model = float4x4::identity();
	view = float4x4::identity();
	projection = float4x4::identity();
}

float3 VertexProcessor::transformVertex(float4 vertex)
{
	vertex = float4x4::mul(vertex, model);
	vertex = float4x4::mul(vertex, view);
	vertex = float4x4::mul(vertex, projection);
	vertex /= vertex.w;
	return vertex;
}

void VertexProcessor::transformTriangle(Triangle& tri)
{
	tri.tv1.pos = transformVertex(float4(tri.v1.pos, 1.0f));
	tri.tv2.pos = transformVertex(float4(tri.v2.pos, 1.0f));
	tri.tv3.pos = transformVertex(float4(tri.v3.pos, 1.0f));
}

float4x4 VertexProcessor::makePerspective(float fovy, float aspectRatio, float nearPlane, float farPlane)
{
	fovy *= PI / 360.0f;
	float f = std::cos(fovy) / std::sin(fovy);
	float4x4 mat =
	{
		{f / aspectRatio, 0.0f, 0.0f, 0.0f},
		{0.0f, f, 0.0f, 0.0f},
		{0.0f, 0.0f, (farPlane + nearPlane)/(nearPlane - farPlane), -1.0f},
		{0.0f, 0.0f, (2.0f * farPlane * nearPlane)/(nearPlane - farPlane), 0.0f}
	};
	return mat;
}

float4x4 VertexProcessor::lookAt(float3 eye, float3 center, float3 up)
{
	float3 f = center - eye;
	f.normalize();
	up.normalize();
	float3 s = float3::cross(f, up);
	float3 u = float3::cross(s, f);
	/*float4x4 mat =
	{
		{s[0], u[0], -f[0], 0.0f},
		{s[1], u[1], -f[1], 0.0f},
		{s[2], u[2], -f[2], 0.0f},
		{-eye.x, -eye.y, -eye.z, 1.0f}
	};*/
	float4x4 mat =
	{
		{s[0], s[1], s[2], -eye.x},
		{u[0], u[1], u[2], -eye.y},
		{-f[0], -f[1], -f[2], -eye.z},
		{0.0f, 0.0f, 0.0f, 1.0f}
	};
	//mat.transpose();
	float4x4 ident = float4x4::identity();
	ident[3] = float4(-eye, 1.0f);
	return float4x4::mul(mat, ident);
}

void VertexProcessor::translate(float4x4& matrix, float3 translation)
{
	float4x4 tMat = getTranslationMatrix(translation);
	matrix = float4x4::mul(matrix, tMat);
}

void VertexProcessor::rotate(float4x4& matrix, float angle, float3 axis)
{
	float4x4 tMat = getRotationMatrix(angle, axis);
	matrix = float4x4::mul(tMat, matrix);
}

void VertexProcessor::scale(float4x4& matrix, float3 scale)
{
	float4x4 tMat = getScaleMatrix(scale);
	matrix = float4x4::mul(tMat, matrix);
}

float4x4 VertexProcessor::getTranslationMatrix(float3 t)
{
	return float4x4(
		{1.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 0.0f},
		{0.0f, 0.0f, 1.0f, 0.0f},
		{t.x, t.y, t.z, 1.0f}
	);
}

float4x4 VertexProcessor::getRotationMatrix(float angle, float3 axis)
{
	float radians = angle * PI / 180.0f;
	float s = std::sin(radians);
	float c = std::cos(radians);
	axis.normalize();
	return float4x4(
		{ (axis.x * axis.x * (1.0f - c) + c),			 (axis.y * axis.x * (1.0f - c) + axis.z * s), (axis.x * axis.z * (1.0f - c) - axis.y * s), 0.0f },
		{ (axis.x * axis.y * (1.0f - c) - axis.z * s), (axis.y * axis.y * (1.0f - c) + c),			(axis.y * axis.z * (1.0f - c) + axis.x * s), 0.0f },
		{ (axis.x * axis.z * (1.0f - c) - axis.y * s), (axis.y * axis.z * (1.0f - c) - axis.x * s), (axis.z * axis.z * (1.0f - c) + c),		   0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f}
	);
}

float4x4 VertexProcessor::getScaleMatrix(float3 s)
{
	return float4x4(
		{s.x, 0.0f, 0.0f, 0.0f},
		{0.0f, s.y, 0.0f, 0.0f},
		{0.0f, 0.0f, s.z, 0.0f},
		{0.0f, 0.0f, 0.0f, 1.0f}
	);
}
