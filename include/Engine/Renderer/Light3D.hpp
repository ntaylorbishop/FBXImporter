#pragma once

#include "Engine/General.hpp"
#include "Engine/Math/Vector3.hpp"

enum LightType {
	LIGHT_POINT = 0,
	LIGHT_DIRECTIONAL,
	LIGHT_CONE,
	NUM_LIGHTS
};

class Light3D {
public:
	//STRUCTORS
	Light3D();
	Light3D(const Vector3& pos, const RGBA& color, float radius); //For Local Point Light
	Light3D(const Vector3& pos, const Vector3& dir, float dist, const RGBA& color); //For Local Directional Light
	Light3D(const Vector3& pos,const Vector3& dir,const RGBA& color, //For cone light
		float minLightDist, float maxLightDist,
		float powerAtMin, float powerAtMax,
		float thetaInner, float thetaOuter,
		float thetaInnerPower, float thetaOuterPower
	);
	Light3D(const Vector3& pos, const Vector3& dir, const RGBA& color, //For cone light
		float minLightDist, float maxLightDist,
		float powerAtMin, float powerAtMax, float dirInterp,
		float thetaInner, float thetaOuter,
		float thetaInnerPower, float thetaOuterPower
	);

	//UPDATE RENDER
	void Update(float deltaSeconds);	
	void Render() const;

	//PURE GETTERS SETTERS
	Vector3 GetPosition() const;
	Vector3 GetDirection() const;
	RGBA GetColor() const;
	float GetMinLightDistance() const;
	float GetMaxLightDistance() const;
	float GetPowerAtMin() const;
	float GetPowerAtMax() const;
	float GetIsDirectionInterpolated() const;
	float GetInnerTheta() const;
	float GetOuterTheta() const;
	float GetThetaInnerPower() const;
	float GetThetaOuterPower() const;

	void SetPosition(const Vector3& position);
	void SetDirection(const Vector3& direction);
	void SetColor(const RGBA& color);
	void SetMinLightDistance(float minLightDist);
	void SetMaxLightDistance(float maxLightDist);
	void SetPowerAtMin(float minPower);
	void SetPowerAtMax(float maxPower);
	void SetIsDirectionInterpolated(float isDirInterp);
	void SetInnerTheta(float innerTheta);
	void SetOuterTheta(float outerTheta);
	void SetThetaInnerPower(float innerPower);
	void SetThetaOuterPower(float outerPower);

	//GETTERS SETTERS
	void SetRadius(float radius);
	void SetConeWidth(float angleNormalized);


private:
	Vector3 m_position;
	Vector3 m_direction;
	RGBA m_color;
	float m_minLightDistance;
	float m_maxLightDistance;
	float m_powerAtMin;
	float m_powerAtMax;

	//Needed for cone light
	float m_directionalInterp; //1 or 0, depends on if we want to interpolate between lighting values
	float m_thetaInner;
	float m_thetaOuter;
	float m_thetaInnerPower;
	float m_thetaOuterPower;
};