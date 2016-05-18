#include "Game/Sphere.hpp"

//---------------------------------------------------------------------------------------------------------------------------
//STRUCTORS
//---------------------------------------------------------------------------------------------------------------------------
Sphere::Sphere() { }
Sphere::Sphere(float radius, const Vector3& position) {
	m_mesh = Mesh(VertexDefinition::TEXTUREDVERTEX_TBN);
	m_material = g_theMaterialManager->GetMaterial("Brick");
	CreateMesh(radius);

	m_mesh.ChangePosition(position);
}

//---------------------------------------------------------------------------------------------------------------------------
//UPDATE RENDER
//---------------------------------------------------------------------------------------------------------------------------
void Sphere::Update(float deltaSeconds) {
	UNREFERENCED_PARAMETER(deltaSeconds);
}
void Sphere::Render() const {
	m_meshRenderer.RenderMeshWithMaterial(m_mesh, m_material);
}

//---------------------------------------------------------------------------------------------------------------------------
//PRIVATE MEMBER FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
void Sphere::CreateMesh(float radius) {
	std::vector<TexturedVertex_TBN> sphereVerts;
	std::vector<uint16_t> sphereIndices;
	int rings = 100;
	int sectors = 100;
	int curRow = 0;
	int nextRow = 0;
	int nextS = 0;

	//r * R ==== UP
	//s * S ==== RIGHT

	float const R = 1.f / (float)(rings - 1);
	float const S = 1.f / (float)(sectors - 1);

	for (int r = 0; r < rings; ++r) {
		for (int s = 0; s < sectors; ++s) {
			float const x = (float)sin(2 * (float)M_PI * s * S) * (float)sin((float)M_PI * r * R);
			float const y = (float)cos(2 * (float)M_PI * s * S) * (float)sin((float)M_PI * r * R);
			float const z = (float)sin(-(float)M_PI_2 + (float)M_PI * r * R);

			Vector3 tangent = radius * Vector3((float)cos(2.f * M_PI * s * S) * (float)sin(M_PI * r * R), -(float)sin(2 * M_PI * s * S) * (float)sin(M_PI * r * R), (float)sin(-(float)M_PI_2 + (float)M_PI * r * R));
			Vector3 bitangent = radius * Vector3((float)sin(2 * (float)M_PI * s * S) * (float)cos((float)M_PI * r * R), (float)cos(2 * (float)M_PI * s * S) * (float)cos((float)M_PI * r * R), (float)cos((float)M_PI_2 + (float)M_PI * r * R));

			tangent.Normalize();
			bitangent.Normalize();

			sphereVerts.push_back(TexturedVertex_TBN(Vector3(x * radius, y * radius, -z * radius), RGBA::WHITE, Vector2(1 - s*S, r*R), tangent , bitangent));

			g_theDebugRenderer->DrawDebugLine(tangent, DebugExtendVector3(tangent), RGBA::MAGENTA, DEBUG_DRAW_DEPTH_TEST_DUAL);
			g_theDebugRenderer->DrawDebugLine(tangent, DebugExtendVector3(bitangent), RGBA::MAGENTA, DEBUG_DRAW_DEPTH_TEST_DUAL);

			curRow = r * sectors;
			nextRow = (r + 1) * sectors;
			nextS = (s + 1) % sectors;

			if (r < rings - 1) {
				sphereIndices.push_back((unsigned short)nextRow + (unsigned short)nextS);
				sphereIndices.push_back((unsigned short)nextRow + (unsigned short)s);
				sphereIndices.push_back((unsigned short)curRow + (unsigned short)s);

				sphereIndices.push_back((unsigned short)curRow + (unsigned short)nextS);
				sphereIndices.push_back((unsigned short)nextRow + (unsigned short)nextS);
				sphereIndices.push_back((unsigned short)curRow + (unsigned short)s);
			}
		}
	}

	m_mesh.UpdateMesh(sphereVerts, sphereIndices);
}

Vector3 Sphere::DebugExtendVector3(const Vector3& vec) {
	Vector3 dir = vec;
	dir.Normalize();
	dir = dir + vec;
	return dir;
}