#pragma once

#include <vector>

#include "Triangle.hpp"

class Buffer;

class Mesh
{
public:
	static Color c0, c1, c2;
	
	static Mesh cone(float r, float h, int sides);
	static Mesh cylinder(float r, float h, int sides, int cuts);
	static Mesh torus(float r1, float r2, int nSegs, int nSides);
	static Mesh ramiel();

	void render(Buffer& buffer);
	
private:
	Mesh() = default;
	explicit Mesh(int nTriangles);
	static float3 pOnCircleY(float angle, float radius, float3 center = {0.0f, 0.0f, 0.0f});
	static float3 pOnTorus(float phi, float theta, float r1, float r2);
	std::vector<Triangle> triangles;
};
