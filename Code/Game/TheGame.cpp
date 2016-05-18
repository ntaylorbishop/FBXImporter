#include "Game/TheGame.hpp"

TheGame* g_theGame = nullptr;

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS AND INITIALIZATION
//---------------------------------------------------------------------------------------------------------------------------
TheGame::TheGame()
	: m_isOriginEnabled(true)
	, m_isSkeletonEnabled(true)
	, m_currMotionBeingPlayed(nullptr)
	, m_age(0.f)
	, m_isPlayingAnim(false)
	, m_blendWeight(0.f)
	, m_animator(nullptr)
{
	g_theCamera = new TheCamera(Vector3(0.f, -5.f, 3.f), 0.f, 0.f, 0.f);
	g_theApparatusEngine->BindKeyToConsole(VK_F1);

	g_theLightSystem = new LightSystem();

	RegisterCommands();

	m_meshToRender = MeshToRender(Vector3(0.f, 0.f, 0.f));

	m_pointToDrawTo = Vector3(0.f, 0.f, 10.f);

	m_isAnimPaused = false;
	m_animator = new Animator(PLAYBACK_LOOP);
	m_isAnimating = false;
}
TheGame::~TheGame() {
	delete g_theLightSystem;
	g_theLightSystem = nullptr;
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE RENDER
//---------------------------------------------------------------------------------------------------------------------------
void TheGame::Update(float deltaSeconds) {

	if (!m_isAnimPaused) {
		m_age += deltaSeconds;
	}
	if (g_theInputSystem->GetKeyDown(VK_F4)) {
		m_isAnimPaused = !m_isAnimPaused;
	}

	g_theCamera->Update(deltaSeconds);

	if (g_theApp->HasFocus()) {
		HandlePlayerLook();
		HandlePlayerMovement(deltaSeconds);
		HandlePlayerInput(deltaSeconds);
	}


	g_theLightSystem->Update(deltaSeconds);
	
	if (m_isOriginEnabled) {
		g_theDebugRenderer->DrawDebugAxis(Vector3::ZERO, 10.f, DEBUG_DRAW_DEPTH_TEST_ON);
	}

	m_meshToRender.Update(deltaSeconds);

	if (m_isAnimating) {
		m_animator->ApplyMotionToSkeleton(m_skeletons[0], deltaSeconds, m_blendWeight);
	}
}

void TheGame::UpdateMaterials() const {
	std::vector<Light3D> lights = g_theLightSystem->GetLights();
	int lightCount = lights.size();

	Material* brick = g_theMaterialManager->GetMaterial("Brick");
	
	Uniform_INT* gLightCount = static_cast<Uniform_INT*>(brick->GetUniform("gLightCount"));
	Uniform_VECTOR3* gCameraPosition = static_cast<Uniform_VECTOR3*>(brick->GetUniform("gCameraPosition"));
	Uniform_MAT4* gView = static_cast<Uniform_MAT4*>(brick->GetUniform("gView"));
	Uniform_MAT4* gProj = static_cast<Uniform_MAT4*>(brick->GetUniform("gProj"));
	Uniform_RGBA* gAmbientLight = static_cast<Uniform_RGBA*>(brick->GetUniform("gAmbientLight"));

	gLightCount->SetData(lightCount);
	gCameraPosition->SetData(g_theCamera->m_position);
	gView->SetData(g_theRenderer->GetViewMatrix());
	gProj->SetData(g_theRenderer->GetProjectionMatrix());
	gAmbientLight->SetData(LIGHTS_AMBIENT_LIGHT);
	
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightCount);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gCameraPosition);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gView);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gProj);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gAmbientLight);

	Uniform_VECTOR3* gLightPosition = static_cast<Uniform_VECTOR3*>(brick->GetUniform("gLightPosition"));
	Uniform_VECTOR3* gLightDirection = static_cast<Uniform_VECTOR3*>(brick->GetUniform("gLightDirection"));
	Uniform_RGBA* gLightColor = static_cast<Uniform_RGBA*>(brick->GetUniform("gLightColor"));
	Uniform_FLOAT* gMinLightDistance = static_cast<Uniform_FLOAT*>(brick->GetUniform("gMinLightDistance"));
	Uniform_FLOAT* gMaxLightDistance = static_cast<Uniform_FLOAT*>(brick->GetUniform("gMaxLightDistance"));
	Uniform_FLOAT* gMinLightPower = static_cast<Uniform_FLOAT*>(brick->GetUniform("gMinLightPower"));
	Uniform_FLOAT* gMaxLightPower = static_cast<Uniform_FLOAT*>(brick->GetUniform("gMaxLightPower"));
	Uniform_FLOAT* gInterpolateAttenuation = static_cast<Uniform_FLOAT*>(brick->GetUniform("gInterpolateAttenuation"));
	Uniform_FLOAT* gThetaInner = static_cast<Uniform_FLOAT*>(brick->GetUniform("gThetaInner"));
	Uniform_FLOAT* gThetaOuter = static_cast<Uniform_FLOAT*>(brick->GetUniform("gThetaOuter"));
	Uniform_FLOAT* gLightInsidePower = static_cast<Uniform_FLOAT*>(brick->GetUniform("gLightInsidePower"));
	Uniform_FLOAT* gLightOutsidePower = static_cast<Uniform_FLOAT*>(brick->GetUniform("gLightOutsidePower"));

	std::vector<Vector3> lightPositions;
	std::vector<Vector3> lightDirections;
	std::vector<RGBA> lightColors;
	std::vector<float> minLightDists;
	std::vector<float> maxLightDists;
	std::vector<float> minLightPowers;
	std::vector<float> maxLightPowers;
	std::vector<float> dirInterps;
	std::vector<float> thetaInners;
	std::vector<float> thetaOuters;
	std::vector<float> lightInsidePowers;
	std::vector<float> lightOutsidePowers;

	for (int i = 0; i < lightCount; i++) {
		lightPositions.push_back(lights[i].GetPosition());
		lightDirections.push_back(lights[i].GetDirection());
		lightColors.push_back(lights[i].GetColor());
		minLightDists.push_back(lights[i].GetMinLightDistance());
		maxLightDists.push_back(lights[i].GetMaxLightDistance());
		minLightPowers.push_back(lights[i].GetPowerAtMin());
		maxLightPowers.push_back(lights[i].GetPowerAtMax());
		dirInterps.push_back(lights[i].GetIsDirectionInterpolated());
		thetaInners.push_back(lights[i].GetInnerTheta());
		thetaOuters.push_back(lights[i].GetOuterTheta());
		lightInsidePowers.push_back(lights[i].GetThetaInnerPower());
		lightOutsidePowers.push_back(lights[i].GetThetaOuterPower());
	}
		

	gLightPosition->SetData(lightPositions);
	gLightDirection->SetData(lightDirections);
	gLightColor->SetData(lightColors);
	gMinLightDistance->SetData(minLightDists);
	gMaxLightDistance->SetData(maxLightDists);
	gMinLightPower->SetData(minLightPowers);
	gMaxLightPower->SetData(maxLightPowers);
	gInterpolateAttenuation->SetData(dirInterps);
	gThetaInner->SetData(thetaInners);
	gThetaOuter->SetData(thetaOuters);
	gLightInsidePower->SetData(lightInsidePowers);
	gLightOutsidePower->SetData(lightOutsidePowers);

	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightPosition);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightDirection);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightColor);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gMinLightDistance);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gMaxLightDistance);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gMinLightPower);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gMaxLightPower);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gInterpolateAttenuation);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gThetaInner);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gThetaOuter);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightInsidePower);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightOutsidePower);


	//BONE MATRICES
	if (m_skeletons.size() > 0) {
		Uniform_MAT4* gBoneMatrices = static_cast<Uniform_MAT4*>(brick->GetUniform("gBoneMatrices"));

		std::vector<Matrix4> mats;
		for (unsigned int i = 0; i < m_skeletons[0]->m_boneToModelSpace.size(); i++) {
			Matrix4 mat = m_skeletons[0]->m_modelToBoneSpace[i] * m_skeletons[0]->m_boneToModelSpace[i];

			mats.push_back(mat);
		}

		gBoneMatrices->SetData(mats);

		g_theMaterialManager->UpdateUniformOnMaterial("Brick", gBoneMatrices);
	}
	else {
		Uniform_MAT4* boneMatrices = static_cast<Uniform_MAT4*>(brick->GetUniform("gBoneMatrices"));

		g_theMaterialManager->UpdateUniformOnMaterial("Brick", boneMatrices);
	}
}
void TheGame::ClearLights() const {
	Material* brick = g_theMaterialManager->GetMaterial("Brick");

	Uniform_INT* gLightCount = static_cast<Uniform_INT*>(brick->GetUniform("gLightCount"));
	Uniform_VECTOR3* gCameraPosition = static_cast<Uniform_VECTOR3*>(brick->GetUniform("gCameraPosition"));
	Uniform_MAT4* gView = static_cast<Uniform_MAT4*>(brick->GetUniform("gView"));
	Uniform_MAT4* gProj = static_cast<Uniform_MAT4*>(brick->GetUniform("gProj"));
	Uniform_RGBA* gAmbientLight = static_cast<Uniform_RGBA*>(brick->GetUniform("gAmbientLight"));

	gLightCount->SetData(0);
	gCameraPosition->SetData(g_theCamera->m_position);
	gView->SetData(g_theRenderer->GetViewMatrix());
	gProj->SetData(g_theRenderer->GetProjectionMatrix());
	gAmbientLight->SetData(LIGHTS_AMBIENT_LIGHT);

	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gLightCount);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gCameraPosition);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gView);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gProj);
	g_theMaterialManager->UpdateUniformOnMaterial("Brick", gAmbientLight);
}

//---------------------------------------------------------------------------------------------------------------------------
//RENDER
//---------------------------------------------------------------------------------------------------------------------------
void TheGame::SetUpPerspectiveProjection() const {
	float aspect = 16.f / 9.f;
	float fovDegreesVertical = 90.f;
	float nearClippingPlane = 0.1f;
	float farClippingPlane = 100.f;

	g_theRenderer->SetPerspective(fovDegreesVertical, aspect, nearClippingPlane, farClippingPlane);

	g_theRenderer->EnableDepthTesting();
	g_theRenderer->EnableBackfaceCulling();
	g_theRenderer->EnableAlphaTesting();

	//NEW WAY
	Vector3 cameraRotation = Vector3(g_theCamera->m_pitchAboutX, g_theCamera->m_rollAboutY, g_theCamera->m_yawAboutZ);
	g_theRenderer->SetCamera3D(Vector3(cameraRotation), g_theCamera->m_position);

	//OLD WAY
	g_theRenderer->RotateViewMatrix(-90.f, Vector3(1.f, 0.f, 0.f)); //Put z up
	g_theRenderer->RotateViewMatrix(-g_theCamera->m_rollAboutY, Vector3(1.f, 0.f, 0.f));
	g_theRenderer->RotateViewMatrix(-g_theCamera->m_pitchAboutX, Vector3(0.f, 1.f, 0.f));
	g_theRenderer->RotateViewMatrix(g_theCamera->m_yawAboutZ, Vector3(0.f, 0.f, 1.f));
	g_theRenderer->TranslateViewMatrix(Vector3(-g_theCamera->m_position.x, -g_theCamera->m_position.y, -g_theCamera->m_position.z));
}
void TheGame::Render() const {

	//Render 3D
	SetUpPerspectiveProjection();

	if (g_theLightSystem->AreLightsEnabled()) {
		UpdateMaterials();
	}
	else {
		ClearLights();
	}

	g_theLightSystem->Render();

	m_meshToRender.Render();

	g_theRenderer->DrawLine(Vector3::ZERO, m_pointToDrawTo, RGBA::MAGENTA);

	if (m_isSkeletonEnabled) {
		for (unsigned int i = 0; i < m_skeletons.size(); i++) {
			m_skeletons[i]->Visualize();
		}
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//USER INPUT
//---------------------------------------------------------------------------------------------------------------------------
void TheGame::HandlePlayerLook() {
	IntVector2 cursorDelta = g_theApp->GetCursorDelta();
	g_theInputSystem->HideMouseCursor();

	if (g_theCamera->m_rollAboutY <= 89.f && cursorDelta.y < 0.f) {
		g_theCamera->m_rollAboutY -= (float)cursorDelta.y * MOUSE_SENSITIVITY;
	}
	else if(g_theCamera->m_rollAboutY >= -89.f && cursorDelta.y > 0.f) {
		g_theCamera->m_rollAboutY -= (float)cursorDelta.y * MOUSE_SENSITIVITY;
	}

	g_theCamera->m_yawAboutZ += (float)cursorDelta.x * MOUSE_SENSITIVITY;
}
void TheGame::HandlePlayerMovement(float deltaSeconds) {
	float moveSpeed = PLAYER_MOVE_SPEED * deltaSeconds;

	//g_theDebugRenderer->DrawDebugSphere(Vector3(10.f, 10.f, 0.f), 2.f, RGBA::WHITE, DEBUG_DRAW_DEPTH_TEST_DUAL);

	//FORWARD BACKWARD
	if (g_theInputSystem->GetKey('D')) {
		g_theCamera->m_position += g_theCamera->GetForwardXY() * moveSpeed; //Forward
	}
	else if (g_theInputSystem->GetKey('A')) {
		g_theCamera->m_position += g_theCamera->GetForwardXY() * -moveSpeed; //Backward
	}
	//LEFT RIGHT
	if (g_theInputSystem->GetKey('W')) {
		g_theCamera->m_position += g_theCamera->GetLeftXY() * moveSpeed; //Left
	}
	else if (g_theInputSystem->GetKey('S')) {
		g_theCamera->m_position += g_theCamera->GetLeftXY() * -moveSpeed; //Right
	}

	//UP DOWN
	if (g_theInputSystem->GetKey(VK_SPACE)) {
		g_theCamera->m_position += Vector3(0.f, 0.f, moveSpeed); //Up
	}
	else if (g_theInputSystem->GetKey('C')) {
		g_theCamera->m_position += Vector3(0.f, 0.f, -moveSpeed); //Down
	}
}
void TheGame::HandlePlayerInput(float deltaSeconds) {
	if (g_theInputSystem->GetKeyDown('7')) {
		Material* mat = g_theMaterialManager->GetMaterial("Brick");

		Uniform_INT* gWhatToRender = static_cast<Uniform_INT*>(mat->GetUniform("gWhatToRender"));
		gWhatToRender->SetData(0);
		mat->UpdateUniform(gWhatToRender);
	}
	if (g_theInputSystem->GetKeyDown('8')) {
		Material* mat = g_theMaterialManager->GetMaterial("Brick");

		Uniform_INT* gWhatToRender = static_cast<Uniform_INT*>(mat->GetUniform("gWhatToRender"));
		gWhatToRender->SetData(1);
		mat->UpdateUniform(gWhatToRender);
	}
	else if (g_theInputSystem->GetKeyDown('9')) {
		Material* mat = g_theMaterialManager->GetMaterial("Brick");

		Uniform_INT* gWhatToRender = static_cast<Uniform_INT*>(mat->GetUniform("gWhatToRender"));
		gWhatToRender->SetData(2);
		mat->UpdateUniform(gWhatToRender);
	}
	else if (g_theInputSystem->GetKeyDown('0')) {
		Material* mat = g_theMaterialManager->GetMaterial("Brick");

		Uniform_INT* gWhatToRender = static_cast<Uniform_INT*>(mat->GetUniform("gWhatToRender"));
		gWhatToRender->SetData(3);
		mat->UpdateUniform(gWhatToRender);
	}

	//BLEND WEIGHTS
	if (g_theInputSystem->GetKey(VK_LEFT)) {
		if(m_blendWeight >= 0.f)
			m_blendWeight -= 10.f * deltaSeconds;
	}
	else if (g_theInputSystem->GetKey(VK_RIGHT)) {
		if (m_blendWeight <= 40.f) 
			m_blendWeight += 10.f * deltaSeconds;
	}

	if (m_blendWeight < 0.f)
		m_blendWeight = 0.f;
	else if (m_blendWeight > 40.f)
		m_blendWeight = 40.f;
}

void TheGame::SwapMeshInGame(String name) {
	if (name == "patch1") {
		m_meshToRender.m_mesh = SurfacePatch::MakePatch(MyFunc1, Vector3(0.f, 0.f, 0.f), Vector3::RIGHT, Vector3(0.f, 1.f, 0.f), Vector2(0.f, 0.f), Vector2(10.f, 10.f), IntVector2(200, 200));
	}
	else if (name == "patch2") {
		m_meshToRender.m_mesh = SurfacePatch::MakePatch(SinSquared, Vector3(0.f, 0.f, 0.f), Vector3::RIGHT, Vector3(0.f, 1.f, 0.f), Vector2(0.f, 0.f), Vector2(10.f, 10.f), IntVector2(200, 200));
	}
	if (name == "cube") {
		m_meshToRender.SwapToCubeMesh();
	}
}

//---------------------------------------------------------------------------------------------------------------------------
//CONSOLE SETUP
//---------------------------------------------------------------------------------------------------------------------------
void TheGame::RegisterCommands() {
	g_theApparatusEngine->RegisterCommandToConsole("loadmesh", LoadMesh);
	g_theApparatusEngine->RegisterCommandToConsole("savemesh", SaveMesh);
	g_theApparatusEngine->RegisterCommandToConsole("help", ShowHelp);
	g_theApparatusEngine->RegisterCommandToConsole("lights", ToggleLights);
	g_theApparatusEngine->RegisterCommandToConsole("origin", ToggleOrigin);
	g_theApparatusEngine->RegisterCommandToConsole("swapmesh", SwapMesh);
	g_theApparatusEngine->RegisterCommandToConsole("fbxload", FbxLoadFromFile);
	g_theApparatusEngine->RegisterCommandToConsole("skeleton", ToggleSkeleton);
	g_theApparatusEngine->RegisterCommandToConsole("loadskeleton", LoadSkeleton);
	g_theApparatusEngine->RegisterCommandToConsole("saveskeleton", SaveSkeleton);

	g_theApparatusEngine->RegisterCommandToConsole("animtoggle", ToggleAnim);
	g_theApparatusEngine->RegisterCommandToConsole("playanim", PlayAnim);
	g_theApparatusEngine->RegisterCommandToConsole("animmode", SetAnimMode);
	g_theApparatusEngine->RegisterCommandToConsole("animsave", SaveAnimation);
	g_theApparatusEngine->RegisterCommandToConsole("animload", LoadAnimation);
	g_theApparatusEngine->RegisterCommandToConsole("animblend", LoadAnimationBlends);
}

//---------------------------------------------------------------------------------------------------------------------------
//COMMANDS
//---------------------------------------------------------------------------------------------------------------------------
void LoadSkeleton(Command& args) {
	String filename;

	args.GetNextString(filename);

	g_theGame->m_skeletons.clear();
	g_theGame->m_skeletons.push_back(Skeleton::ReadSkeletonFromFile("Data/Mesh/" + filename + ".skeleton"));
	g_theApparatusEngine->PrintOutputToConsole("Loaded skeleton successfully.", CONSOLE_VERIFY);
}
void SaveSkeleton(Command& args) {
	String filename;

	args.GetNextString(filename);

	Skeleton* skeletonToSave = nullptr;
	if (g_theGame->m_skeletons.size() > 0) {
		skeletonToSave = g_theGame->m_skeletons[0];
	}
	else {
		g_theApparatusEngine->PrintOutputToConsole("ERROR: No skeleton to save.", CONSOLE_WARNING);
	}

	if (skeletonToSave) {
		Skeleton::WriteSkeletonToFile(skeletonToSave, "Data/Mesh/" + filename + ".skeleton");
	}
}
void LoadMesh(Command& args) {
	String filename;

	args.GetNextString(filename);

	if (nullptr != g_theGame->m_meshToRender.m_mesh) {
		delete g_theGame->m_meshToRender.m_mesh;
		g_theGame->m_meshToRender.m_mesh = nullptr;
	}
	g_theGame->m_meshToRender.m_mesh = MeshBuilder::ReadMeshFromFile(g_theGame->m_meshToRender.m_mesh, "Data/Mesh/", filename + ".mesh");

	g_theApparatusEngine->PrintOutputToConsole("Mesh loaded successfully.", CONSOLE_VERIFY);
}
void SaveMesh(Command& args) {
	String filename;

	args.GetNextString(filename);

	MeshBuilder::WriteMeshToFile(g_theGame->m_meshToRender.m_mesh, "Data/Mesh/", filename + ".mesh");

	g_theApparatusEngine->PrintOutputToConsole("Mesh saved successfully.", CONSOLE_VERIFY);
}
void FbxLoadFromFile(Command& args) {
	String fbxName;
	String filename;
	float scale = 1.f;
	float fps = 30.f;

	args.GetNextString(fbxName);
	args.GetNextFloat(scale);
	args.GetNextFloat(fps);

	filename = "Data/FBX/" + fbxName + ".fbx";

	if (filename.empty()) {
		return;
	}
	
	SceneImport* import = new SceneImport(filename, scale, fps);

	if (!import->m_importSuccessful) {
		g_theApparatusEngine->PrintOutputToConsole("ERROR: Failed to load file.", CONSOLE_WARNING);
	}
	else {
		int meshSize = import->m_meshBuilder.GetNumMeshes(); // import->m_meshes.size();
		String str = StringUtils::Stringf("Loaded %s. Had %i meshes.", filename.c_str(), meshSize);
		g_theApparatusEngine->PrintOutputToConsole(str, CONSOLE_VERIFY);

		g_theGame->m_meshToRender.m_mesh = import->m_meshBuilder.GetMasterMesh();
		//g_theGame->m_meshToRender.m_mesh = import->m_mesh;

		g_theGame->m_pointToDrawTo = import->m_pointToDraw;
		g_theGame->m_skeletons = import->m_skeletons;
		g_theGame->m_motions = import->m_motions;
		g_theGame->m_currMotionBeingPlayed = import->m_motions[0];
		g_theGame->m_age = 0.f;
	}
}
void ShowHelp(Command& args) {
	UNREFERENCED_PARAMETER(args);
	String arg0;

	g_theApparatusEngine->PrintOutputToConsole("\"help\": Prints this prompt", CONSOLE_WARNING);
	g_theApparatusEngine->PrintOutputToConsole("\"clear\": Clears the console window", CONSOLE_WARNING);
	g_theApparatusEngine->PrintOutputToConsole("\"quit\": Quits the application", CONSOLE_WARNING);
	g_theApparatusEngine->PrintOutputToConsole("\"lights <enable> <disable>\": Enables or disables the light system", CONSOLE_WARNING);
	g_theApparatusEngine->PrintOutputToConsole("\"origin <enable> <disable>\": Enables or disables debug origin drawing", CONSOLE_WARNING);
}
void ToggleLights(Command& args) {
	String arg0;

	args.GetNextString(arg0);

	if (arg0 == "enable") {
		g_theLightSystem->SetIsLightEnabled(true);
		String strToPrint = StringUtils::Stringf("Lights are now enabled");
		g_theApparatusEngine->PrintOutputToConsole(strToPrint, CONSOLE_VERIFY);
	}
	else if (arg0 == "disable") {
		g_theLightSystem->SetIsLightEnabled(false);
		String strToPrint = StringUtils::Stringf("Lights are now disabled");
		g_theApparatusEngine->PrintOutputToConsole(strToPrint, CONSOLE_VERIFY);
	}
}
void ToggleOrigin(Command& args) {
	String arg0;

	args.GetNextString(arg0);

	if (arg0 == "enable") {
		g_theGame->m_isOriginEnabled = true;
		String strToPrint = StringUtils::Stringf("Origin is now enabled");
		g_theApparatusEngine->PrintOutputToConsole(strToPrint, CONSOLE_VERIFY);
	}
	else if (arg0 == "disable") {
		g_theGame->m_isOriginEnabled = false;
		String strToPrint = StringUtils::Stringf("Origin is now disabled");
		g_theApparatusEngine->PrintOutputToConsole(strToPrint, CONSOLE_VERIFY);
	}
}

void ToggleSkeleton(Command& args) {
	String arg0;

	args.GetNextString(arg0);

	if (arg0 == "enable") {
		g_theGame->m_isSkeletonEnabled = true;
		g_theApparatusEngine->PrintOutputToConsole("Skeleton is now enabled", CONSOLE_VERIFY);
	}
	else if (arg0 == "disable") {
		g_theGame->m_isSkeletonEnabled = false;
		g_theApparatusEngine->PrintOutputToConsole("Skeleton is now disabled", CONSOLE_VERIFY);
	}
}

void SwapMesh(Command& args) {
	String arg0;

	args.GetNextString(arg0);

	g_theGame->SwapMeshInGame(arg0);
}

//---------------------------------------------------------------------------------------------------------------------------
//ANIMATIONS
//---------------------------------------------------------------------------------------------------------------------------
void ToggleAnim(Command& args) {

	if (g_theGame->m_currMotionBeingPlayed == nullptr) {
		g_theApparatusEngine->PrintOutputToConsole("ERROR: No motion to toggle.", CONSOLE_WARNING);
	}

	g_theGame->m_isPlayingAnim = !g_theGame->m_isPlayingAnim;

	if (g_theGame->m_isPlayingAnim) {
		g_theApparatusEngine->PrintOutputToConsole("Playing animation.", CONSOLE_WARNING);
	}
	else {
		g_theApparatusEngine->PrintOutputToConsole("Pausing animation.", CONSOLE_WARNING);
	}
}
void PlayAnim(Command& args) {
	g_theGame->m_age = 0.f;
	g_theApparatusEngine->PrintOutputToConsole("Playing animation.", CONSOLE_WARNING);
}
void SetAnimMode(Command& args) {
	String mode;

	args.GetNextString(mode);

	if (mode == "clamp") {
		g_theGame->m_age = 0.f;
		g_theGame->m_currMotionBeingPlayed->SetPlaybackType(PLAYBACK_CLAMP);
		g_theApparatusEngine->PrintOutputToConsole("Setting anim mode to clamp and playing once.", CONSOLE_WARNING);
	}
	else if (mode == "loop") {
		g_theGame->m_currMotionBeingPlayed->SetPlaybackType(PLAYBACK_LOOP);
		g_theApparatusEngine->PrintOutputToConsole("Setting anim mode to loop.", CONSOLE_WARNING);
	}
	else if (mode == "pingpong") {
		g_theGame->m_currMotionBeingPlayed->SetPlaybackType(PLAYBACK_PINGPONG);
		g_theApparatusEngine->PrintOutputToConsole("Setting anim mode to ping pong.", CONSOLE_WARNING);
	}
	else {
		g_theApparatusEngine->PrintOutputToConsole("Unrecognized playback mode.", CONSOLE_WARNING);
	}
}

void LoadAnimation(Command& args) {
	String filename;

	args.GetNextString(filename);

	if (nullptr != g_theGame->m_currMotionBeingPlayed) {
		delete g_theGame->m_currMotionBeingPlayed;
		g_theGame->m_currMotionBeingPlayed = nullptr;
	}

	g_theGame->m_currMotionBeingPlayed = Motion::ReadAnimFromFile("Data/Mesh/" + filename + ".anim");

	g_theApparatusEngine->PrintOutputToConsole("Mesh loaded successfully.", CONSOLE_VERIFY);
}
void SaveAnimation(Command& args) {
	String filename;

	args.GetNextString(filename);

	Motion::WriteAnimToFile(g_theGame->m_currMotionBeingPlayed, "Data/Mesh/" + filename + ".anim");

	g_theApparatusEngine->PrintOutputToConsole("Animation saved successfully.", CONSOLE_VERIFY);
}

void LoadAnimationBlends(Command& args) {

	g_theGame->m_skeletons.clear();
	g_theGame->m_skeletons.push_back(Skeleton::ReadSkeletonFromFile("Data/Mesh/u1.skeleton"));


	if (nullptr != g_theGame->m_meshToRender.m_mesh) {
		delete g_theGame->m_meshToRender.m_mesh;
		g_theGame->m_meshToRender.m_mesh = nullptr;
	}
	g_theGame->m_meshToRender.m_mesh = MeshBuilder::ReadMeshFromFile(g_theGame->m_meshToRender.m_mesh, "Data/Mesh/", "u1.mesh");

	g_theGame->m_idleAnim = Motion::ReadAnimFromFile("Data/Mesh/u1_IDLE.anim");
	g_theGame->m_jogAnim = Motion::ReadAnimFromFile("Data/Mesh/u1_WALK.anim");
	g_theGame->m_runAnim = Motion::ReadAnimFromFile("Data/Mesh/u1_RUN.anim");

	g_theGame->m_animator->AddMotionForBlending(g_theGame->m_idleAnim, 0.f);
	g_theGame->m_animator->AddMotionForBlending(g_theGame->m_jogAnim, 20.f);
	g_theGame->m_animator->AddMotionForBlending(g_theGame->m_runAnim, 40.f);

	g_theGame->m_currMotionBeingPlayed = g_theGame->m_jogAnim;
	g_theGame->m_currMotionBeingPlayed->SetPlaybackType(PLAYBACK_LOOP);
	g_theGame->m_isAnimating = true;
}