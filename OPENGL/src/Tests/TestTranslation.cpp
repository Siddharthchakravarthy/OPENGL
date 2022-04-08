#include "TestTranslation.h"

test::TestTranslation::TestTranslation()
    : m_TranslationA(100.0f, 100.0f, 0.0f), m_TranslationB(200.0f, 100.0f, 0.0f)
    , m_ProjectionMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f))
    , m_ViewMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
    , m_Clear_Color(1.00f, 1.00f, 1.00f, 1.00f)
{
    float arr_of_positions[] = {
        -50.0f, -50.0f, 0.0f , 0.0f,            //// this is actually the position of the points of the image
        50.0f, -50.0f, 1.0f , 0.0f,          //// alva so changing this would change the resolution of the image
        50.0f, 50.0f, 1.0f , 1.0f,
        -50.0f, 50.0f, 0.0f , 1.0f
    };

    unsigned int indexBuffer[] = {
        0 , 1 , 2,
        2 , 3 , 0
    };
    m_Vertex_Array = std::make_unique<VertexArray>();
    m_VertexBufferLayout = std::make_unique<VertexBufferLayout>();
    m_VertexBuffer = std::make_unique<VertexBuffer>(arr_of_positions, 4 * 4 * sizeof(float));
    
    m_VertexBufferLayout->Push<float>(2);
    m_VertexBufferLayout->Push<float>(2);
    m_Vertex_Array->AddBuffer(*m_VertexBuffer, *m_VertexBufferLayout);
    unsigned int count_len = sizeof(indexBuffer) / sizeof(indexBuffer[0]);
    m_IndexBuffer = std::make_unique<IndexBuffer>(indexBuffer, count_len);


    m_Shader = std::make_unique<Shader>("res/shader/Shader.shader");

    m_Renderer = std::make_unique<Renderer>();

    m_Texture = std::make_unique<Texture>("res/textures/Peru_open_gl.png");
    m_TextureA = std::make_unique<Texture>("res/textures/ChernoLogo.png");
}

test::TestTranslation::~TestTranslation()
{
}

void test::TestTranslation::OnUpdate(float deltaTime)
{
}

void test::TestTranslation::OnRender()
{
  
    m_Shader->Bind();
    m_Texture->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);
    m_Renderer->Clear();
    angle_of_curv = angle_of_curv + Increment;
    if (angle_of_curv >= 360) {
        Increment = Increment * -1.0f;
    }
    if (angle_of_curv == 0){
        Increment = Increment * -1.0f;
    }
    {
        m_Shader->Bind();
        m_ModelA = glm::mat4(1.0f);
        m_ModelA = glm::translate(m_ModelA, m_TranslationA);
        m_ModelA = glm::rotate(m_ModelA, toRadians * angle_of_curv, glm::vec3(0.0f, 0.0f, 1.0f));
        m_MVPA = m_ProjectionMatrix * m_ViewMatrix * m_ModelA;
        m_Shader->SetUniformmat4f("u_MVP", m_MVPA);
        m_Shader->SetUniform4f("u_color", m_Clear_Color.x, m_Clear_Color.y, m_Clear_Color.z, m_Clear_Color.w);
        m_Renderer->Draw(*m_IndexBuffer, *m_Vertex_Array, *m_Shader);
    }
    m_Shader->Bind();
    m_TextureA->Bind();
    m_Shader->SetUniform1i("u_Texture", 0);
    {
        m_Shader->Bind();
        m_ModelB = glm::translate(glm::mat4(1.0f), m_TranslationB);
        m_MVPB = m_ProjectionMatrix * m_ViewMatrix * m_ModelB;
        m_Shader->SetUniformmat4f("u_MVP", m_MVPB);
        m_Shader->SetUniform4f("u_color", m_Clear_Color.x, m_Clear_Color.y, m_Clear_Color.z, m_Clear_Color.w);
        m_Renderer->Draw(*m_IndexBuffer, *m_Vertex_Array, *m_Shader);
    }
}

void test::TestTranslation::OnImGuiRender()
{
    ImGui::SliderFloat3("translationA", &m_TranslationA.x, 0.0f, 960.0f);
    ImGui::SliderFloat3("translationB", &m_TranslationB.x, 0.0f, 960.0f);
    ImGui::SliderFloat("Rotation", &angle_of_curv, 0.0f, 360.0f);
    // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3("clear color", (float*)&m_Clear_Color);
}