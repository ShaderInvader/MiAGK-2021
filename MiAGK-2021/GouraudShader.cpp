#include "GouraudShader.hpp"

#include "Light.hpp"
#include "Triangle.hpp"

Color GouraudShader::sample(const Triangle* tri, float3 barycentric, float3 normal)
{
	return Color(tri->tv1.col * barycentric.x + tri->tv2.col * barycentric.y + tri->tv3.col * barycentric.z);
}
