#include "TestTexture2D.h"
#include <glew.h>
#include "Renderer.h"
#include "imgui/imgui.h"


#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test {

	TestTexture2D::TestTexture2D()
		: m_Proj(glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f)), 
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))), 
		m_TranslationA(200, 200, 0), 
		m_TranslationB(400, 200, 0)
	{

		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f, // 0
			 50.0f, -50.0f, 1.0f, 0.0f, // 1
			 50.0f,  50.0f, 1.0f, 1.0f, // 2
			-50.0f,  50.0f, 0.0f, 1.0f  // 3

			/* 0.0, -1.0f,
			 0.5, -0.2f,
			-0.5, -0.2f,
			0.25,  0.2f,
		   -0.25,  0.2f,
			   0, -0.2f*/
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0

			/*4, 0, 1,
			0, 1, 5,
			5, 6, 0,
			7, 5, 9,
			9, 8, 6*/
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		
		m_VertexArray = std::make_unique<VertexArray>();

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 2 * 3);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.Shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		m_Texture = std::make_unique<Texture>("res/textures/Onozuka.png");

		m_Shader->SetUniform1i("u_Texture", 0); // 0 = slot der Texture

	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::OnUpdate(float DeltaTime)
	{

	}

	void TestTexture2D::OnRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;
		m_Texture->Bind();

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		}

		//shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = m_Proj * m_View * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 640.0f);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 640.0f);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}


