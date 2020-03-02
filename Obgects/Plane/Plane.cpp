#include "Plane.h"
#include <iostream>


Plane::Plane(const float a, const float b)
	:m_sizeA(a),m_sizeB(b),m_Matrix(glm::mat4(1.0f)), m_Shader(m_ShaderPath), m_Norm(glm::vec3(0.0f,0.0f,1.0f))
{
	float Coordinates[20] = {
	-a / 2.0f, -b / 2.0f, 0.0f,  0.0f,  0.0f,
	 a / 2.0f, -b / 2.0f, 0.0f,  1.0f,  0.0f,
	 a / 2.0f,  b / 2.0f, 0.0f,  1.0f,  1.0f,
	-a / 2.0f,  b / 2.0f, 0.0f,  0.0f,  1.0f
	};
	for(int i=0;i<20;i++)
		m_Coordinates[i] = Coordinates[i];	
	
	m_VB.SetData(&m_Coordinates, 20 * sizeof(float));	
	m_Layout.Push<float>(3);
	m_Layout.Push<float>(2);
	m_VA.SetBuffer(m_VB, m_Layout);	
	
	m_IB.SetIndices(m_Indices, 6);

	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}


Plane::~Plane()
{
}

void Plane::DrawAt(const float x, const float y, const float z , const Camera cam)
{
	m_position = glm::vec3(x, y, z);
	glm::mat4 tr = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	

	
	m_Texture.Bind(0);
	
	m_Shader.SetUniformMat4f("u_MVP", cam.GetMatr() * tr * m_Matrix);
	
	//m_Shader.SetUniform3f("normal", m_Norm.x, m_Norm.y, m_Norm.z);

	glm::vec3 resultLightColor = glm::vec3(0.0f);
	for (int i = 0; i < cam.vectorOfWorldLights.size(); i++)
		resultLightColor += cam.vectorOfWorldLights[i].lightColor;
	for (int i = 0; i < 3; i++)
		if (resultLightColor[i] > 1.0f)
			resultLightColor[i] = 1.0f;
	m_Shader.SetUniform3f("summlightColor", resultLightColor.r, resultLightColor.g, resultLightColor.b);

	glm::vec3 diffuseComp = glm::vec3(0.0f);
	for (int i = 0; i < cam.vectorOfWorldLights.size(); i++)
	{
		glm::vec3 lightDir = glm::normalize(cam.vectorOfWorldLights[i].lightPosition - glm::vec3(x, y, z));
		float cosofangle = 0.0f;
		if (dot(m_Norm, lightDir)>0.0f)
			cosofangle = dot(m_Norm, lightDir);
		diffuseComp += cam.vectorOfWorldLights[i].lightColor * cosofangle;
	}	
	m_Shader.SetUniform3f("diffComp", diffuseComp.r, diffuseComp.g, diffuseComp.b);
	
	

	/////////Add only 4 light sourses///////////
	glm::mat4x3 lightPositions = glm::mat4x3(0.0f);
	glm::mat4x3 lightCollors = glm::mat4x3(0.0f);
	int numberoflights = cam.vectorOfWorldLights.size();
	if (cam.vectorOfWorldLights.size() > 4)
		numberoflights = 4;
	for (int i = 0; i < numberoflights; i++) {
		lightPositions[i] = cam.vectorOfWorldLights[i].lightPosition;
		lightCollors[i] = cam.vectorOfWorldLights[i].lightColor;
	}
	m_Shader.SetUniformMat4x3f("lightPositions", lightPositions);
	m_Shader.SetUniformMat4x3f("lightColors", lightCollors);


	m_Shader.SetUniformMat4f("modelMatr", tr * m_Matrix);
	m_Shader.SetUniform3f("camPos", cam.GetPos().x, cam.GetPos().y, cam.GetPos().z);
	m_Shader.SetUniform3f("normal", m_Norm.x, m_Norm.y, m_Norm.z);
	///////////////////////////////////////////////////
	m_IB.Bind();
	m_VA.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	
	m_VA.Unbind();	
	m_Shader.Undind();
	m_IB.Unbind();
	m_Texture.Unbind();
	
}

void Plane::SetTexture(const std::string & path)
{
	m_Texture.Bind(m_Texture.GetID());
	m_Texture.SetTexture(path);
	m_Texture.Bind(m_Texture.GetID());
	m_Shader.SetUniform1i("ourTexture", m_Texture.GetID());

	m_SpecTexture.Bind(m_SpecTexture.GetID());
	m_SpecTexture.SetTexture(path);
	m_SpecTexture.Bind(m_SpecTexture.GetID());
	m_Shader.SetUniform1i("specularTexture", m_SpecTexture.GetID());
}

void Plane::SetSpecularMap(const std::string & path)
{
	m_SpecTexture.Bind(m_SpecTexture.GetID());
	m_SpecTexture.SetTexture(path);
	m_SpecTexture.Bind(m_SpecTexture.GetID());
	m_Shader.SetUniform1i("specularTexture", m_SpecTexture.GetID());
}

void Plane::ChangeSize(const float x, const float y)
{
	
	for (int i = 0; i < 4; i++) {
		m_Coordinates[5 * i] *= x / 2.0f / (m_sizeA / 2.0f);
		m_Coordinates[5 * i+1] *= y / 2.0f / (m_sizeB / 2.0f);
	}

	m_sizeA = x;
	m_sizeB = y;

	m_VB.SetData(&m_Coordinates, 20 * sizeof(float));
	m_VA.SetBuffer(m_VB, m_Layout);
}

void Plane::SetNormal(const glm::vec3 normalVector)
{
	if (glm::normalize(normalVector) != glm::normalize(m_Norm) && glm::normalize(normalVector) != glm::normalize(-m_Norm)) {
		float angle;
		glm::vec3 newnorm = glm::normalize(normalVector);
		angle = glm::acos(newnorm.x*m_Norm.x + newnorm.y*m_Norm.y + newnorm.z*m_Norm.z)/sqrt((newnorm.x*newnorm.x+ newnorm.y*newnorm.y + newnorm.z*newnorm.z)*(m_Norm.x*m_Norm.x + m_Norm.y*m_Norm.y + m_Norm.z*m_Norm.z));
		m_Matrix = glm::rotate(glm::mat4(1.0f), angle, glm::cross(m_Norm, newnorm));		
		m_Norm = newnorm;		
	}	
	if (glm::normalize(normalVector) == glm::normalize(-m_Norm))
	{		
		m_Norm = -m_Norm;
	}
}
