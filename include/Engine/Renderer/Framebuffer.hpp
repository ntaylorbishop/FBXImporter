#pragma once

#include "Engine/General.hpp"
#include "Engine/Renderer.hpp"

class Framebuffer {
public:
	//STRUCTORS INITIALIZATION
	Framebuffer();
	Framebuffer(int width, int height, vector<eTextureFormat> color_formats, eTextureFormat depth_stencil_format);
	Framebuffer(std::vector<Texture*> colors, size_t color_count, Texture* depth_stencil_target);

	//GETTERS SETTERS
	int GetPixelWidth();
	int GetPixelHeight();
	unsigned int GetFBOHandle();
	int GetColorCount();

	Texture* GetColorTexture();
	Texture* GetDepthTexture();

private:
	uint32_t m_fboHandle;

	std::vector<Texture*> m_colorTargets;
	Texture* m_depthStencilTarget;

	int m_pixelWidth;
	int m_pixelHeight;
};