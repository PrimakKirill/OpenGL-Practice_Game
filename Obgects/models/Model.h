#pragma once
#include "Obgects/AObject.h"
#include "Mesh.h"
#include <string>
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include "assimp\config.h"

//struct Mesh
//{
//	Mesh(const aiMesh *mesh, const aiScene *scene);
//	VertexBuffer m_VB;
//	IndexBuffer m_IB;
//	VertexArray m_VA;
//	VertexBufferLayout m_lay;
//	Texture m_Texture;
//};

class Model :
	public AObject
{
public:
	Model(std::string modelPath);
	~Model();
	void DrawAt(const float x, const float y, const float z, const Camera* cam) override;
	void DrawAt(glm::vec3 pos, const Camera* cam) override;
	inline void Scale(const glm::vec3 scaleCoof) override { m_scaleCoof = scaleCoof; } ;
	inline void Scale(const float scaleCoof) override { m_scaleCoof = glm::vec3(scaleCoof); } ;
	//glm::vec3 first_scaleCoof;
	inline void SetFirstScaleCoof() override { first_scaleCoof = m_scaleCoof; };
	inline glm::vec3 GetScaleCoof() const override {return m_scaleCoof; };
	
	IndexBuffer m_IB;
	VertexArray m_VA;
	VertexBuffer m_VB;
	VertexBufferLayout m_lay;
	
	std::string m_FilePath;	
	
private:
	const std::string m_ShaderPath = "Obgects/Model.shader";
	Shader m_Shader;
	std::vector<Mesh> m_Meshes;
	void SetNodes(const aiNode *node, const aiScene *scene);
	
	glm::vec3 m_scaleCoof;
};

