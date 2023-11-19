#include "THPrecomp.h"
#include "Camera.h"

#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"

namespace TopHat
{
	Camera::Camera() : m_ProjectionMatrix(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f)), m_Position(glm::vec2(0, 0)), m_Rotation(0)
	{
		RecalculateProjectionViewMat();
	}

	Camera::Camera(float left, float right, float bottom, float top, float close, float end) : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, close, end)), m_Position(glm::vec2(0, 0)), m_Rotation(0)
	{
		RecalculateProjectionViewMat();
	}

	Camera::Camera(float left, float right, float bottom, float top, float close, float end, glm::vec2& position, float rotation ) : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, close, end)), m_Position(position), m_Rotation(rotation) 
	{
		RecalculateProjectionViewMat();
	}


	void Camera::RecalculateProjectionViewMat()
	{
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 0)) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1)); 
		m_ViewMatrix = glm::inverse(trans);
		m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::SetPosition(const glm::vec2& pos)
	{
		 m_Position = pos;
		 RecalculateProjectionViewMat();
	}

	void Camera::SetRotation(const float rot)
	{
		 m_Rotation = rot;
		 RecalculateProjectionViewMat();
	}

}
