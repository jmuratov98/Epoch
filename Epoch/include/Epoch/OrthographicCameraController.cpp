#include "pch.h"
#include "OrthographicCameraController.h"

#include "Epoch/Input.h"
#include "Epoch/KeyCodes.h"

namespace Epoch {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: m_ZoomLevel(1.0f), m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_IsRotation(rotation)
	{
	}

	void OrthographicCameraController::onUpdate(Timestep ts)
	{
		if (Input::isKeyPressed(EGE_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Input::isKeyPressed(EGE_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Input::isKeyPressed(EGE_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Input::isKeyPressed(EGE_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (m_IsRotation)
		{
			if (Input::isKeyPressed(EGE_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * ts;
			if (Input::isKeyPressed(EGE_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * ts;

			m_Camera.setRotation(m_CameraRotation);
		}

		m_Camera.setPosition(m_CameraPosition);

		m_CameraMoveSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<MouseScrolledEvent>(EGE_BIND_EVENT_FN(OrthographicCameraController::onMouseScrolled));
		dispatcher.dispatch<WindowResizedEvent>(EGE_BIND_EVENT_FN(OrthographicCameraController::onWindowResized));
	}

	bool OrthographicCameraController::onMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.getYScrolled() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::onWindowResized(WindowResizedEvent& e)
	{
		m_AspectRatio = (float)e.getWidth() / (float)e.getHeight();
		m_Camera.setProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}