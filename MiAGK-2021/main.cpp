#include "Buffer.hpp"
#include "float4x4.hpp"
#include "Light.hpp"
#include "Mesh.hpp"
#include "GouraudShader.hpp"
#include "PhongShader.hpp"
#include "TexturedShader.hpp"
#include "VertexProcessor.hpp"

constexpr int WINDOW_HEIGHT = 1920;
constexpr int WINDOW_WIDTH = 1920;

int main(int argc, char* argv[])
{
	VertexProcessor vp;
	vp.projection = VertexProcessor::makePerspective(80, (float)WINDOW_WIDTH / WINDOW_HEIGHT, 0.01f, 100.0f);
	vp.view = VertexProcessor::lookAt({ 0.0f, -0.3f, 2.5f }, { 0.0f, -0.5f, 0.0f }, float3::Up());
	Buffer img(WINDOW_WIDTH, WINDOW_HEIGHT);
	img.vp = &vp;

	// Textures
	Buffer testTex("res/voltas.png");
	testTex.saveToFile("generated/textureTest.png");
	
	float4x4 cylTrans = float4x4::identity();
	VertexProcessor::translate(cylTrans, { 2.0f, 0.25f, 1.0f });
	VertexProcessor::scale(cylTrans, { 0.5f, 0.5f, 0.5f });

	float4x4 coneTrans = float4x4::identity();
	VertexProcessor::translate(coneTrans, { -1.5f, 2.0f, 0.0f });
	VertexProcessor::scale(coneTrans, { 0.5f, 0.5f, 0.5f });

	float4x4 torusTrans = float4x4::identity();
	VertexProcessor::translate(torusTrans, { 0.0f, 0.0f, 1.0f });
	VertexProcessor::rotate(torusTrans, 90, { 1.0f, 0.0f, 0.0f });

	float4x4 torusTrans2 = float4x4::identity();
	VertexProcessor::translate(torusTrans2, { 0.0f, 0.0f, 0.75f });
	VertexProcessor::rotate(torusTrans2, 90, { 1.0f, 0.0f, 0.0f });

	float4x4 ramielTrans = float4x4::identity();
	VertexProcessor::rotate(ramielTrans, 22, { 0.0f, 1.0f, 0.0f });
	
	PhongShader phongShader;
	Material phongMat;
	phongMat.shader = &phongShader;

	GouraudShader gouraudShader;
	Material gouraudMat;
	gouraudMat.shader = &gouraudShader;

	TexturedShader texturedShader;
	Material texturedMat;
	texturedMat.shader = &texturedShader;
	texturedShader.mainTex = &testTex;

	Light directional;
	directional.isDirectional = true;
	directional.direction = float3(-1.0f, -1.0f, 0.25f).normalized();
	directional.diffuse = { 0.0f, 0.0f, 1.0f };
	Light::sceneLights.push_back(directional);

	Light point;
	point.isDirectional = false;
	point.position = { 3.0f, 3.0f, 1.0f };
	point.diffuse = { 1.0f, 0.0f, 0.0f };
	Light::sceneLights.push_back(point);
	
	Mesh* ramiel = Mesh::ramiel();
	ramiel->material = &texturedMat;
	Mesh::c0 = { 0.5f, 0.5f, 0.5f };
	Mesh::c1 = { 0.4f, 0.4f, 0.4f };
	Mesh::c2 = { 0.6f, 0.6f, 0.6f };
	Mesh* cone = Mesh::cone(1.0f, 1.0f, 32);
	cone->material = &texturedMat;
	Mesh* cyl = Mesh::cylinder(0.5f, 2.0f, 32, 4);
	cyl->material = &texturedMat;
	Mesh* torus = Mesh::torus(1.0f, 0.15f, 16, 8);
	torus->material = &texturedMat;
	Mesh* torus2 = Mesh::torus(1.0f, 0.15f, 16, 8);
	torus2->material = &texturedMat;

	//Mesh* triangle = Mesh::triangle(
	//	{-0.1f, -1.0f, -1.0f},
	//	{0.0f, 1.0f, 0.0f},
	//	{0.1f, -1.0f, 1.0f}
	//);
	//triangle->material = &phongMat;
	
	img.clearColor(Color(0.427f, 0.537f, 0.666f, 1.0f));
	//vp.model = float4x4::identity();
	vp.model = torusTrans;
	torus->render(img);
	vp.model = torusTrans2;
	torus2->render(img);
	vp.model = float4x4::identity();
	ramiel->render(img);
	vp.model = cylTrans;
	cyl->render(img);
	vp.model = coneTrans;
	cone->render(img);
	/*vp.model = float4x4::identity();
	triangle->render(img);*/

	img.saveToFile("generated/xd.png");

	delete ramiel;
	delete cone;
	delete cyl;
	delete torus;
}