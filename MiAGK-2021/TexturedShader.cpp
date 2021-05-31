#include "TexturedShader.hpp"

#include <algorithm>


#include "Buffer.hpp"

Color TexturedShader::sample(const Triangle* tri, float3 barycentric, float3 normal)
{
	float3 worldPos = float4x4::mul(float4(tri->v1.pos, 1.0f), VertexProcessor::instance->model) * barycentric.x + float4x4::mul(float4(tri->v2.pos, 1.0f), VertexProcessor::instance->model) * barycentric.y + float4x4::mul(float4(tri->v3.pos, 1.0f), VertexProcessor::instance->model) * barycentric.z;
	return mainTex->getPixel(std::clamp(std::abs(worldPos.x), 0.0f, 0.9f), std::clamp(std::abs(worldPos.y), 0.0f, 0.9f));
}