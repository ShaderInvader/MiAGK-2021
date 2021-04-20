#include "Mesh.hpp"

#include "Buffer.hpp"

constexpr float pi = 3.14159265358979323846f;
constexpr float twoPi = 6.283185307179586f;
constexpr float oneOverPi = 0.3183098861837906f;
constexpr float piOver180 = 0.017453292519943f;

Color Mesh::c0 = { 1.0f, 0.0f, 0.0f };
Color Mesh::c1 = { 0.0f, 1.0f, 0.0f };
Color Mesh::c2 = { 0.0f, 0.0f, 1.0f };

Mesh Mesh::cone(float r, float h, int sides)
{
	Mesh mesh;
	float step = (360.0f / static_cast<float>(sides)) * piOver180;
	
	for (float angle = 0.0f; angle < twoPi; angle += step)
	{
		float3 p0 = pOnCircle(angle, r);
		float3 p1 = pOnCircle(angle + step, r);
		mesh.triangles.emplace_back(p1, float3( 0.0f, h, 0.0f ), p0, c0, c1, c2);
		mesh.triangles.emplace_back(p0, float3( 0.0f, 0.0f, 0.0f ), p1, c0, c1, c2);
	}

	return mesh;
}

Mesh Mesh::cylinder(float r, float h, int sides, int cuts)
{
	Mesh mesh;
	float step = (360.0f / static_cast<float>(sides)) * piOver180;
	float rise = h / static_cast<float>(cuts);

	for (float angle = 0; angle < twoPi; angle += step)
	{
		for (int i = 0; i < cuts; ++i)
		{
			mesh.triangles.emplace_back(
				pOnCircle(angle, r, float3(0.0f, rise * i, 0.0f)), 
				pOnCircle(angle + step, r, float3(0.0f, rise * i, 0.0f)),
				pOnCircle(angle, r, float3(0.0f, rise * (i + 1), 0.0f)),
				c0, c1, c2
			);
			mesh.triangles.emplace_back(
				pOnCircle(angle, r, float3(0.0f, rise * (i + 1), 0.0f)),
				pOnCircle(angle + step, r, float3(0.0f, rise * i, 0.0f)),
				pOnCircle(angle + step, r, float3(0.0f, rise * (i + 1), 0.0f)),
				c0, c1, c2
			);
		}
		mesh.triangles.emplace_back(pOnCircle(angle, r), float3(0.0f, 0.0f, 0.0f), pOnCircle(angle + step, r), c0, c1, c2);
		mesh.triangles.emplace_back(pOnCircle(angle, r), float3(0.0f, h, 0.0f), pOnCircle(angle + step, r), c0, c1, c2);
	}

	return mesh;
}

Mesh Mesh::torus(float r1, float r2, int nSegs, int nSides)
{
	/*
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	vertices.resize(((long long)nSegments + 1) * ((long long)nSides + 1));

	for (int seg = 0; seg <= nSegments; seg++)
	{
		int currSeg = seg == nSegments ? 0 : seg;

		float t1 = static_cast<float>(currSeg) / nSegments * glm::two_pi<float>();
		glm::vec3 r1(glm::cos(t1) * radius1, 0.0f, glm::sin(t1) * radius1);

		for (int side = 0; side <= nSides; side++)
		{
			int currSide = side == nSides ? 0 : side;

			float t2 = (float)currSide / nSides * glm::two_pi<float>();
			glm::vec3 r2(glm::angleAxis(-t1, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec3(glm::sin(t2) * radius2, glm::cos(t2) * radius2, 0.0f));

			vertices[(long long)side + (long long)seg * ((long long)nSides + 1)] = r1 + r2;
		}
	}

	int nFaces = vertices.size();
	int nTriangles = nFaces * 2;
	int nIndices = nTriangles * 3;
	indices.resize(nIndices);

	int i = 0;
	for (int seg = 0; seg <= nSegments; seg++)
	{
		for (int side = 0; side <= nSides - 1; side++)
		{
			int current = side + seg * (nSides + 1);
			int next = side + (seg < nSegments ? (seg + 1) * (nSides + 1) : 0);

			if (i < nIndices - 6)
			{
				indices[i++] = current;
				indices[i++] = next;
				indices[i++] = next + 1;

				indices[i++] = current;
				indices[i++] = next + 1;
				indices[i++] = current + 1;
			}
		}
	}

	Mesh* outMesh = new Mesh(vertices, indices, {});
	return outMesh;*/
	return Mesh(0);
}

Mesh Mesh::ramiel()
{
	Color c1 = { 0.211f, 0.592f, 0.909f };
	Color c0 = { 0.0f, 0.09f, 0.529f };
	Color c2 = { 0.027f, 0.219f, 0.588f };
	
	Mesh mesh;
	mesh.triangles.emplace_back(
		float3( 0.0f, -1.0f, 0.0f),
		float3( 0.0f, 0.0f, 1.0f ),
		float3( 1.0f, 0.0f, 0.0f ),
		c0, c1, c2
	);
	mesh.triangles.emplace_back(
		float3(1.0f, 0.0f, 0.0f),
		float3(0.0f, 0.0f, 1.0f),
		float3(0.0f, 1.0f, 0.0f),
		c0, c1, c2
	);
	mesh.triangles.emplace_back(
		float3(0.0f, 1.0f, 0.0f),
		float3(0.0f, 0.0f, 1.0f),
		float3(-1.0f, 0.0f, 0.0f),
		c0, c1, c2
	);
	mesh.triangles.emplace_back(
		float3(-1.0f, 0.0f, 0.0f),
		float3(0.0f, 0.0f, 1.0f),
		float3(0.0f, -1.0f, 0.0f),
		c0, c1, c2
	);
	mesh.triangles.emplace_back(
		float3(0.0f, -1.0f, 0.0f),
		float3(1.0f, 0.0f, 0.0f),
		float3(0.0f, 0.0f, -1.0f),
		c0, c1, c2
	);
	mesh.triangles.emplace_back(
		float3(1.0f, 0.0f, 0.0f),
		float3(0.0f, 1.0f, 0.0f),
		float3(0.0f, 0.0f, -1.0f),
		c0, c1, c2
	);
	mesh.triangles.emplace_back(
		float3(0.0f, 1.0f, 0.0f),
		float3(-1.0f, 0.0f, 0.0f),
		float3(0.0f, 0.0f, -1.0f),
		c0, c1, c2
	);
	mesh.triangles.emplace_back(
		float3(-1.0f, 0.0f, 0.0f),
		float3(0.0f, -1.0f, 0.0f),
		float3(0.0f, 0.0f, -1.0f),
		c0, c1, c2
	);

	return mesh;
}

void Mesh::render(Buffer& buffer)
{
	for (auto triangle : triangles)
	{
		buffer.draw(triangle);
	}
}

Mesh::Mesh(int nTriangles)
{
	triangles.reserve(nTriangles);
}

float3 Mesh::pOnCircle(float angle, float radius, float3 center)
{
	return { radius * std::cos(angle) + center.x,
			 center.y,
			 radius * std::sin(angle) + center.z };
}
