#pragma once

#include "Color.hpp"
#include "float3.hpp"

class Triangle
{
public:
	Triangle();
	Triangle(float3 p1, float3 p2, float3 p3);
	Triangle(float3 p1, float3 p2, float3 p3, Color c1, Color c2, Color c3);

	void setVerts(float3 p1, float3 p2, float3 p3);

	Color rasterize(float x, float y, float& depth);

	float3 getMinBounds();
	float3 getMaxBounds();

private:
	float3 p1, p2, p3;
	Color c1, c2, c3;
	float3 min, max;

	void calculateBounds();
	float getMin(float x, float y);
	float getMax(float x, float y);
};