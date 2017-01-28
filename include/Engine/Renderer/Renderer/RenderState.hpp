#pragma once

#include "Engine/Renderer/Renderer/TheRenderer.hpp"

class RenderState {
public:
	//STRUCTORS
	RenderState();
	RenderState(bool depthTestingEnabled, bool cullFaceEnabled, bool alphaTestingEnabled, bool blendingEnabled);

	//ENABLE DISABLE COMPONENTS
	void EnableCullFace();
	void EnableDepthTesting();
	void EnableAlphaTesting();

	void DisableCullFace();
	void DisableDepthTesting();
	void DisableAlphaTesting();

	void SetBlendMode(eBlendMode srcPixel, eBlendMode destPixel);
	void EnableBlending();
	void DisableBlending();

	//ENABLE DISABLE RENDER STATE
	void EnableRenderState() const;
	void DisableRenderState() const;

	GLenum GetGLEnumForBlendMode(eBlendMode mode) const;

private:
	bool m_depthTestEnabled;
	bool m_cullFaceEnabled;
	bool m_alphaTestingEnabled;
	bool m_blendingEnabled;
	eBlendMode m_srcPixel;
	eBlendMode m_destPixel;
};