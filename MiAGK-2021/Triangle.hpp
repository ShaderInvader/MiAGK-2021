#pragma once

#include "Color.hpp"
#include "Vertex.hpp"

struct Triangle
{
	Triangle();
	Triangle(float3 p1, float3 p2, float3 p3);
	Triangle(float3 p1, float3 p2, float3 p3, Color c1, Color c2, Color c3);

	Vertex_C v1, v2, v3;
	Vertex tv1, tv2, tv3;
	
	void setVerts(float3 p1, float3 p2, float3 p3);
	void calculateBounds(float3& min, float3& max) const;
	Color rasterize(float x, float y, float& depth);
};