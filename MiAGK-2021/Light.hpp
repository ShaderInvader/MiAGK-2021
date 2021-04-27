#pragma once
#include "float3.hpp"

class Light
{
public:
	float3 position;

	float3 diffuse;
	float3 specular;
	float shininess;
};
