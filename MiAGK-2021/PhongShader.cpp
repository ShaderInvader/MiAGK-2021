#include "PhongShader.hpp"

#include "Light.hpp"
#include "Triangle.hpp"

Color PhongShader::sample(const Triangle* tri, float3 barycentric, float3 normal)
{
	//float3 diffuse = 0.0f;
	//for (auto& light : Light::sceneLights)
	//{
	//	if (light.isDirectional)
	//	{
	//		diffuse += std::max(float3::dot(light.direction, normal), 0.0f) * light.diffuse;
	//	}
	//	else
	//	{
	//		//float3 lightDir = light.position
	//	}
	//}
	
	return Color(tri->tv1.col * barycentric.x + tri->tv2.col * barycentric.y + tri->tv3.col * barycentric.z);
}
