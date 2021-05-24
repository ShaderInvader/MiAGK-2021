#include "PhongShader.hpp"

#include "Light.hpp"
#include "Triangle.hpp"
#include "VertexProcessor.hpp"

Color PhongShader::sample(const Triangle* tri, float3 barycentric, float3 normal)
{
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
			float3 worldPos = float4x4::mul(float4(tri->v1.pos, 1.0f), VertexProcessor::instance->model) * barycentric.x + float4x4::mul(float4(tri->v2.pos, 1.0f), VertexProcessor::instance->model) * barycentric.y + float4x4::mul(float4(tri->v3.pos, 1.0f), VertexProcessor::instance->model) * barycentric.z;
			float3 lightDir = (light.position - worldPos).normalized();
			diffuse += std::max(float3::dot(lightDir, normal), 0.0f) * light.diffuse;
		}
	}
	return diffuse.clamp01();
	//return Color(tri->tv1.col * barycentric.x + tri->tv2.col * barycentric.y + tri->tv3.col * barycentric.z);
}
