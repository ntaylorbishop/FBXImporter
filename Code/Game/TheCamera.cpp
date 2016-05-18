#include "Game/TheCamera.hpp"

TheCamera* g_theCamera = nullptr;

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
TheCamera::TheCamera() 
	: m_position()
	, m_yawAboutZ(0.f)
	, m_rollAboutY(0.f)
	, m_pitchAboutX(0.f)
{ 
	Initialization();
}
TheCamera::TheCamera(Vector3 position, float roll, float pitch, float yaw) 
	: m_position(position)
	, m_rollAboutY(roll)
	, m_pitchAboutX(pitch)
	, m_yawAboutZ(yaw)
{ 
	Initialization();
}
void TheCamera::Initialization() {
	m_projection.ChangeToPerspectiveProjection(90.f, 16.f / 9.f, 0.1f, 100.f);

	Matrix4 COB = Matrix4();
	COB.SetBasis(Vector3(1.f, 0.f, 0.f), Vector3(0.f, 0.f, 1.f), Vector3(0.f, 1.f, 0.f));
	Matrix4 newProj = COB * m_projection;
	m_projection = newProj;
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE RENDER
//---------------------------------------------------------------------------------------------------------------------------
void TheCamera::Update(float deltaSeconds) {
	UNREFERENCED_PARAMETER(deltaSeconds);

	Vector3 forward = GetForwardXYZ();
	Vector3 lookAtPos = m_position + forward;

	m_view.ChangeToLookAtMatrix(lookAtPos, m_position);
	m_view.TransposeRotation();
	m_view.NegateTranslation(m_position);
}

//---------------------------------------------------------------------------------------------------------------------------
//MOVEMENT VECTORS
//---------------------------------------------------------------------------------------------------------------------------
Vector3 TheCamera::GetForwardXYZ() const {
	return Vector3(CosDegrees(m_pitchAboutX) * SinDegrees(m_yawAboutZ), CosDegrees(m_pitchAboutX) * CosDegrees(m_yawAboutZ), SinDegrees(m_pitchAboutX));
}
Vector3 TheCamera::GetForwardXY() const {
	return Vector3(CosDegrees(m_yawAboutZ), -SinDegrees(m_yawAboutZ), 0.f);
}
Vector3 TheCamera::GetLeftXY() const {
	Vector3 forwardXY = GetForwardXY();
	return Vector3(-forwardXY.y, forwardXY.x, 0.f);
}

Matrix4 TheCamera::GetViewMatrix() const {
	return m_view;
}
Matrix4 TheCamera::GetProjectionMatrix() const {
	return m_projection;
}