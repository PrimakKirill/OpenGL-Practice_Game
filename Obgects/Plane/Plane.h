#pragma once

#include "Obgects/AObject.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

#include <iostream>


class Plane:
	public AObject
{
public:
	Plane(const float a, const float b);
	~Plane();
	void DrawAt(const float x, const float y, const float z, const Camera cam) override;
	inline void SetPosition(glm::vec3 newposition) override { m_position = newposition; };
	inline void SetVelocity(glm::vec3 newvelocity) override { m_velocity = newvelocity; };

	void SetTexture(const std::string & path);
	void SetSpecularMap(const std::string & path);
	void ChangeSize(const float x, const float y);
	void SetNormal(const glm::vec3 normalVector);

private:
	//usual data
	float m_sizeA;
	float m_sizeB;
	float m_Coordinates[20];
	unsigned int m_Indices[6] = {
		0,1,2,
		2,3,0
	};
	glm::vec3 m_Norm;

	//buffers and array
	VertexBuffer m_VB;
	VertexBufferLayout m_Layout;
	VertexArray m_VA;
	IndexBuffer m_IB;

	//
	glm::mat4 m_Matrix;
	const std::string m_ShaderPath = "Obgects/Plane/Res/Plane.shader";
	Shader m_Shader;
	//const std::string & texturePath = "Obgects/Plane/Res/Picture.png";
	Texture m_Texture;
	Texture m_SpecTexture;
};

