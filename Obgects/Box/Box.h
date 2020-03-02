#pragma once

#include "Obgects/AObject.h"

#include <iostream>

class Box:
	public AObject
{
public:
	Box(const float a);
	~Box();

	void DrawAt(const float x, const float y, const float z, const Camera* cam) override;
	void DrawAt(glm::vec3 pos, const Camera* cam) override;
	inline void Scale(const glm::vec3 scaleCoof) override {};
	inline void Scale(const float scaleCoof) override {};
	inline void SetPosition(glm::vec3 newposition) override { m_position = newposition; };
	inline void SetVelocity(glm::vec3 newvelocity) override { m_velocity = newvelocity; };
	void SetTexture(const std::string & path);
	void SetSpecularMap(const std::string & path);



private:
	float m_side;

	unsigned int m_Indices[36] = {
		0,1,2,2,3,0,
		4,5,6,6,7,4,
		8,9,10,10,11,8,
		12,13,14,14,15,12,
		16,17,18,18,19,16,
		20,21,22,22,23,20
	};
	IndexBuffer m_IB;

	float m_Coordinates[192];
	VertexBuffer m_VB;
	VertexBufferLayout m_Layout;
	VertexArray m_VA;

	const std::string m_ShaderPath = "Obgects/Box/Res/Box.shader";
	Shader m_Shader;
	Texture m_Texture;
	Texture m_SpecTexture;
};

