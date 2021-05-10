#include <iostream>

#include "Buffer.hpp"
#include "float4x4.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "PhongShader.hpp"
#include "Triangle.hpp"
#include "VertexProcessor.hpp"

constexpr int WINDOW_HEIGHT = 1920;
constexpr int WINDOW_WIDTH = 1920;

int main(int argc, char* argv[])
{
	VertexProcessor vp;
	vp.projection = VertexProcessor::makePerspective(80, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.01f, 100.0f);
	//vp.view = VertexProcessor::lookAt({ 0.5f, -0.5f, 2.5f }, { 0.75f, -0.75f, 0.5f }, float3::Up());
	vp.view = VertexProcessor::lookAt({ 0.0f, -0.3f, 2.5f }, { 0.0f, -0.5f, 0.0f }, float3::Up());
	Buffer img(WINDOW_WIDTH, WINDOW_HEIGHT);
	img.vp = &vp;

	float4x4 cylTrans = float4x4::identity();
	VertexProcessor::translate(cylTrans, { 2.0f, 0.25f, 1.0f });
	VertexProcessor::scale(cylTrans, { 0.5f, 0.5f, 0.5f });

	float4x4 coneTrans = float4x4::identity();
	VertexProcessor::translate(coneTrans, { -1.5f, -2.0f, 0.0f });
	VertexProcessor::rotate(coneTrans, 180, { 1.0f, 0.0f, 0.0f });
	VertexProcessor::scale(coneTrans, { 0.5f, 0.5f, 0.5f });

	float4x4 torusTrans = float4x4::identity();
	VertexProcessor::rotate(torusTrans, 90, { 1.0f, 0.0f, 0.0f });
	VertexProcessor::translate(torusTrans, { 0.0f, 0.0f, 1.0f });

	float4x4 ramielTrans = float4x4::identity();
	VertexProcessor::rotate(ramielTrans, 22, { 0.0f, 1.0f, 0.0f });
	
	PhongShader phongShader;
	Material phongMat;
	phongMat.shader = &phongShader;

	Light directional;
	directional.isDirectional = true;
	directional.direction = float3(1.0f, 1.0f, 0.0f).normalized();
	directional.diffuse = { 1.0f, 1.0f, 1.0f };
	Light::sceneLights.push_back(directional);
	
	Mesh* ramiel = Mesh::ramiel();
	ramiel->material = &phongMat;
	Mesh::c0 = {0.5f, 0.5f, 0.5f};
	Mesh::c1 = { 0.4f, 0.4f, 0.4f };
	Mesh::c2 = { 0.6f, 0.6f, 0.6f };
	Mesh* cone = Mesh::cone(1.0f, 1.0f, 16);
	cone->material = &phongMat;
	Mesh* cyl = Mesh::cylinder(0.5f, 2.0f, 16, 4);
	cyl->material = &phongMat;
	Mesh* torus = Mesh::torus(1.0f, 0.15f, 16, 8);
	torus->material = &phongMat;
	
	img.clearColor(Color(0.427f, 0.537f, 0.666f, 1.0f));
	vp.model = torusTrans;
	torus->render(img);
	vp.model = float4x4::identity();
	ramiel->render(img);
	vp.model = cylTrans;
	cyl->render(img);
	vp.model = coneTrans;
	cone->render(img);

	img.saveToFile("generated/xd.png");

	delete ramiel;
	delete cone;
	delete cyl;
	delete torus;
}