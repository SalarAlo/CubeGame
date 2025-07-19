#pragma once

#include <cstddef>  

class VertexBuffer {
public:
        void Init();
        void Bind();
        void Unbind();
        void SetData(float vertices[], std::size_t size);

        inline bool IsBound() const { return m_Bound; } 

        ~VertexBuffer();

private:
        unsigned int m_BufferId {};
        bool m_Bound {}; 
        bool m_Initialised {};
};
