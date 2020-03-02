#include "AObject.h"



AObject::AObject():
	m_Matrix(glm::mat4(1.0f)), dirLightCollor(glm::mat4x3(0.0f)), dirLightDirection(glm::mat4x3(0.0f)),
	m_Collor(glm::vec4(0.0f)), ObjectWorldID(-1), first_scaleCoof(glm::vec3(1.0f))
{
}


AObject::~AObject()
{
}

void AObject::Rotate(glm::vec3 rotationVector, float angle)
{
	if(rotationVector != glm::vec3(0))
		m_Matrix = glm::rotate(m_Matrix, glm::radians(angle), rotationVector);
}

glm::vec3 AObject::GetCollor()
{
	return m_Collor;
}

void AObject::AddLightsToMatr(std::vector<ALight*> lights)
{
	unsigned int dirCount = 0;
	unsigned int pointCount = 0;
	unsigned int flashCount = 0;
	for (int i = 0; i < lights.size(); i++)
	{
		if (lights[i]->lightType == "Directed")
		{
			if (dirCount < 4)
			{
				this->dirLightCollor[dirCount] = lights[i]->GetColor();
				this->dirLightDirection[dirCount] = lights[i]->GetDir();				
				dirCount += 1;
			}
		}

		if (lights[i]->lightType == "Point" && pointCount<4)
		{
			this->pointLightCollor[dirCount] = lights[i]->GetColor();
			this->pointLightPosition[dirCount] = lights[i]->GetPosition();
			pointCount += 1;
		}

		if (lights[i]->lightType == "FlashLight" && flashCount < 4)
		{
			this->flashLightPosition[flashCount] = lights[i]->GetPosition();
			this->flashLightCollor[flashCount] = lights[i]->GetColor();
			this->flashLightDirAndAngle[flashCount] = glm::vec4(lights[i]->GetDir(),lights[i]->GetAngle());
			//std::cout << lights[i]->GetDir().z << "  " << lights[i]->GetDir().y << "  " << this->flashLightDirAndAngle[flashCount][3] << std::endl;
			flashCount += 1;
		}
	}
}
