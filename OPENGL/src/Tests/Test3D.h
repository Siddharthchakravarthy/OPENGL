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
namespace test {
	class Test3D : public Test
	{
	public:
		Test3D();
		~Test3D();
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		float angle_of_curv = 0.0f;
		float Increment = 1.0f;
		const float toRadians = 3.147f / 180.0f;
		float Z_Translate;
		float Y_Translate;
		float X_Translate;
		float VX_Rotate; 
		float VY_Rotate; 
		float VZ_Rotate;
		glm::vec3 m_Translation;
		std::unique_ptr<Renderer> m_Renderer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexArray> m_Vertex_Array;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBufferLayout> m_VertexBufferLayout;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_Model;
		glm::mat4 m_MVP;
		ImVec4 m_Clear_Color;
	};
}

