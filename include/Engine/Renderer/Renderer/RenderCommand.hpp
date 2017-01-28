#pragma once

#include "Engine/Renderer/Material/Shaders/ShaderProgram.hpp"

enum eDrawType {
	DEBUG_DRAW_DEPTH_TEST_ON = 0,
	DEBUG_DRAW_DEPTH_TEST_OFF,
	DEBUG_DRAW_DEPTH_TEST_DUAL
};

class RenderCommand {
public:
	//STRUCTORS
	RenderCommand(std::vector<Vertex> verts, ePrimitiveType pType, eDrawType dType, float durSeconds, ShaderProgram shaderProgram);

public:
	std::vector<Vertex> m_verts;
	ePrimitiveType m_primitiveType;
	eDrawType m_drawType;
	float m_durationSeconds;
	float m_age;
	int m_frameCount;
	ShaderProgram m_programToUse;
};