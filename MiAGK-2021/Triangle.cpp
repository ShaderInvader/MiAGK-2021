#include "Triangle.hpp"

Triangle::Triangle()
{
	p1 = { 0.0f, 0.0f, 0.0f };
	p2 = { 0.0f, 0.0f, 0.0f };
	p3 = { 0.0f, 0.0f, 0.0f };
	c1 = { 1.0f, 1.0f, 1.0f };
	c2 = { 1.0f, 1.0f, 1.0f };
	c3 = { 1.0f, 1.0f, 1.0f };
	calculateBounds();
}

Triangle::Triangle(float3 p1, float3 p2, float3 p3)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	c1 = { 1.0f, 1.0f, 1.0f };
	c2 = { 1.0f, 1.0f, 1.0f };
	c3 = { 1.0f, 1.0f, 1.0f };
	calculateBounds();
}

Triangle::Triangle(float3 p1, float3 p2, float3 p3, Color c1, Color c2, Color c3)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->c1 = c1;
	this->c2 = c2;
	this->c3 = c3;
	calculateBounds();
}

void Triangle::setVerts(float3 p1, float3 p2, float3 p3)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	calculateBounds();
}

Color Triangle::rasterize(float x, float y, float& depth)
{
	Color outputColor(0, 0, 0, 0);

	float dx12 = p1.x - p2.x;
	float dx23 = p2.x - p3.x;
	float dx31 = p3.x - p1.x;
	float dy12 = p1.y - p2.y;
	float dy23 = p2.y - p3.y;
	float dy31 = p3.y - p1.y;

	bool tl1 = (dy12 < 0.0f) || (dy12 == 0.0f && dx12 > 0.0f);
	bool tl2 = (dy23 < 0.0f) || (dy23 == 0.0f && dx23 > 0.0f);
	bool tl3 = (dy31 < 0.0f) || (dy31 == 0.0f && dx31 > 0.0f);
	
	float cond1 = dx12 * (y - p1.y) - dy12 * (x - p1.x);
	float cond2 = dx23 * (y - p2.y) - dy23 * (x - p2.x);
	float cond3 = dx31 * (y - p3.y) - dy31 * (x - p3.x);

	float lambda1 = ((p2.y - p3.y) * (x - p3.x) + (p3.x - p2.x) * (y - p3.y)) / ((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y));
	float lambda2 = ((p3.y - p1.y) * (x - p3.x) + (p1.x - p3.x) * (y - p3.y)) / ((p3.y - p1.y) * (p2.x - p3.x) + (p1.x - p3.x) * (p2.y - p3.y));
	float lambda3 = 1.0f - lambda1 - lambda2;
	
	if ( ((cond1 > 0.0f && !tl1) || (cond1 >= 0.0f && tl1)) && 
		 ((cond2 > 0.0f && !tl2) || (cond2 >= 0.0f && tl2)) &&
		 ((cond3 > 0.0f && !tl3) || (cond3 >= 0.0f && tl3)))
	{
		float triDepth = (p1.z * lambda1) + (p2.z * lambda2) + (p3.z * lambda3);
		if (triDepth < depth)
		{
			outputColor = (c1 * lambda1) + (c2 * lambda2) + (c3 * lambda3);
			depth = triDepth;
		}
	}

	return outputColor;
}

float3 Triangle::getMinBounds()
{
	return min;
}

float3 Triangle::getMaxBounds()
{
	return max;
}

void Triangle::calculateBounds()
{
	min.x = getMin(getMin(p1.x, p2.x), p3.x);
	max.x = getMax(getMax(p1.x, p2.x), p3.x);
	min.y = getMin(getMin(p1.y, p2.y), p3.y);
	max.y = getMax(getMax(p1.y, p2.y), p3.y);
}

float Triangle::getMin(float x, float y)
{
	if (x < y)
	{
		return x;
	}
	return y;
}

float Triangle::getMax(float x, float y)
{
	if (x > y)
	{
		return x;
	}
	return y;
}
