#pragma once

#include "Engine/Math/Vector3.hpp"
#include "Engine/Renderer/Mesh/Mesh.hpp"
#include "Engine/General/Utils/ErrorWarningAssert.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTS
//---------------------------------------------------------------------------------------------------------------------------
struct Plane {
	Vector3 initialPosition;
	Vector3 right;
	Vector3 up;
};

//---------------------------------------------------------------------------------------------------------------------------
//SURFACE PATCH CLASS
//---------------------------------------------------------------------------------------------------------------------------
typedef Vector3(PatchFunction)(float x, float y);

namespace SurfacePatch {
	Vector3 PlaneFunc(void const *data, float x, float y);

	Mesh* MakePlane(Vector3 initialPosition, Vector3 right, Vector3 up, Vector2 start, Vector2 end, IntVector2 sectionCount);
	Mesh* MakePatch(PatchFunction* patchFunctionPtr, Vector3 initialPosition, Vector3 right, Vector3 up, Vector2 start, Vector2 end, IntVector2 sectionCount);
}

Vector3 SinSquared(float x, float y);
Vector3 MyFunc1(float x, float y);

/*
void Foo() {
	MeshBuilder mb;
	MeshBuildPatch(SinSquared, nullptr, -5.0f, 5.0f, 100, -5.0f, 5.0f, 100);
}*/