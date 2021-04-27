#include "Shader.hpp"

float3 Shader::reflect(float3 incident, float3 normal)
{
	return incident - 2.0f * float3::dot(normal, incident) * normal;
}
