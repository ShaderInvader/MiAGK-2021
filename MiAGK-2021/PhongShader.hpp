#pragma once
#include "Shader.hpp"

class PhongShader : public Shader
{
public:
	Color sample(const Triangle* tri, float3 barycentric, float3 normal) override;

};
