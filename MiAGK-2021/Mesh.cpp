#include "Mesh.hpp"

#include "Buffer.hpp"

constexpr float pi = 3.14159265358979323846f;
constexpr float twoPi = 6.283185307179586f;
constexpr float oneOverPi = 0.3183098861837906f;
constexpr float piOver180 = 0.017453292519943f;

Color Mesh::c0 = { 1.0f, 0.0f, 0.0f };
Color Mesh::c1 = { 0.0f, 1.0f, 0.0f };
Color Mesh::c2 = { 0.0f, 0.0f, 1.0f };

Mesh* Mesh::triangle(float3 p1, float3 p2, float3 p3)
{
	Mesh* mesh = new Mesh(1);
	mesh->triangles.emplace_back(p1, p2, p3, mesh);

	return mesh;
}

Mesh* Mesh::cone(float r, float h, int sides)
{
	Mesh* mesh = new Mesh();
	float step = (360.0f / static_cast<float>(sides)) * piOver180;
	
	for (float angle = 0.0f; angle < twoPi; angle += step)
	{
		float3 p0 = pOnCircleY(angle, r);
		float3 p1 = pOnCircleY(angle + step, r);
		mesh->triangles.emplace_back(p0, float3( 0.0f, -h, 0.0f ), p1, c0, c1, c2, mesh);
		mesh->triangles.emplace_back(p1, float3( 0.0f, 0.0f, 0.0f ), p0, c0, c1, c2, mesh);
	}
	// This naive method of smooth normals generation is too aggressive for cone
	//mesh->smoothNormals();
	return mesh;
}

Mesh* Mesh::cylinder(float r, float h, int sides, int cuts)
{
	Mesh* mesh = new Mesh();
	float step = (360.0f / static_cast<float>(sides)) * piOver180;
	float rise = h / static_cast<float>(cuts);

	for (float angle = 0; angle < twoPi; angle += step)
	{
		for (int i = 0; i < cuts; ++i)
		{
			mesh->triangles.emplace_back(
				pOnCircleY(angle, r, float3(0.0f, rise * i, 0.0f)), 
				pOnCircleY(angle + step, r, float3(0.0f, rise * i, 0.0f)),
				pOnCircleY(angle, r, float3(0.0f, rise * (i + 1), 0.0f)),
				c0, c1, c2,
				mesh
			);
			mesh->triangles.emplace_back(
				pOnCircleY(angle, r, float3(0.0f, rise * (i + 1), 0.0f)),
				pOnCircleY(angle + step, r, float3(0.0f, rise * i, 0.0f)),
				pOnCircleY(angle + step, r, float3(0.0f, rise * (i + 1), 0.0f)),
				c0, c1, c2,
				mesh
			);
		}
		mesh->triangles.emplace_back(pOnCircleY(angle, r), float3(0.0f, 0.0f, 0.0f), pOnCircleY(angle + step, r), c0, c1, c2, mesh);
		mesh->triangles.emplace_back(pOnCircleY(angle + step, r, { 0.0f, h, 0.0f }), float3(0.0f, h, 0.0f), pOnCircleY(angle, r, { 0.0f, h, 0.0f }), c0, c1, c2, mesh);
	}
	mesh->smoothNormals();
	return mesh;
}

Mesh* Mesh::torus(float r1, float r2, int nSegs, int nSides)
{
	Mesh* mesh = new Mesh();
	float segStep = twoPi / nSegs;
	float sideStep = twoPi / nSides;

	float currTheta = 0.0f;
	float nextTheta = segStep;
	float currPhi = 0.0f;
	float nextPhi = sideStep;

	for (int i = 0; i < nSegs; ++i)
	{
		for (int j = 0; j < nSides; ++j)
		{
			mesh->triangles.emplace_back(
				pOnTorus(currPhi, currTheta, r1, r2),
				pOnTorus(nextPhi, currTheta, r1, r2),
				pOnTorus(currPhi, nextTheta, r1, r2),
				mesh
			);
			mesh->triangles.emplace_back(
				pOnTorus(currPhi, nextTheta, r1, r2),
				pOnTorus(nextPhi, currTheta, r1, r2),
				pOnTorus(nextPhi, nextTheta, r1, r2),
				mesh
			);
			
			currPhi += sideStep;
			nextPhi += sideStep;
		}
		currTheta += segStep;
		nextTheta += segStep;
	}
	mesh->smoothNormals();
	return mesh;
}

Mesh* Mesh::ramiel()
{
	Color c1 = { 0.211f, 0.592f, 0.909f };
	Color c0 = { 0.0f, 0.09f, 0.529f };
	Color c2 = { 0.027f, 0.219f, 0.588f };
	
	Mesh* mesh = new Mesh();
	mesh->triangles.emplace_back(
		float3( 0.0f, -1.0f, 0.0f),
		float3( 0.0f, 0.0f, 1.0f ),
		float3( 1.0f, 0.0f, 0.0f ),
		c0, c1, c2,
		mesh
	);
	mesh->triangles.emplace_back(
		float3(1.0f, 0.0f, 0.0f),
		float3(0.0f, 0.0f, 1.0f),
		float3(0.0f, 1.0f, 0.0f),
		c0, c1, c2,
		mesh
	);
	mesh->triangles.emplace_back(
		float3(0.0f, 1.0f, 0.0f),
		float3(0.0f, 0.0f, 1.0f),
		float3(-1.0f, 0.0f, 0.0f),
		c0, c1, c2,
		mesh
	);
	mesh->triangles.emplace_back(
		float3(-1.0f, 0.0f, 0.0f),
		float3(0.0f, 0.0f, 1.0f),
		float3(0.0f, -1.0f, 0.0f),
		c0, c1, c2,
		mesh
	);
	mesh->triangles.emplace_back(
		float3(0.0f, -1.0f, 0.0f),
		float3(1.0f, 0.0f, 0.0f),
		float3(0.0f, 0.0f, -1.0f),
		c0, c1, c2,
		mesh
	);
	mesh->triangles.emplace_back(
		float3(1.0f, 0.0f, 0.0f),
		float3(0.0f, 1.0f, 0.0f),
		float3(0.0f, 0.0f, -1.0f),
		c0, c1, c2,
		mesh
	);
	mesh->triangles.emplace_back(
		float3(0.0f, 1.0f, 0.0f),
		float3(-1.0f, 0.0f, 0.0f),
		float3(0.0f, 0.0f, -1.0f),
		c0, c1, c2,
		mesh
	);
	mesh->triangles.emplace_back(
		float3(-1.0f, 0.0f, 0.0f),
		float3(0.0f, -1.0f, 0.0f),
		float3(0.0f, 0.0f, -1.0f),
		c0, c1, c2,
		mesh
	);

	return mesh;
}

void Mesh::smoothNormals()
{
	// This is also a one huge ugly hack
	for (auto& triangle : triangles)
	{
		auto foundVertices = findVertices(triangle.v1.pos);
		for (auto && foundVertex : foundVertices)
		{
			triangle.tv1.norm += foundVertex->norm;
		}
		triangle.tv1.norm.normalize();

		foundVertices = findVertices(triangle.v2.pos);
		for (auto&& foundVertex : foundVertices)
		{
			triangle.tv2.norm += foundVertex->norm;
		}
		triangle.tv2.norm.normalize();

		foundVertices = findVertices(triangle.v3.pos);
		for (auto&& foundVertex : foundVertices)
		{
			triangle.tv3.norm += foundVertex->norm;
		}
		triangle.tv3.norm.normalize();
	}
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

float3 Mesh::pOnCircleY(float angle, float radius, float3 center)
{
	return { radius * std::cos(angle) + center.x,
			 center.y,
			 radius * std::sin(angle) + center.z };
}

float3 Mesh::pOnTorus(float phi, float theta, float r1, float r2)
{
	return {std::cos(theta) * (r1 + std::cos(phi) * r2),
			std::sin(theta) * (r1 + std::cos(phi) * r2),
			std::sin(phi) * r2};
}

std::vector<Vertex_NC*> Mesh::findVertices(float3 position)
{
	std::vector<Vertex_NC*> foundVertices;
	constexpr float delta = 0.0001f;
	
	for (auto && triangle : triangles)
	{
		if (std::abs(triangle.v1.pos.x - position.x) < delta && std::abs(triangle.v1.pos.y - position.y) < delta && std::abs(triangle.v1.pos.z - position.z) < delta)
		{
			foundVertices.push_back(&triangle.v1);
		}
		if (std::abs(triangle.v2.pos.x - position.x) < delta && std::abs(triangle.v2.pos.y - position.y) < delta && std::abs(triangle.v2.pos.z - position.z) < delta)
		{
			foundVertices.push_back(&triangle.v2);
		}
		if (std::abs(triangle.v3.pos.x - position.x) < delta && std::abs(triangle.v3.pos.y - position.y) < delta && std::abs(triangle.v3.pos.z - position.z) < delta)
		{
			foundVertices.push_back(&triangle.v3);
		}
	}
	return foundVertices;
}