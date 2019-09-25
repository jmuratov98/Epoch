#include "pch.h"
#include "Epoch/Graphics/Renderer.h"

#include "Epoch/Platform/OpenGL/OpenGLShader.h"

namespace Epoch {

	Renderer::SceneData* Renderer::cm_SceneData = new Renderer::SceneData;

	void Renderer::init()
	{
		RendererCommand::init();
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