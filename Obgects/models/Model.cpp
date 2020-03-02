#include "Model.h"



Model::Model(std::string modelPath):
	m_FilePath(modelPath), m_Shader(m_ShaderPath), m_scaleCoof(glm::vec3(1.0f))
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
	}
	aiNode *node = scene->mRootNode;	
	SetNodes(node, scene);
	

	m_Shader.Undind();

}


Model::~Model()
{
}

void Model::DrawAt(const float x, const float y, const float z, const Camera* cam) 
{
	//m_position = glm::vec3(x, y, z);
	glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));

	for (int i = 0; i < m_Meshes.size(); i++) {
		m_Meshes[i].m_VA.Bind();
		m_Meshes[i].m_IB.Bind();
		m_Shader.SetUniformMat4f("u_MVP", cam->GetMatr()*trans*m_Matrix*m_Meshes[i].m_Matrix);
		m_Shader.SetUniformMat4f("modelTransMatr", trans*m_Matrix*m_Meshes[i].m_Matrix);
		m_Shader.SetUniformMat4f("m_Matrix", m_Matrix*m_Meshes[i].m_Matrix);
		m_Meshes[i].m_Texture -> Bind(m_Meshes[i].m_Texture -> GetID());
		m_Shader.SetUniform1i("DiffTexture", m_Meshes[i].m_Texture->GetID());
		m_Shader.SetUniform1i("SpecTexture", m_Meshes[i].m_SpecTexture.GetID());
		m_Shader.SetUniform3f("scaleCoof", m_scaleCoof.x, m_scaleCoof.y, m_scaleCoof.z);

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
		
		glDrawElements(GL_TRIANGLES, m_Meshes[i].m_IB.GetCount(), GL_UNSIGNED_INT, nullptr);
		m_Meshes[i].m_VA.Unbind();
		m_Meshes[i].m_IB.Unbind();
	}
	m_Shader.Undind();
}

void Model::DrawAt(glm::vec3 pos, const Camera * cam)
{
	DrawAt(pos.x, pos.y, pos.z, cam);
}

void Model::SetNodes(const aiNode * node, const aiScene * scene)
{
	m_Meshes.resize(scene->mNumMeshes);
	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[i];
		m_Meshes[i].SetDataToBuffers(mesh, scene, m_FilePath);
	}

	/*for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		SetNodes(node->mChildren[i], scene);
	}*/
}



