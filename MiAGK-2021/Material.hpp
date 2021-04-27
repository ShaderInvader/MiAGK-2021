#pragma once
#include "float3.hpp"

class Shader;

struct Material
{
	Shader* shader;
	
	float3 diffuse;
	float3 specular;
};
