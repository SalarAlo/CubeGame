#pragma once

#include <cstddef>

class IndexBuffer {
public:
    	void Bind();
	void Unbind();
	void Init();
        void FillData(unsigned int indices[], std::size_t size);

        inline bool IsBound() const { return m_Bound; }
        
        ~IndexBuffer();

private:
	unsigned int m_BufferId;
	bool m_Initiliased;
	bool m_Bound;
};
