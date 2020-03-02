#include "DirectedLight.h"



DirectedLight::DirectedLight() 
{
	this->SetDir(glm::vec3(0.0f, 0.0f, -1.0f));
	lightType = "Directed";
}


DirectedLight::~DirectedLight()
{
}
