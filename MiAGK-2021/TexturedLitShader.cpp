#include "TexturedLitShader.hpp"

#include <algorithm>

#include "Buffer.hpp"
#include "Light.hpp"

Color TexturedLitShader::sample(const Triangle* tri, float3 barycentric, float3 normal)
{
	float3 worldPos = float4x4::mul(float4(tri->v1.pos, 1.0f), VertexProcessor::instance->model) * barycentric.x + float4x4::mul(float4(tri->v2.pos, 1.0f), VertexProcessor::instance->model) * barycentric.y + float4x4::mul(float4(tri->v3.pos, 1.0f), VertexProcessor::instance->model) * barycentric.z;
	float3 diffuse = 0.0f;
	for (auto& light : Light::sceneLights)
	{
		if (light.isDirectional)
		{
			diffuse += std::max(float3::dot(light.direction, normal), 0.0f) * light.diffuse;
		}
		else
		{
			// Basically a huge hack, but it works :D
			float3 lightDir = (light.position - worldPos).normalized();
			diffuse += std::max(float3::dot(lightDir, normal), 0.0f) * light.diffuse * mainTex->getPixel(std::clamp(std::abs(worldPos.x), 0.0f, 1.0f), std::clamp(std::abs(worldPos.y), 0.0f, 1.0f));
		}
	}
	return diffuse.clamp01();
	//mainTex->getPixel(std::clamp(std::abs(worldPos.x), 0.0f, 0.9f), std::clamp(std::abs(worldPos.y), 0.0f, 0.9f));
}
