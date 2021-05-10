#pragma once
#include <vector>

#include "float3.hpp"

class Light
{
public:
	static std::vector<Light> sceneLights;
	
	float3 position;
	float3 direction;
	bool isDirectional;

	float3 diffuse;
	float3 specular;
	float shininess;
};
