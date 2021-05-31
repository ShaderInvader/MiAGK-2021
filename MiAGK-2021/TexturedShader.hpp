#pragma once
#include "Shader.hpp"

class Buffer;

class TexturedShader : public Shader
{
public:
	Color sample(const Triangle* tri, float3 barycentric, float3 normal) override;

	Buffer* mainTex;
};
