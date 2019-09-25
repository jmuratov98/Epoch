#pragma once

#include "Epoch/Graphics/RendererCommand.h"

#include "Epoch/Graphics/Shader.h"
#include "Epoch/Graphics/OrthographicCamera.h"

namespace Epoch {

	class Renderer
	{
	public:
		static void init();

		static void beginScene(OrthographicCamera& camera);
		static void endScene();

		static void submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }
	
	private:
		struct SceneData 
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* cm_SceneData;
	};


}