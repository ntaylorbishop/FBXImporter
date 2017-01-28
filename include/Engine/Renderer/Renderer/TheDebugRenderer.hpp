#pragma once

#define _USE_MATH_DEFINES

#include <list>
#include "Engine/Renderer/Renderer/TheRenderer.hpp"
#include "Engine/General/Utils/TheLogger.hpp"

class TheDebugRenderer;
extern TheDebugRenderer* g_theDebugRenderer;

enum eDrawType {
	DEBUG_DRAW_DEPTH_TEST_ON = 0,
	DEBUG_DRAW_DEPTH_TEST_OFF,
	DEBUG_DRAW_DEPTH_TEST_DUAL
};

//---------------------------------------------------------------------------------------------------------------------------
//RENDER COMMAND
//---------------------------------------------------------------------------------------------------------------------------
struct RenderCommand {
	//STRUCTORS
	RenderCommand(std::vector<Vertex> verts, ePrimitiveType pType, eDrawType dType, float durSeconds)
		: m_verts(verts)
		, m_primitiveType(pType)
		, m_drawType(dType)
		, m_durationSeconds(durSeconds)
		, m_age(0.f)
		, m_frameCount(0)
	{
		if (durSeconds == 0) {
			m_frameCount = 0;
		}
		else {
			m_frameCount = -1;
		}
	}

	//DATA MEMBERS
	std::vector<Vertex> m_verts;
	ePrimitiveType m_primitiveType;
	eDrawType m_drawType;
	float m_durationSeconds;
	float m_age;
	int m_frameCount;
};

//---------------------------------------------------------------------------------------------------------------------------
//DEBUG RENDERER
//---------------------------------------------------------------------------------------------------------------------------
class TheDebugRenderer {
public:
	//STRUCTORS
	TheDebugRenderer();
	~TheDebugRenderer();

	//UPDATE RENDER
	void Update(float deltaSeconds);
	void Render() const;

	//DEBUG DRAWING
	void DrawDebugPoint(const Vector3& position,                  const RGBA& color, eDrawType drawType, float durationSeconds = 0);
	void DrawDebugLine(const Vector3& start,  const Vector3& end, const RGBA& color, eDrawType drawType, float durationSeconds = 0);
	void DrawDebugArrow(const Vector3& start, const Vector3& end, const RGBA& color, eDrawType drawType, float durationSeconds = 0);
	void DrawDebugAABB3(const AABB3& box,                         const RGBA& wireFrameColor, const RGBA& faceColor, eDrawType drawType, float durationSeconds = 0);
	void DrawDebugSphere(const Vector3& position, float radius,   const RGBA& color, eDrawType drawType, float durationSeconds = 0);
	void DrawDebugAxis(const Vector3& position, float length,                        eDrawType drawType, float durationSeconds = 0);

	void ClearDebugPoints();

private:
	void DrawRenderCommand(std::list<RenderCommand*>::const_iterator renderCommand) const;

private:
	std::list<RenderCommand*> m_renderCommands;
};