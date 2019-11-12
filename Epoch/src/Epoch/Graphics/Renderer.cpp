#include "pch.h"
#include "Epoch/Graphics/Renderer.h"

#include "Epoch/Platform/OpenGL/OpenGLShader.h"

namespace Epoch {

	Scope<Renderer::SceneData> Renderer::cm_SceneData = create_scope<Renderer::SceneData>();

	void Renderer::init()
	{
		RendererCommand::init();
	}

	void Renderer::onWindowResized(uint32_t width, uint32_t height)
	{
		RendererCommand::setViewPort(0, 0, width, height);
	}
	
	void Renderer::beginScene(OrthographicCamera& camera)
	{
		cm_SceneData->ViewProjectionMatrix = camera.getViewProjectionMarix();
	}

	void Renderer::endScene()
	{
	}

	void Renderer::submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_ViewProjection", cm_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->uploadUniformMat4("u_Transform", transform);

		vertexArray->bind();
		RendererCommand::drawIndexed(vertexArray);
	}

}