#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(float fov, float ar, glm::vec3 position) :
        m_Position(position), 
        m_Fov(fov), m_Ar(ar),
        m_Forward(0, 0, 1), m_Right(1, 0, 0), m_Up(0, 1, 0)
{ 
        CalculateView();
        CalculateProjection();
};

void Camera::CalculateView() {
	m_ViewMx = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

void Camera::CalculateProjection() {
	m_ProjectionMx = glm::perspective(glm::radians(m_Fov), m_Ar, 0.1f, 1000.0f);
}
