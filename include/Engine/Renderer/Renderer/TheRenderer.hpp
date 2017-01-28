#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <vector>
#pragma comment( lib, "opengl32" ) // Link in the OpenGL32.lib static library
#pragma comment( lib, "GLu32" ) // Link in the GLu32.lib static library

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Renderer/OpenGL/OpenGLExtensions.hpp"
#include "Engine/Renderer/Vertex/Vertex.hpp"
#include "Engine/Renderer/Sprites/Spritesheet.hpp"
#include "Engine/Renderer/General/Texture.hpp"
#include "Engine/Renderer/General/RGBA.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/IntVector3.hpp"
#include "Engine/Math/MathUtils.hpp"
#include "Engine/General/Utils/ErrorWarningAssert.hpp"
#include "Engine/Math/AABB2.hpp"
#include "Engine/Math/AABB3.hpp"
#include "Engine/Math.hpp"
#include "Engine/General/Utils/FileUtils.hpp"
#include "Engine/General/Utils/TheLogger.hpp"
#include "Engine/Renderer/Vertex/VertexDefinition.hpp"
#include "Engine/Renderer/OpenGL/OpenGLEnums.hpp"
#include "Engine/Renderer/Material/Shaders/Uniform.hpp"

class Framebuffer;

class TheRenderer;
extern TheRenderer* g_theRenderer;

using namespace std;

//---------------------------------------------------------------------------------------------------------------------------
//ENUMS 
//---------------------------------------------------------------------------------------------------------------------------
enum eBlendMode {
	BLEND_ZERO = 0,
	BLEND_ONE,
	BLEND_SRC_COLOR,
	BLEND_ONE_MINUS_SRC_COLOR,
	BLEND_DST_COLOR,
	BLEND_ONE_MINUS_DST_COLOR,
	BLEND_SRC_ALPHA,
	BLEND_ONE_MINUS_SRC_ALPHA,
	BLEND_DST_ALPHA,
	BLEND_ONE_MINUS_DST_ALPHA,
	BLEND_CONSTANT_COLOR,
	BLEND_ONE_MINUS_CONSTANT_COLOR,
	BLEND_CONSTANT_ALPHA,
	BLEND_ONE_MINUS_CONSTANT_ALPHA,
	BLEND_SRC_ALPHA_SATURATE,
	BLEND_SRC1_COLOR,
	BLEND_ONE_MINUS_SRC1_COLOR,
	BLEND_SRC1_ALPHA,
	BLEND_ONE_MINUS_SRC1_ALPHA
};

enum ePrimitiveType {
	PRIMITIVE_POINTS = 0,
	PRIMITIVE_LINES,
	PRIMITIVE_LINE_LOOP,
	PRIMITIVE_TRIANGLES,
	PRIMITIVE_QUADS,
	NUM_PRIMITIVE_TYPES
};

enum eShaderType {
	SHADER_VERTEX = 0,
	SHADER_FRAGMENT
};

//---------------------------------------------------------------------------------------------------------------------------
//RENDERER CLASS 
//---------------------------------------------------------------------------------------------------------------------------
class TheRenderer {
public:
	//---------------------------------------------------------------------------------------------------------------------------
	//STRUCTORS AND INITIALIZATION
	//---------------------------------------------------------------------------------------------------------------------------
	TheRenderer(Vector2 aspect, float yFieldOfView, float nearClip, float farClip);
	void InitializeOpenGLDefinitions();

	//---------------------------------------------------------------------------------------------------------------------------
	//UPDATE RENDER
	//---------------------------------------------------------------------------------------------------------------------------
	void Update(float deltaSeconds);
	void Render() const;

	//---------------------------------------------------------------------------------------------------------------------------
	//SETUP / UTILITY FUNCS
	//---------------------------------------------------------------------------------------------------------------------------
	void EnableBackfaceCulling();
	void EnableBlending();
	void EnableDepthTesting();
	void EnableAlphaTesting();
	void EnableLineSmoothing();
	void DisableBackfaceCulling();
	void DisableBlending();
	void DisableDepthTesting();
	void DisableAlphaTesting();
	void DisableLineSmoothing();

	void BlendMode(GLenum sfactor, GLenum dfactor);
	void PointSize(float size);
	void LineWidth(float width);
	void ClearBuffer(GLbitfield mask);
	void ClearScreen(float red, float green, float blue);
	String GetCurrentVersionOfGLSL();
	String GetCurrentVersionOfOpenGL();

	//---------------------------------------------------------------------------------------------------------------------------
	//DRAW OBJECTS
	//---------------------------------------------------------------------------------------------------------------------------
	void BindTexture(Texture* texture);
	void BindAndEnableTexture(Texture* texture);
	void DisableTextures();
	void SetActiveTextureBindPoint(int bindPoint);
	void ResetActiveTextureBindPoint();

	void BindTextureToSampler(Texture* texture, unsigned int bindPoint, unsigned int samplerID);
	void DisableTextureBindPoint();
	void DrawLine(const Vector2& start, const Vector2& end, RGBA color);
	void DrawLine(const Vector3& start, const Vector3& end, RGBA color);
	void DrawCircle(const Vector2& center, float radius, RGBA color);

	void DrawSquare(const AABB2& quad, const RGBA& tint, float lineWidth);
	void DrawAABB2(const AABB2& quad, const RGBA& tint, ePrimitiveType type);
	void DrawTexturedAABB2(Texture* texture, const RGBA& tint, const AABB2& quad);
	void DrawTexturedAABB2(Texture* texture, const AABB2& texCoords, const RGBA& tint, const AABB2& quad);
	void DrawTexturedAABB2FromSpriteSheet(const SpriteSheet* spriteSheet, const RGBA& tint, const AABB2& quad, const AABB2& texCoords);
	void DrawTexturedAABB2FromSpriteSheet(const SpriteSheet* spriteSheet, const RGBA& tint, const AABB2& quad, const IntVector2& spriteCoords);
	void DrawTexturedQuadFromSpritesheet(const SpriteSheet* spriteSheet, const RGBA& tint, const Vector3& bottomLeft, const Vector3& bottomRight, const Vector3& topRight, const Vector3& topLeft, const IntVector2& spriteCoords);

	void DrawVertexArray(const Vertex* verts, int numVerts, ePrimitiveType type);
	void DrawVertexArray(const vector<Vertex>& verts, int numVerts, ePrimitiveType type);
	void DrawVertexArray(const TexturedVertex* verts, int numVerts, ePrimitiveType type);
	void DrawVertexArray(const vector<TexturedVertex>& verts, int numVerts, ePrimitiveType type);

	//---------------------------------------------------------------------------------------------------------------------------
	//VBO'S
	//---------------------------------------------------------------------------------------------------------------------------
	int GenerateNewVboID();

	void UpdateVBO(const vector<TexturedVertex_TBNBN>& verts, int numVerts, int vboID);
	void UpdateVBO(const TexturedVertex_TBNBN* verts, int numVerts, int vboID);
	void UpdateVBO(const vector<TexturedVertex_N>& verts, int numVerts, int vboID);
	void UpdateVBO(const TexturedVertex_N* verts, int numVerts, int vboID);
	void UpdateVBO(const vector<TexturedVertex_TBN>& verts, int numVerts, int vboID);
	void UpdateVBO(const TexturedVertex_TBN* verts, int numVerts, int vboID);
	void UpdateVBO(const vector<TexturedVertex>& verts, int numVerts, int vboID);
	void UpdateVBO(const TexturedVertex* verts, int numVerts, int vboID);
	void UpdateVBO(const vector<Vertex>& verts, int numVerts, int vboID);
	void UpdateVBO(const Vertex* verts, int numVerts, int vboID);

	void DrawVBO(int numVerts, ePrimitiveType type, int &vboID, bool isTextured);
	void ClearVBOData(int vboID);
	void BindVBO(int vboID);

	//---------------------------------------------------------------------------------------------------------------------------
	//VAO's
	//---------------------------------------------------------------------------------------------------------------------------
	int GenerateNewVaoID();
	void ClearVAOData(int vaoID);
	void BindVAO(int vaoID);

	//---------------------------------------------------------------------------------------------------------------------------
	//VIEW MATRIX TRANSLATIONS
	//---------------------------------------------------------------------------------------------------------------------------
	void LoadIdentity();
	void SetOrtho2D(const Vector2& mins, const Vector2& maxs);
	void SetPerspective(float fieldOfViewYAxis, float aspect, float nearClippingPlane, float farClippingPlane);

	void TranslateViewMatrix(const Vector2& offset);
	void TranslateViewMatrix(const Vector3& offset);
	void RotateViewMatrix(float angle); //Takes radians
	void RotateViewMatrix(float angle, const Vector3& axisOfRotation); //Takes degrees
	void SetCamera3D(const Vector3& cameraRotation, const Vector3& cameraPosition);
	Vector3 Get3DCameraPosition();

	GLenum GetGLEnumForPrimitiveType(ePrimitiveType type);
	int GetShaderTypeForEnum(eShaderType type);


	//---------------------------------------------------------------------------------------------------------------------------
	//TESTING
	//---------------------------------------------------------------------------------------------------------------------------
	void EnableGLAlphaFunc(float amount);
	void DisableGLAlphaFunc();

	//---------------------------------------------------------------------------------------------------------------------------
	//SHADERS
	//---------------------------------------------------------------------------------------------------------------------------
	void DeleteShader(int shaderID);
	void DeleteProgram(int programID);
	int LoadShader(const String& fileName, int shaderType);
	int CreateAndLinkProgram(int vertexShaderID, int fragmentVertexShaderID, String vertFilePath, String fragFilePath);
	void UseProgram(int programID);

	bool ShaderProgramSetMat4(int programID, const String& name, const Matrix4& mat) const;
	bool ShaderProgramSetInt(int programID, const String& name, int val) const;
	bool ShaderProgramSetColor(int programID, const String& name, const RGBA& color) const;
	bool ShaderProgramSetFloat(int programID, const String& name, float val) const;
	bool ShaderProgramSetVector3(int programID, const String& name, const Vector3& vec3) const;

	bool ShaderProgramSetMat4Array(int programID, const String& name, std::vector<Matrix4>& vals) const;
	bool ShaderProgramSetIntArray(int programID, const String& name, std::vector<int>& vals) const;
	bool ShaderProgramSetColorArray(int programID, const String& name, std::vector<RGBA>& vals) const;
	bool ShaderProgramSetFloatArray(int programID, const String& name, std::vector<float>& vals) const;
	bool ShaderProgramSetVector3Array(int programID, const String& name, std::vector<Vector3>& vals) const;
	void ShaderProgramBindProperty(int programID, const String& name, int32_t count, int32_t type, int normalize, int stride, int offset);

	void UpdateUniformInShaderProgram(int programID, Uniform* uniform);
	Uniform* GetShaderProgramUniform(int programID, uint idx);
	Uniform* CreateUniform(const String& name, uint size, eRenderEnum type);

	void BindVertexAttributes(int programID, VertexDefinition vertexDef);

	void BindIBO(int iboID);
	void UnbindPrograms();
	void UnbindVAOs();
	void UnbindVBOs();
	void UnbindIBOs();
	void UpdateIBOData(int iboID, const std::vector<uint16_t>& data, bool isStatic);
	void DrawElements(ePrimitiveType renderType, int size, GLenum type);
	void DrawArray(ePrimitiveType renderType, int size, GLenum type);
	//glDrawArrays(GetGLEnumForPrimitiveType(type), 0, numVerts);

	GLuint CreateSampler(eRenderEnum min_filter, eRenderEnum mag_filter, eRenderEnum u_wrap, eRenderEnum v_wrap) const; //min_filter: How it shrinks, mag_filter: how it stretches, u_wrap / v_wrap: if not normalized, how does it behave
	void BindTextureToSampler(unsigned int bindPointIdx, unsigned int samplerID);

	unsigned int GetNumberOfActiveUniforms(int programID) const;

	//---------------------------------------------------------------------------------------------------------------------------
	//MODEL VIEW TRANSFORM STUFF
	//---------------------------------------------------------------------------------------------------------------------------
	Matrix4 GetViewMatrix();
	Matrix4 GetProjectionMatrix();

	void SetUpPerspectiveProjection(float yFovDegrees, float aspect, float nearClippingPlane, float farClippingPlane);
	void SetUpProjectionMatrix(float screenWidth, float screenHeight, float nearClip, float farClip);

	//---------------------------------------------------------------------------------------------------------------------------
	//FRAME BUFFERS
	//---------------------------------------------------------------------------------------------------------------------------
	void FramebufferBind(Framebuffer* fbo);
	void FramebufferCopyToBack(Framebuffer* fbo);

private:
	Matrix4 m_view;
	Matrix4 m_projection;
	Vector2 m_screenSize;

	Vector3 m_cameraPosition;

	Framebuffer* m_currentUserFBO;
};