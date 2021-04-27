#pragma once

#include "Color.hpp"
#include "float3.hpp"

struct Triangle;

class Shader
{
public:
	virtual Color sample(const Triangle* tri, float3 barycentric, float3 normal) = 0;

	static float3 reflect(float3 incident, float3 normal);
};
