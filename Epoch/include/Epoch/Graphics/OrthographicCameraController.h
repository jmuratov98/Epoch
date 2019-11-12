#pragma once

#include "Epoch/Graphics/OrthographicCamera.h"

#include "Epoch/Core/Timestep.h"

#include "Epoch/Events/ApplicationEvents.h"
#include "Epoch/Events/MouseEvents.h"

namespace Epoch {

	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void onUpdate(Timestep ts);
		void onEvent(Event& e);

		// Getters
		OrthographicCamera& getCamera() { return m_Camera; }
		const OrthographicCamera& getCamera() const { return m_Camera; }

	private:
		bool onMouseScrolled(MouseScrolledEvent& e);
		bool onWindowResized(WindowResizedEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel;
		OrthographicCamera m_Camera;

		bool m_IsRotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraMoveSpeed = 5.0f;
		float m_CameraRotation = 0.0f;
		float m_CameraRotationSpeed = 180.0f;
	};

}