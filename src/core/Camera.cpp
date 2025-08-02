#include "Camera.h"
#include "ShaderWriter.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void Camera::WriteToShader(ShaderWriter& shaderWriter, glm::mat4 model) {
	const std::string modelMatrixName { "u_Model" };
	const std::string viewMatrixName { "u_View" };
	const std::string projMatrixName { "u_Projection" };
	const std::string cameraPosName { "u_CameraPos" };

        shaderWriter.WriteUniformMatrix4(modelMatrixName, model);
        shaderWriter.WriteUniformMatrix4(viewMatrixName, GetView());
        shaderWriter.WriteUniformMatrix4(projMatrixName, GetProjection());
        shaderWriter.WriteUniformVec3(cameraPosName, m_Position);
        
}

void Camera::Init(float fov, float ar, glm::vec3 position, glm::vec3 forward) {
        m_Position = position;
        m_Fov = fov;
        m_Ar = ar;

        const glm::vec3 worldUp { 0, 1, 0 };

        m_Forward = forward;
        m_Right = glm::normalize(glm::cross(worldUp, forward));
        m_Up = glm::normalize(glm::cross(m_Forward, m_Right));

        CalculateView();
        CalculateProjection();
}

void Camera::CalculateView() {
	m_ViewMx = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

void Camera::CalculateProjection() {
	m_ProjectionMx = glm::perspective(glm::radians(m_Fov), m_Ar, 0.1f, 1000.0f);
}
