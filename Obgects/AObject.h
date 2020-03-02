#pragma once

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include <iostream>

class AObject
{
protected:
	AObject();

public:
	
	virtual ~AObject();

	glm::vec3 m_position;
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;

	void Rotate(glm::vec3 rotationVector, float angle);

	glm::vec4 m_Collor;
	void inline SetColor(glm::vec3 collor) { m_Collor = glm::vec4(collor,1.0f); };
	glm::vec3 GetCollor();

	glm::mat4 m_Matrix;

	int ObjectWorldID;
	virtual void DrawAt(const float x, const float y, const float z, const Camera* cam) = 0;
	virtual void DrawAt(glm::vec3 pos, const Camera* cam) = 0;
	inline virtual void SetPosition(glm::vec3 newposition) { m_position = newposition; };
	inline virtual void SetVelocity(glm::vec3 newvelocity) { m_velocity = newvelocity; };
	inline virtual void Scale(const glm::vec3 scaleCoof) {};
	inline virtual void Scale(const float scaleCoof) {};
	inline virtual void SetFirstScaleCoof() {};
	inline virtual glm::vec3 GetScaleCoof() const { return glm::vec3(1.0f); };
	glm::vec3 first_scaleCoof = glm::vec3(1.0f);

	void AddLightsToMatr(std::vector<ALight*> lights);

	glm::mat4x3 dirLightCollor;
	glm::mat4x3 dirLightDirection;

	glm::mat4x3 pointLightCollor;
	glm::mat4x3 pointLightPosition;

	glm::mat4x3 flashLightCollor;
	glm::mat4x3 flashLightPosition;
	glm::mat4 flashLightDirAndAngle;

};

