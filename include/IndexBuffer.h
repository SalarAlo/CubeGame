#pragma once

#include <cstddef>

class IndexBuffer {
public:
    	void Bind();
	void Unbind();
	void Init();
        void FillData(const unsigned int indices[], std::size_t size);

        inline bool IsBound() const { return m_Bound; }
        inline unsigned int GetElementCount() const { return m_ElementCount; }
        
        ~IndexBuffer();

private:
	unsigned int m_BufferId;
        unsigned int m_ElementCount;
	bool m_Initiliased;
	bool m_Bound;
};
