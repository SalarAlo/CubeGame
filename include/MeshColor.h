#pragma once

#include <glm/glm.hpp>


class MeshColor {
public:
        enum Type {
                Red,
                Green,
                Blue,
                Yellow,
                Cyan,
                Magenta,
                White,
                Black,
                Gray,
                Orange,
                Purple,
                Brown,
        };
public:
        MeshColor(Type type);

        Type GetColor() const { return m_Color; };

        glm::vec3 GetRgb() const;
        static glm::vec3 GetRgb(Type type);

private:
        Type m_Color;
};
