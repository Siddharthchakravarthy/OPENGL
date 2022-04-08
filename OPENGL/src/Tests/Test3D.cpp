#include "Test3D.h"

test::Test3D::Test3D() :
	m_Translation(-45.0f, -7.0f, -250.0f)
	, m_ViewMatrix(glm::mat4(1.0f))
	, Z_Translate(0), VZ_Rotate(0)
	, Y_Translate(0), VY_Rotate(0)
	, X_Translate(0), VX_Rotate(0)
{
	float Vertices[] = {
		 -50.0f, -50.0f,  0.0f,
		  50.0f, -50.0f,  0.0f,
		  0.0f ,  50.0f,  0.0f,
		  0.0f , -50.0f,  50.0f
	};

	unsigned int indexBuffer[] = {
		0 , 1 , 2,
		1 , 3 , 2,
		0 , 3 , 2,
		0 , 3 , 1
	};
	m_VertexBuffer = std::make_unique<VertexBuffer>(Vertices, 12 * sizeof(float));
	m_Vertex_Array = std::make_unique<VertexArray>();
	m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
	m_IndexBuffer = std::make_unique<IndexBuffer>(indexBuffer, 12);
	m_VertexBufferLayout->Push<float>(3);
	
	m_Vertex_Array->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);

	m_Renderer = std::make_unique<Renderer>();
	m_Shader = std::make_unique<Shader>("res/Shader/3DShader.shader");

}

test::Test3D::~Test3D()
{
}

void test::Test3D::OnUpdate(float deltaTime)
{
}

void test::Test3D::OnRender()
{
	m_Shader->Bind();
	angle_of_curv = angle_of_curv + Increment;
	if (angle_of_curv >= 360) {
		Increment = Increment * -1.0f;
	}
	if (angle_of_curv == 0) {
		Increment = Increment * -1.0f;
	}
	m_Model = glm::mat4(1.0f);
	//m_Model = glm::translate(m_Model, glm::vec3(X_Translate, Y_Translate, Z_Translate));
	m_Model = glm::translate(m_Model, m_Translation);

	m_Model = glm::rotate(m_Model, toRadians * angle_of_curv , glm::vec3(0.0f, 1.0f, 0.0f));
	m_Model = glm::scale(m_Model, glm::vec3(1.4f, 1.4f, 2.0f));


	m_ViewMatrix = glm::rotate(glm::mat4(1.0f), 50.0f * toRadians, glm::vec3(VX_Rotate, VY_Rotate, VZ_Rotate));
	m_ViewMatrix = glm::translate(m_ViewMatrix, glm::vec3(X_Translate, Y_Translate, Z_Translate));
	
	//m_Shader->SetUniform4f("u_color", m_Clear_Color.x, m_Clear_Color.y, m_Clear_Color.z, m_Clear_Color.w);
	m_ProjectionMatrix = glm::perspective(45.0f, 960.0f / 540.0f, 0.1f, 540.0f);
	//m_ProjectionMatrix = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -500.0f, 500.0f);
	m_MVP = m_ProjectionMatrix * m_ViewMatrix * m_Model;

	m_Shader->SetUniformmat4f("u_MVP", m_MVP);
	m_Renderer->Draw(*m_IndexBuffer, *m_Vertex_Array, *m_Shader);
}

void test::Test3D::OnImGuiRender()
{
	ImGui::SliderFloat3("Projected_model_translation", &m_Translation.x, -500.0f, 360.0f);
	ImGui::SliderFloat("Rotation", &angle_of_curv, 0.0f, 360.0f);
	ImGui::SliderFloat("Z_Translate", &Z_Translate, -500.0f, 360.0f);
	ImGui::SliderFloat("Y_Translate", &Y_Translate, -500.0f, 360.0f);
	ImGui::SliderFloat("X_Translate", &X_Translate, -500.0f, 360.0f);
	ImGui::SliderFloat("VX_Rotate", &VX_Rotate, -500.0f, 360.0f);
	ImGui::SliderFloat("VY_Rotate", &VY_Rotate, -500.0f, 360.0f);
	ImGui::SliderFloat("VZ_Rotate", &VZ_Rotate, -500.0f, 360.0f);

	ImGui::ColorEdit3("clear color", (float*)&m_Clear_Color);
}
