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
	m_BlueSquareVAO.reset(Epoch::VertexArray::create());

	float square_vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	std::shared_ptr<Epoch::VertexBuffer> blueSquareVertexBuffer;
	blueSquareVertexBuffer.reset(Epoch::VertexBuffer::create(square_vertices, sizeof(square_vertices)));

	blueSquareVertexBuffer->setBufferLayout({
		{ Epoch::ShaderDataType::Float3, "a_Position" },
	});
	m_BlueSquareVAO->addVertexBuffer(blueSquareVertexBuffer);

	uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<Epoch::IndexBuffer> blueSquareIndexBuffer;
	blueSquareIndexBuffer.reset(Epoch::IndexBuffer::create(square_indices, sizeof(square_indices) / sizeof(uint32_t)));
	m_BlueSquareVAO->setIndexBuffer(blueSquareIndexBuffer);

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

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

	m_FlatColorShader.reset(Epoch::Shader::create(flatShaderVertexSrc, flatShaderFragmentSrc));
}

void SandboxLayer::onUpdate(Epoch::Timestep ts)
{
	m_CameraController.onUpdate(ts);

	Epoch::RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Epoch::RendererCommand::clear();

	Epoch::Renderer::beginScene(m_CameraController.getCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Epoch::Renderer::submit(m_FlatColorShader, m_BlueSquareVAO, transform);
		}
	}

	Epoch::Renderer::submit(m_FlatColorShader, m_BlueSquareVAO);

	Epoch::Renderer::endScene();
}

void SandboxLayer::onEvent(Epoch::Event& e)
{
	m_CameraController.onEvent(e);
}

void SandboxLayer::onImGuiRender()
{
	ImGui::Begin("Text");
	ImGui::Text("Hello, World");
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
