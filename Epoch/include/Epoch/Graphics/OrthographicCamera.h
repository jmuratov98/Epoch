#pragma once

#include <glm/glm.hpp>

namespace Epoch {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		// Getters
		const glm::vec3& getPosition() const { return m_Position; }
		float getRotation() const { return m_Rotation; }

		const glm::mat4 getProjectionMatrix() { return m_ProjectionMatrix; }
		const glm::mat4 getViewMatrix() { return m_ViewMatrix; }
		const glm::mat4 getViewProjectionMarix() { return m_VPM; }

		// Setters
		void setPosition(const glm::vec3& pos) { m_Position = pos; recalcViewProjectionMatrix(); }
		void setRotation(float rot) { m_Rotation = rot; recalcViewProjectionMatrix(); }
		void setProjection(float left, float right, float bottom, float top);

	private:
		void recalcViewProjectionMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_VPM;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}