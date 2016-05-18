#pragma once

#include "Engine/General/Core/GameEngine.hpp"
#include "Engine/Renderer/Mesh/Mesh.hpp"
#include "Engine/Renderer/Material/Material.hpp"
#include "Engine/Renderer/Mesh/MeshRenderer.hpp"
#include "Engine/Renderer/Framebuffer.hpp"
#include "Engine/SurfacePatch.hpp"
#include "Engine/Tools/FBX.hpp"
#include "Engine/Tools/FBX/SceneImport.hpp"
#include "Engine/General/Utils/StringUtils.hpp"
#include "Engine/Renderer/Animation/Animator.hpp"
#include "Game/GameCommon.hpp"
#include "Game/TheApp.hpp"
#include "Game/TheCamera.hpp"
#include "Game/Sphere.hpp"
#include "Game/MeshToRender.hpp"
#include "Game/LightSystem.hpp"
#include "Game/MaterialManager.hpp"


class TheGame;
extern TheGame* g_theGame;

class TheGame {
public:
	//STRUCTORS AND INITIALIZATION
	TheGame();
	~TheGame();

	//UPDATE
	void Update(float deltaSeconds);

	void UpdateMaterials() const;
	void ClearLights() const;

	//RENDER
	void SetUpPerspectiveProjection() const;
	void Render() const;

	//USER INPUT
	void HandlePlayerLook();
	void HandlePlayerMovement(float deltaSeconds);
	void HandlePlayerInput(float deltaSeconds);

	void SwapMeshInGame(String name);

	//OTHER
	void RegisterCommands();

	MeshToRender m_meshToRender;
public:
	bool m_isOriginEnabled;
	bool m_isSkeletonEnabled;
	bool m_isPlayingAnim;

	float m_age;

	//DEBUG
	Vector3 m_pointToDrawTo;

	std::vector<Skeleton*> m_skeletons;
	std::vector<Motion*> m_motions;
	Motion* m_currMotionBeingPlayed;

	bool m_isAnimPaused;
	float m_blendWeight;


	//FOR BLENDING
	Animator* m_animator;

	Motion* m_idleAnim;
	Motion* m_jogAnim;
	Motion* m_runAnim;

	bool m_isAnimating;

private:

};

//CONSOLE COMMANDS
void LoadSkeleton(Command& args);
void SaveSkeleton(Command& args);
void LoadMesh(Command& args);
void SaveMesh(Command& args);
void FbxLoadFromFile(Command& args);
void ShowHelp(Command& args);
void ToggleLights(Command& args);
void ToggleOrigin(Command& args);
void SwapMesh(Command& args);
void ToggleSkeleton(Command& args);

//ANIMATION
void ToggleAnim(Command& args);
void PlayAnim(Command& args);
void SetAnimMode(Command& args);

void SaveAnimation(Command& args);
void LoadAnimation(Command& args);

void LoadAnimationBlends(Command& args);