#include "PhongShader.hpp"

#include "Light.hpp"

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
			//float3 lightDir = light.position
		}
	}
	return diffuse.clamp01();
}
