#pragma once

#include "float3.hpp"

class Triangle
{
public:
	Triangle();
	Triangle(float3 p1, float3 p2, float3 p3);

	void setVerts(float3 p1, float3 p2, float3 p3);

	float rasterize(float x, float y);

private:
	float3 p1, p2, p3;
	float3 min, max;

	void calculateBounds();
	float getMin(float x, float y);
	float getMax(float x, float y);
};