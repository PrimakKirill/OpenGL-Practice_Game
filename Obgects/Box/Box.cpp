#include "Box.h"



Box::Box(const float a):
	m_side(a) ,  m_Shader(m_ShaderPath)
{
	float coordinates[192] = {
		 a / 2.0 , -a / 2.0 , -a / 2.0 , 0.0 , 0.0 , -1.0 , 0.25f , 1.0f / 3.0f,
		 a / 2.0 ,  a / 2.0 , -a / 2.0 , 0.0 , 0.0 , -1.0 , 0.5f  , 1.0f / 3.0f,
		-a / 2.0 ,  a / 2.0 , -a / 2.0 , 0.0 , 0.0 , -1.0 , 0.5f  , 0.0f,
		-a / 2.0 , -a / 2.0 , -a / 2.0 , 0.0 , 0.0 , -1.0 , 0.25f , 0.0f,
																	   
		 a / 2.0 , -a / 2.0 , -a / 2.0 , 0.0 , -1.0 , 0.0 , 0.25f , 1.0f / 3.0f,
		-a / 2.0 , -a / 2.0 , -a / 2.0 , 0.0 , -1.0 , 0.0 , 0.0f  , 1.0f / 3.0f,
		-a / 2.0 , -a / 2.0 ,  a / 2.0 , 0.0 , -1.0 , 0.0 , 0.0f  , 2.0f / 3.0f,
		 a / 2.0 , -a / 2.0 ,  a / 2.0 , 0.0 , -1.0 , 0.0 , 0.25f , 2.0f / 3.0f,
																	   
		 a / 2.0 , -a / 2.0 , -a / 2.0 , 1.0 , 0.0 , 0.0 , 0.25f , 1.0f/ 3.0f,
		 a / 2.0 ,  a / 2.0 , -a / 2.0 , 1.0 , 0.0 , 0.0 , 0.5f  , 1.0f/ 3.0f,
		 a / 2.0 ,  a / 2.0 ,  a / 2.0 , 1.0 , 0.0 , 0.0 , 0.5f  , 2.0f/ 3.0f,
		 a / 2.0 , -a / 2.0 ,  a / 2.0 , 1.0 , 0.0 , 0.0 , 0.25f , 2.0f/ 3.0f,
																	   
		 a / 2.0 ,  a / 2.0 , -a / 2.0 , 0.0 , 1.0 , 0.0 , 0.5f  , 1.0f/ 3.0f,
		-a / 2.0 ,  a / 2.0 , -a / 2.0 , 0.0 , 1.0 , 0.0 , 0.75f , 1.0f/ 3.0f,
		-a / 2.0 ,  a / 2.0 ,  a / 2.0 , 0.0 , 1.0 , 0.0 , 0.75f , 2.0f/ 3.0f,
		 a / 2.0 ,  a / 2.0 ,  a / 2.0 , 0.0 , 1.0 , 0.0 , 0.5f  , 2.0f/ 3.0f,
																	   
		-a / 2.0 ,  a / 2.0 , -a / 2.0 , -1.0 , 0.0 , 0.0 , 0.75f , 1.0f / 3.0f,
		-a / 2.0 , -a / 2.0 , -a / 2.0 , -1.0 , 0.0 , 0.0 , 1.0f  , 1.0f / 3.0f,
		-a / 2.0 , -a / 2.0 ,  a / 2.0 , -1.0 , 0.0 , 0.0 , 1.0f  , 2.0f / 3.0f,
		-a / 2.0 ,  a / 2.0 ,  a / 2.0 , -1.0 , 0.0 , 0.0 , 0.75f , 2.0f / 3.0f,
																	   
		 a / 2.0 , -a / 2.0 ,  a / 2.0 ,  0.0 , 0.0 , 1.0 , 0.25f , 2.0f / 3.0f,
		 a / 2.0 ,  a / 2.0 ,  a / 2.0 ,  0.0 , 0.0 , 1.0 , 0.5f  , 2.0f / 3.0f,
		-a / 2.0 ,  a / 2.0 ,  a / 2.0 ,  0.0 , 0.0 , 1.0 , 0.5f  , 1.0f,
		-a / 2.0 , -a / 2.0 ,  a / 2.0 ,  0.0 , 0.0 , 1.0 , 0.25f , 1.0f
	};


	for (int i = 0; i < 192; i++) 
		m_Coordinates[i] = coordinates[i];
		
	m_VB.SetData(&m_Coordinates, 192 * sizeof(float));
	m_IB.SetIndices(m_Indices, 36);

	m_Layout.Push<float>(3);
	m_Layout.Push<float>(3);
	m_Layout.Push<float>(2);
	
	//m_IB.Unbind();
	m_VA.SetBuffer(m_VB, m_Layout);
	m_Shader.Undind();

	m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	m_acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

}

void Box::DrawAt(const float x, const float y, const float z, const Camera* cam)
{
	//m_position = glm::vec3(x, y, z);
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
	m_VA.Bind();
	m_IB.Bind();
		
	m_Shader.SetUniformMat4f("u_MVP", cam->GetMatr()*trans*m_Matrix);
	m_Shader.SetUniformMat4f("modelTransMatr", trans*m_Matrix);
	m_Shader.SetUniformMat4f("m_Matrix", m_Matrix);
	m_Shader.SetUniform4f("m_Collor", m_Collor.r, m_Collor.g, m_Collor.b, m_Collor.w);

	//Lights
	m_Shader.SetUniform3f("camPos", cam->GetPos().x, cam->GetPos().y, cam->GetPos().z);
	//DirLights
	m_Shader.SetUniformMat4x3f("dirLightCollor", dirLightCollor);
	m_Shader.SetUniformMat4x3f("dirLightDirection", dirLightDirection);
	//Point Lights(max 4)
	m_Shader.SetUniformMat4x3f("pointLightCollor", pointLightCollor);
	m_Shader.SetUniformMat4x3f("pointLightPos", pointLightPosition);
	//Flash Lights(max 4)
	m_Shader.SetUniformMat4x3f("flashLightCollor", flashLightCollor);
	m_Shader.SetUniformMat4x3f("flashLightPos", flashLightPosition);
	m_Shader.SetUniformMat4f("flashLightDirAndAngle", flashLightDirAndAngle);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

	m_VA.Unbind();
	m_Shader.Undind();
	m_IB.Unbind();
	//m_Texture.Unbind();
}

void Box::DrawAt(glm::vec3 pos, const Camera * cam)
{
	DrawAt(pos.x, pos.y, pos.z, cam);
}


void Box::SetTexture(const std::string & path)
{
	m_Texture.Bind(m_Texture.GetID());
	m_Texture.SetTexture(path);
	m_Texture.Bind(m_Texture.GetID());
	m_Shader.SetUniform1i("BoxTexture", m_Texture.GetID());
	SetSpecularMap(path);

	m_Collor = glm::vec4(0.0f);
}

void Box::SetSpecularMap(const std::string & path)
{
	m_SpecTexture.Bind(m_SpecTexture.GetID());
	m_SpecTexture.SetTexture(path);
	m_SpecTexture.Bind(m_SpecTexture.GetID());
	m_Shader.SetUniform1i("SpecTexture", m_SpecTexture.GetID());
}

Box::~Box()
{
}


