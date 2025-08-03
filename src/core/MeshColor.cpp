#include "MeshColor.h"

MeshColor::MeshColor(MeshColor::Type type) : m_Color(type) {}

glm::vec3 MeshColor::GetRgb() const {
        switch (m_Color) {
        case Red:     return {1.0f, 0.0f, 0.0f};
        case Green:   return {0.0f, 1.0f, 0.0f};
        case Blue:    return {0.0f, 0.0f, 1.0f};
        case Yellow:  return {1.0f, 1.0f, 0.0f};
        case Cyan:    return {0.0f, 1.0f, 1.0f};
        case Magenta: return {1.0f, 0.0f, 1.0f};
        case White:   return {1.0f, 1.0f, 1.0f};
        case Black:   return {0.0f, 0.0f, 0.0f};
        case Gray:    return {0.5f, 0.5f, 0.5f};
        case Orange:  return {1.0f, 0.5f, 0.0f};
        case Purple:  return {0.5f, 0.0f, 0.5f};
        case Brown:   return {0.6f, 0.3f, 0.1f};
        default:      return MeshColor::GetRgb(MeshColor::Magenta);  
        }
}

glm::vec3 MeshColor::GetRgb(MeshColor::Type type) {
        MeshColor color(type);
        return color.GetRgb();
}
