#pragma once

#if defined(TOOLS_BUILD)
	#include <fbxsdk.h>
	#pragma comment(lib, "libfbxsdk-md.lib")
#else
	class FbxNode;
#endif

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/General/Console/Command.hpp"
#include "Engine/Renderer/Mesh/MeshBuilder.hpp"
#include "Engine/Math/MatrixStack44.hpp"
#include "Engine/Math/IntVector4.hpp"
#include "Engine/Math/Vector4.hpp"
#include "Engine/Renderer/Animation/Skeleton.hpp"
#include "Engine/Renderer/Animation/Motion.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//SKIN WEIGHT STRUCT
//---------------------------------------------------------------------------------------------------------------------------
struct SkinWeight {
	SkinWeight() {}
	SkinWeight(const IntVector4& inds, const Vector4& weights) : m_inds(inds), m_weights(weights) {}

	IntVector4 m_inds;
	Vector4 m_weights;
};

//---------------------------------------------------------------------------------------------------------------------------
//SCENE IMPORT
//---------------------------------------------------------------------------------------------------------------------------
class SceneImport {
public:
	SceneImport(String filename, float scale, float fps);
	~SceneImport();

private:
	bool FbxLoadSceneFromFile(String filename, Matrix4 engineBasis, bool isEngineBasisRightHanded, Matrix4 transform = Matrix4::IDENTITY);

#if defined(TOOLS_BUILD)
	//IMPORTING
	//---------------------------------------------------------------------------------------------------------------------------
	//MESHES
	void TriangulateScene(FbxScene* scene);
	void ImportScene(FbxScene* scene, MatrixStack44& matStack);
	void ImportSceneMeshes(FbxNode* node, MatrixStack44& matStack);
	void ImportSceneAttribute(FbxNodeAttribute* attrib, MatrixStack44& matStack);
	void ImportMesh(FbxMesh* fbxMesh, MatrixStack44& matStack);
	void ImportVertex(Matrix4& transform, FbxMesh* fbxMesh, int polyIdx, int vertIdx, std::vector<SkinWeight>& weights);

	//Skinning
	bool HasSkinWeights(FbxMesh* mesh);
	void AddHighestWeight(SkinWeight* skinWeights, int jointIdx, float weight);
	int GetJointIndexForNode(FbxNode* node);
	void GetSkinWeights(std::vector<SkinWeight>& skinWeights, FbxMesh* mesh);

	//Motions
	void ImportMotions(Matrix4& importTransform, FbxScene* scene, float framerate);
	Matrix4 GetNodeWorldTransformAtTime(FbxNode* node, FbxTime time, const Matrix4& importTransform);
	//Skeleton
	void ImportSkeletons(FbxNode* node, MatrixStack44& matStack, Skeleton* skeleton, int parentJointIdx);
	Skeleton* ImportJoint(MatrixStack44& matStack, Skeleton* skeleton, int parentJointIdx, FbxSkeleton* fbxSkeleton);

	//OTHER GETTERS
	Matrix4 GetGeometricTransform(FbxNode* node);

	//DATA GETTERS
	bool GetBitangent(Vector3* outBitan, FbxMesh* mesh, int polyIdx, int vertIdx, const Matrix4& matStack);
	bool GetTangent(Vector3* outTan, FbxMesh* mesh, int polyIdx, int vertIdx, const Matrix4& matStack);
	bool GetNormal(Vector3* outNormal, FbxMesh* mesh, int polyIdx, int vertIdx, const Matrix4& matStack);
	bool GetUV(Vector2* outUV, FbxMesh* mesh, int polyIdx, int vertIdx, int uvIdx);
	bool GetColor(RGBA* outColor, FbxMesh* mesh, int polyIdx, int vertIdx);
	bool GetPosition(Vector3* outPosition, Matrix4 transform, FbxMesh* fbxMesh, int polyIdx, int vertIdx);

	//MESH UPDATE
	//void CombineMeshesAndUpdate();

	//UTILITY FUNCS
	Matrix4 GetSceneBasis(FbxScene* scene);
	Vector4 ToEngineVector4(FbxDouble4 val);
	Matrix4 ToEngineMatrix(FbxMatrix fbxMatrix);
	Matrix4 GetNodeTransform(FbxNode* node);
	void ConstructTBN(const Vector3& normal, Vector3* outTan, Vector3* outBitan);

#endif

public:
	//vector<Mesh*> m_meshes;
	//Mesh* m_mesh;
	bool m_importSuccessful;

	MeshBuilder m_meshBuilder;
	std::vector<Skeleton*> m_skeletons;
	std::vector<FbxNode*> m_fbxNodeJoints;
	std::vector<Motion*> m_motions;

	float m_fps;

	//DEBUG
	Vector3 m_pointToDraw;
	bool m_foundAPoint;
};

/*
FbxAnimStack //Number of these, can be number of motions you can import (FOR SKELLIES)
FbxAnimLayer //Collection of pointers to FbxAnimCurveNodes
FbxAnimCurveNode //
FbxAnimCurve //
FbxAnimCurveKey //

*/