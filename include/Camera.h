#pragma once

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

class Camera {
public:
        Camera(float fov, float ar, glm::vec3 position);

        inline const glm::mat4& GetView() const { return m_ViewMx; }
        inline const glm::mat4& GetProjection() const { return m_ProjectionMx; }

        inline void CalculateView();
        inline void CalculateProjection();

private:
        float m_Fov { };
        float m_Ar { };

        glm::vec3 m_Position {};
        glm::vec3 m_Right {};
        glm::vec3 m_Forward {};
        glm::vec3 m_Up {};

        glm::mat4 m_ProjectionMx {};
        glm::mat4 m_ViewMx {};
};
