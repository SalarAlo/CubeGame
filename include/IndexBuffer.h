#pragma once

class IndexBuffer {
public:
    void Bind();
    void Unbind();
    void Init();

private:
    unsigned int m_BufferId;
    bool m_Initiliased;
    bool m_Bound;
}
