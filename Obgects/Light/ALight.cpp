#include "ALight.h"



ALight::ALight()
	:m_Color(glm::vec3(1.0f)),m_Position(glm::vec4(0.0f)), m_Direction(glm::vec4(0.0f)), lightWorldID(-1), m_Angle(0.0f)
{
	
}


ALight::~ALight()
{
}
