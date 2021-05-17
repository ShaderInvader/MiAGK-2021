#pragma once
#include "float4.hpp"

class float4x4
{
public:
	float4x4();
	float4x4(float initial);
	float4x4(float4 col1, float4 col2, float4 col3, float4 col4);
	static float4x4 identity();
	
	static float4x4 mul(float4x4& a, float4x4& b);
	static float4x4 mul(float v, const float4x4& a);
	static float4 mul(float4 a, float4x4& b);

	float4& operator[](int i);

	float4 getRow(int i);
	float4 getColumn(int i);
	
	void transpose();
	[[nodiscard]] std::string to_string();

private:
	float4 column[4];
};