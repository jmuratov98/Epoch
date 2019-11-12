#pragma once

#include <Epoch.h>

class Sandbox2D : public Epoch::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void onAttach() override;
	virtual void onDetach() override;

	virtual void onUpdate(Epoch::Timestep ts) override;
	virtual void onEvent(Epoch::Event& e) override;
	virtual void onImGuiRender() override;

private:
	Epoch::OrthographicCameraController m_CameraController;
	
	// Temp
	Epoch::Ref<Epoch::VertexArray> m_FlatSquareVAO;
	Epoch::Ref<Epoch::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2, 0.3, 0.8, 1.0f };

};