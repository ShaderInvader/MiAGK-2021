#include "Triangle.hpp"

Triangle::Triangle()
{
	p1 = { 0.0f, 0.0f, 0.0f };
	p2 = { 0.0f, 0.0f, 0.0f };
	p3 = { 0.0f, 0.0f, 0.0f };
	calculateBounds();
}

Triangle::Triangle(float3 p1, float3 p2, float3 p3)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	calculateBounds();
}

void Triangle::setVerts(float3 p1, float3 p2, float3 p3)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	calculateBounds();
}

float Triangle::rasterize(float x, float y)
{
	float value = 0.0f;
	bool cond1 = (p1.x - p2.x) * (y - p1.y) - (p1.y - p2.y) * (x - p1.x) > 0.0f;
	bool cond2 = (p2.x - p3.x) * (y - p2.y) - (p2.y - p3.y) * (x - p2.x) > 0.0f;
	bool cond3 = (p3.x - p1.x) * (y - p3.y) - (p3.y - p1.y) * (x - p3.x) > 0.0f;
	
	if ( cond1 && cond2 && cond3 )
	{
		value = 1.0f;
	}

	return value;
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
