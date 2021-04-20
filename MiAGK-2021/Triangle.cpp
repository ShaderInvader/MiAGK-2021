#include "Triangle.hpp"

#include <iostream>

Triangle::Triangle()
{
	tv1.pos = v1.pos = { 0.0f, 0.0f, 0.0f };
	tv2.pos = v2.pos = { 0.0f, 0.0f, 0.0f };
	tv3.pos = v3.pos = { 0.0f, 0.0f, 0.0f };
	v1.col = { 1.0f, 1.0f, 1.0f };
	v2.col = { 1.0f, 1.0f, 1.0f };
	v3.col = { 1.0f, 1.0f, 1.0f };
}

Triangle::Triangle(float3 p1, float3 p2, float3 p3)
{
	tv1.pos = v1.pos = p1;
	tv2.pos = v2.pos = p2;
	tv3.pos = v3.pos = p3;
	v1.col = { 1.0f, 0.0f, 0.0f };
	v2.col = { 0.0f, 1.0f, 0.0f };
	v3.col = { 0.0f, 0.0f, 1.0f };
}

Triangle::Triangle(float3 p1, float3 p2, float3 p3, Color c1, Color c2, Color c3)
{
	tv1.pos = v1.pos = p1;
	tv2.pos = v2.pos = p2;
	tv3.pos = v3.pos = p3;
	v1.col = c1;
	v2.col = c2;
	v3.col = c3;
}

void Triangle::setVerts(float3 p1, float3 p2, float3 p3)
{
	v1.pos = p1;
	v2.pos = p2;
	v3.pos = p3;
}

Color Triangle::rasterize(float x, float y, float& depth)
{
	Color outputColor(0, 0, 0, 0);

	float dx12 = tv1.pos.x - tv2.pos.x;
	float dx23 = tv2.pos.x - tv3.pos.x;
	float dx31 = tv3.pos.x - tv1.pos.x;
	float dy12 = tv1.pos.y - tv2.pos.y;
	float dy23 = tv2.pos.y - tv3.pos.y;
	float dy31 = tv3.pos.y - tv1.pos.y;

	bool tl1 = (dy12 < 0.0f) || (dy12 == 0.0f && dx12 > 0.0f);
	bool tl2 = (dy23 < 0.0f) || (dy23 == 0.0f && dx23 > 0.0f);
	bool tl3 = (dy31 < 0.0f) || (dy31 == 0.0f && dx31 > 0.0f);
	
	float cond1 = dx12 * (y - tv1.pos.y) - dy12 * (x - tv1.pos.x);
	float cond2 = dx23 * (y - tv2.pos.y) - dy23 * (x - tv2.pos.x);
	float cond3 = dx31 * (y - tv3.pos.y) - dy31 * (x - tv3.pos.x);

	float lambda1 = ((tv2.pos.y - tv3.pos.y) * (x - tv3.pos.x) + (tv3.pos.x - tv2.pos.x) * (y - tv3.pos.y)) / ((tv2.pos.y - tv3.pos.y) * (tv1.pos.x - tv3.pos.x) + (tv3.pos.x - tv2.pos.x) * (tv1.pos.y - tv3.pos.y));
	float lambda2 = ((tv3.pos.y - tv1.pos.y) * (x - tv3.pos.x) + (tv1.pos.x - tv3.pos.x) * (y - tv3.pos.y)) / ((tv3.pos.y - tv1.pos.y) * (tv2.pos.x - tv3.pos.x) + (tv1.pos.x - tv3.pos.x) * (tv2.pos.y - tv3.pos.y));
	float lambda3 = 1.0f - lambda1 - lambda2;

	//if (y >= 0.5f)
	//{
	//	std::cout << "xd\n";
	//}
	
	if ( ((cond1 > 0.0f && !tl1) || (cond1 >= 0.0f && tl1)) && 
		 ((cond2 > 0.0f && !tl2) || (cond2 >= 0.0f && tl2)) &&
		 ((cond3 > 0.0f && !tl3) || (cond3 >= 0.0f && tl3)))
	{
		float triDepth = (tv1.pos.z * lambda1) + (tv2.pos.z * lambda2) + (tv3.pos.z * lambda3);
		if (triDepth < depth)
		{
			outputColor = (v1.col * lambda1) + (v2.col * lambda2) + (v3.col * lambda3);
			depth = triDepth;
		}
	}

	return outputColor;
}

void Triangle::calculateBounds(float3& min, float3& max) const
{
	min.x = std::min(std::min(tv1.pos.x, tv2.pos.x), tv3.pos.x);
	max.x = std::max(std::max(tv1.pos.x, tv2.pos.x), tv3.pos.x);
	min.y = std::min(std::min(tv1.pos.y, tv2.pos.y), tv3.pos.y);
	max.y = std::max(std::max(tv1.pos.y, tv2.pos.y), tv3.pos.y);
}
