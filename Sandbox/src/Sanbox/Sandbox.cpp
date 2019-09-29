#include "Sandbox/Sandbox.h"

#include "Epoch/Platform/OpenGL/OpenGLShader.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// --------------- Example Layer -----------------

SandboxLayer::SandboxLayer()
	: Layer("SandboxLayer"), m_CameraController(16.0f / 9.0f)
{
	// Blue Square VAO
	m_FlatSquareVAO.reset(Epoch::VertexArray::create());

	float square_vertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	Epoch::Ref<Epoch::VertexBuffer> squareVBO;
	squareVBO = Epoch::VertexBuffer::create(square_vertices, sizeof(square_vertices));

	squareVBO->setBufferLayout({
		{ Epoch::ShaderDataType::Float3, "a_Position" },
		{ Epoch::ShaderDataType::Float2, "a_TextCoord" },
	});
	m_FlatSquareVAO->addVertexBuffer(squareVBO);

	uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<Epoch::IndexBuffer> squareIBO;
	squareIBO = Epoch::IndexBuffer::create(square_indices, sizeof(square_indices) / sizeof(uint32_t));
	m_FlatSquareVAO->setIndexBuffer(squareIBO);

	// Blue Square Shader
	std::string flatShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

	std::string flatShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

	m_FlatColorShader = Epoch::Shader::create("FlatColor", flatShaderVertexSrc, flatShaderFragmentSrc);

	auto textureShader = m_ShaderLibrary.load("assets/shaders/Texture.glsl");
	
	m_CheckerboardTexture = Epoch::Texture2D::create("assets/textures/Checkerboard.png");

	textureShader->bind();
	std::dynamic_pointer_cast<Epoch::OpenGLShader>(textureShader)->uploadUniformInt("u_Texture", 0);
}

void SandboxLayer::onUpdate(Epoch::Timestep ts)
{
	m_CameraController.onUpdate(ts);

	Epoch::RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Epoch::RendererCommand::clear();

	Epoch::Renderer::beginScene(m_CameraController.getCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	m_FlatColorShader->bind();
	std::dynamic_pointer_cast<Epoch::OpenGLShader>(m_FlatColorShader)->uploadUniformFloat3("u_Color", m_SquareColor);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Epoch::Renderer::submit(m_FlatColorShader, m_FlatSquareVAO, transform);
		}
	}

	auto textureShader = m_ShaderLibrary.get("Texture");

	m_CheckerboardTexture->bind();
	Epoch::Renderer::submit(textureShader, m_FlatSquareVAO, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Epoch::Renderer::endScene();
}

void SandboxLayer::onEvent(Epoch::Event& e)
{
	m_CameraController.onEvent(e);
}

void SandboxLayer::onImGuiRender()
{
	ImGui::Begin("Color");
	ImGui::ColorEdit3("Square Color", value_ptr(m_SquareColor));
	ImGui::End();

	ImGui::Begin("Resizing window");
	if (ImGui::Button("Windowed"))
		Epoch::Application::get().getWindow().setWindowMode(Epoch::WindowMode::WINDOW);
	if (ImGui::Button("Borderless"))
		Epoch::Application::get().getWindow().setWindowMode(Epoch::WindowMode::BORDERLESS);
	if (ImGui::Button("Fullscreen"))
		Epoch::Application::get().getWindow().setWindowMode(Epoch::WindowMode::FULL_SCREEN);
	ImGui::End();
}

// --------------- Example Game -----------------

Sandbox::Sandbox()
{
	pushLayer(new SandboxLayer());
}

Sandbox::~Sandbox()
{
}

// --------------- Client -----------------------

Epoch::Application* Epoch::create_application()
{
	return new Sandbox();
}
