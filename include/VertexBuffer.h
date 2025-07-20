#pragma once

#include <cstddef>  

class VertexBuffer {
public:
        void Init();
        void Bind();
        void Unbind();
        void SetData(const float vertices[], std::size_t size);

        inline bool IsBound() const { return m_Bound; } 
        inline unsigned int GetVerticesAmount() const { return m_VertexAmount; }

        ~VertexBuffer();

private:
        unsigned int m_BufferId {};
        unsigned int m_VertexAmount {};
        bool m_Bound {}; 
        bool m_Initialised {};
};
