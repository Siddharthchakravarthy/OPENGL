#pragma once
class IndexBuffer
{
private:
	unsigned int m_RendererID_of_ind_buff;
	unsigned int m_count;
public:
	IndexBuffer(const unsigned int *data, unsigned int count);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;
	unsigned int GetCount();
};

