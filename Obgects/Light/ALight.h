#pragma once

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "GLEW/include/GL/glew.h"
#include <vector>
#include <string>


class ALight
{
public:
	ALight();
	virtual ~ALight();
	inline void SetColor(glm::vec3 newcolor)  {m_Color = newcolor; };
	inline glm::vec3 GetColor() const { return m_Color; };

	inline void SetPosition(glm::vec3 newposition) { m_Position = glm::vec4(newposition , 1.0f); };
	inline glm::vec3 GetPosition() const { return glm::vec3(m_Position); };
	inline void SetDir(const glm::vec3 newdir) { m_Direction = glm::vec4(glm::normalize(newdir), m_Angle); };
	inline glm::vec3 GetDir() const { return glm::vec3(m_Direction); };
	inline void SetAngle(const float newangle) { m_Direction = glm::vec4(glm::vec3(m_Direction), glm::cos(glm::radians(newangle))); m_Angle = glm::cos(glm::radians(newangle)); };
	inline float GetAngle() const { return m_Angle; };
		
	int lightWorldID;
	std::string lightType;

private:	
	glm::vec4 m_Position;
	glm::vec4 m_Direction;
	glm::vec3 m_Color;
	float m_Angle;
};

