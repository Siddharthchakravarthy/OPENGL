#pragma once
#include "Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "shader.h"
#include "VertexBufferLayout.h"
#include <memory>
#include "Texture.h"
namespace test {
	class TestTranslation : public Test{
	public:
		TestTranslation();
		~TestTranslation();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
		
	private:
		float angle_of_curv = 0.0f;
		float Increment = 1.0f;
		const float toRadians = 3.147f / 180.0f;
		glm::vec3 m_TranslationA;
		glm::vec3 m_TranslationB;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexArray> m_Vertex_Array;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBufferLayout> m_VertexBufferLayout;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Texture> m_TextureA;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		ImVec4 m_Clear_Color;
		glm::mat4 m_ModelA;
		glm::mat4 m_MVPA;
		glm::mat4 m_ModelB;
		glm::mat4 m_MVPB;
	};
}
