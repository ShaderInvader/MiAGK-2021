#pragma once
#include "Shader.hpp"

class GouraudShader : public Shader
{
public:
	Color sample(const Triangle* tri, float3 barycentric, float3 normal) override;

};