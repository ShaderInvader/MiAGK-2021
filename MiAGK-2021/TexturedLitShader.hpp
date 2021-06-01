#pragma once
#include "Shader.hpp"

class Buffer;

class TexturedLitShader : public Shader
{
public:
	Color sample(const Triangle* tri, float3 barycentric, float3 normal) override;

	Buffer* mainTex;
};
#pragma once
