#pragma once

#include <vector>

#include "Material.hpp"
#include "Triangle.hpp"

class Buffer;

class Mesh
{
public:
	Material* material;
	
	static Color c0, c1, c2;

	static Mesh* triangle(float3 p1, float3 p2, float3 p3);
	static Mesh* cone(float r, float h, int sides);
	static Mesh* cylinder(float r, float h, int sides, int cuts);
	static Mesh* torus(float r1, float r2, int nSegs, int nSides);
	static Mesh* ramiel();

	void smoothNormals();
	void render(Buffer& buffer);
	
private:
	Mesh() = default;
	explicit Mesh(int nTriangles);
	static float3 pOnCircleY(float angle, float radius, float3 center = {0.0f, 0.0f, 0.0f});
	static float3 pOnTorus(float phi, float theta, float r1, float r2);
	std::vector<Vertex_NC*> findVertices(float3 position);
	std::vector<Triangle> triangles;
};
