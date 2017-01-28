#pragma once

#include "Engine/Math/Matrix4.hpp"
#include <vector>

class MatrixStack44 {
public:
	MatrixStack44();

	bool Empty();
	Matrix4 Top();

	void Push(const Matrix4& transform);
	void Pop();

public:
	std::vector<Matrix4> m_stack;
};