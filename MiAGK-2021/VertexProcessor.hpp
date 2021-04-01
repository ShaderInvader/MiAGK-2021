#pragma once
#include "float4x4.hpp"
#include "Triangle.hpp"

class VertexProcessor
{
public:
	VertexProcessor();

	float4 transformVertex(float4 vertex);
	void transformTriangle(Triangle& tri);
	
	static float4x4 makePerspectiveMatrix(float fovy, float aspectRatio, float nearPlane, float farPlane);
	static float4x4 makeLookAtMatrix();

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
