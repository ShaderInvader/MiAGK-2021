#pragma once
#include "float4.hpp"

class float4x4
{
public:
	float4x4();
	float4x4(float initial);
	static float4x4 identity();
	
	static float4x4 mul(float4x4& a, float4x4& b);
	static float4x4 mul(float v, const float4x4& a);

	float4& operator[](int i);

	float4 getRow(int i);
	float4 getColumn(int i);
	
	void transpose();
	[[nodiscard]] std::string to_string() const;

private:
	float4 column[4];
};