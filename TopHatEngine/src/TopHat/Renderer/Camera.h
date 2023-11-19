#pragma once

#include "glm.hpp"

namespace TopHat
{
	class Camera
	{
	public:
		Camera();
		Camera(float left, float right, float bottom, float top, float close, float end);
		Camera(float left, float right, float bottom, float top, float close, float end, glm::vec2& position, float rotation );
		 
		void SetPosition(const glm::vec2& pos);
		void SetRotation(const float rot);
	 

		const inline glm::vec2& GetPosition() { return m_Position; }
		inline float  GetRotation() { return m_Rotation; }
	 
		const inline glm::mat4& GetProjectionViewMatrix() { return m_ProjectionViewMatrix; }
	private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ProjectionViewMatrix;
		glm::vec2 m_Position;
		float m_Rotation;
		 
		void RecalculateProjectionViewMat();
	};
}
