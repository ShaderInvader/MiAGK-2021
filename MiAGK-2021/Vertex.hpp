#pragma once
#include "Color.hpp"
#include "float3.hpp"

struct Vertex
{
	float3 pos;
};

struct Vertex_C
{
	float3 pos;
	Color col;
};

struct Vertex_N
{
	float3 pos;
	float3 norm;
};

struct Vertex_NC
{
	float3 pos;
	float3 norm;
	Color col;
};
