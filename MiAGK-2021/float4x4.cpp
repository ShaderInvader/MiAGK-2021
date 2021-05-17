#include "float4x4.hpp"

float4x4::float4x4() : float4x4(0.0f)
{}

float4x4::float4x4(float initial)
{
	for (int i = 0; i < 4; ++i)
	{
		column[i] = float4(initial);
	}
}

float4x4::float4x4(float4 col1, float4 col2, float4 col3, float4 col4)
{
	column[0] = col1;
	column[1] = col2;
	column[2] = col3;
	column[3] = col4;
}

float4x4 float4x4::identity()
{
	float4x4 matrix;
	matrix[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
	matrix[1] = { 0.0f, 1.0f, 0.0f, 0.0f };
	matrix[2] = { 0.0f, 0.0f, 1.0f, 0.0f };
	matrix[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
	return matrix;
}

float4x4 float4x4::mul(float4x4& a, float4x4& b)
{
	float4x4 mat;
	for (int k = 0; k < 4; ++k)
	{
		for (int w = 0; w < 4; ++w)
		{
			mat[k][w] = float4::dot(a.getRow(w), b.getColumn(k));
		}
	}
	return mat;
}

float4x4 float4x4::mul(float v, const float4x4& a)
{
	float4x4 mat;
	for (int k = 0; k < 4; ++k)
	{
		for (int w = 0; w < 4; ++w)
		{
			mat[k][w] *= v;
		}
	}
	return mat;
}

float4 float4x4::mul(float4 a, float4x4& b)
{
	float4 vec;
	for (int k = 0; k < 4; ++k)
	{
		vec[k] = float4::dot(a, b.getRow(k));
	}
	return vec;
}

float4& float4x4::operator[](int i)
{
	return column[i];
}

float4 float4x4::getRow(int i)
{
	float4 ret = float4(column[0][i], column[1][i], column[2][i], column[3][i]);
	return ret;
}

float4 float4x4::getColumn(int i)
{
	return column[i];
}

void float4x4::transpose()
{
	float4x4 tempMat = *this;
	for (int k = 0; k < 4; ++k)
	{
		column[k] = tempMat.getRow(k);
	}
}

std::string float4x4::to_string()
{
	return	getRow(0).to_string() + "\n" +
		getRow(1).to_string() + "\n" +
		getRow(2).to_string() + "\n" +
		getRow(3).to_string() + "\n";
}