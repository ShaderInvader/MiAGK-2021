#pragma once

#include "Color.hpp"
#include "Vertex.hpp"

class Mesh;

struct Triangle
{
	Triangle(Mesh* mesh);
	Triangle(float3 p1, float3 p2, float3 p3, Mesh* mesh);
	Triangle(float3 p1, float3 p2, float3 p3, Color c1, Color c2, Color c3, Mesh* mesh);

	Vertex_NC v1, v2, v3;
	Vertex_N tv1, tv2, tv3;

	Mesh* mesh;
	
	void generateNormals();
	void setVerts(float3 p1, float3 p2, float3 p3);
	void calculateBounds(float3& min, float3& max) const;
	float3 calculateBarycentric(float x, float y);
	float3 sampleNormal(float3 barycentric);
	
	Color rasterize(float x, float y, float& depth);

};
