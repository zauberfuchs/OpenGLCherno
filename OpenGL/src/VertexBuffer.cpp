#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{


	glGenBuffers(1, &m_RendererID); // in buffer wird die BufferId geschrieben die der buffer bekommt.
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); // ich binde mein buffer mit dem GL_ARRAY_BUFFER!
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); // buffer array wird erstellt/befüllt und die daten an die GPU gesendet!
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
