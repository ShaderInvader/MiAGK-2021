#pragma once

#include <vector>

#include "Triangle.hpp"

class Mesh
{
public:
	Mesh() = default;
	
private:
	std::vector<Triangle> triangles;
};
