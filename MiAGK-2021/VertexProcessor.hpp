#pragma once
#include "float4x4.hpp"
#include "Triangle.hpp"

class VertexProcessor
{
public:
	VertexProcessor();

	float3 transformVertex(float4 vertex);
	float3 transformNormal(float4 normal);
	void transformTriangle(Triangle& tri);
	
	static float4x4 makePerspective(float fovy, float aspectRatio, float nearPlane, float farPlane);
	static float4x4 lookAt(float3 eye, float3 center, float3 up);
	static void translate(float4x4& matrix, float3 translation);
	static void rotate(float4x4& matrix, float angle, float3 axis);
	static void scale(float4x4& matrix, float3 scale);
	static float4x4 getTranslationMatrix(float3 t);
	static float4x4 getRotationMatrix(float angle, float3 axis);
	static float4x4 getScaleMatrix(float3 s);

	// Union declarations for different matrix names which do the same
	union
	{
		float4x4 obj2world;
		float4x4 model;
	};
	
	union
	{
		float4x4 world2view;
		float4x4 view;
	};

	union
	{
		float4x4 view2projection;
		float4x4 projection;
	};
};
