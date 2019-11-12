#include "Sandbox/Sandbox2D.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <Epoch/Platform/OpenGL/OpenGLShader.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{ }

void Sandbox2D::onAttach()
{
	m_FlatSquareVAO = Epoch::VertexArray::create();

	float square_vertices[3 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Epoch::Ref<Epoch::VertexBuffer> squareVBO;
	squareVBO = Epoch::VertexBuffer::create(square_vertices, sizeof(square_vertices));

	squareVBO->setBufferLayout({
		{ Epoch::ShaderDataType::Float3, "a_Position" }
		});
	m_FlatSquareVAO->addVertexBuffer(squareVBO);

	uint32_t square_indices[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<Epoch::IndexBuffer> squareIBO;
	squareIBO = Epoch::IndexBuffer::create(square_indices, sizeof(square_indices) / sizeof(uint32_t));
	m_FlatSquareVAO->setIndexBuffer(squareIBO);

	m_FlatColorShader = Epoch::Shader::create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::onDetach()
{
}

void Sandbox2D::onUpdate(Epoch::Timestep ts)
{
	m_CameraController.onUpdate(ts);

	Epoch::RendererCommand::setClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Epoch::RendererCommand::clear();

	Epoch::Renderer::beginScene(m_CameraController.getCamera());

	m_FlatColorShader->bind();
	std::dynamic_pointer_cast<Epoch::OpenGLShader>(m_FlatColorShader)->uploadUniformFloat4("u_Color", m_SquareColor);

	Epoch::Renderer::submit(m_FlatColorShader, m_FlatSquareVAO, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Epoch::Renderer::endScene();
}

void Sandbox2D::onEvent(Epoch::Event& e)
{
	m_CameraController.onEvent(e);
}

void Sandbox2D::onImGuiRender()
{
	ImGui::Begin("Color");
	ImGui::ColorEdit4("Square Color", value_ptr(m_SquareColor));
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