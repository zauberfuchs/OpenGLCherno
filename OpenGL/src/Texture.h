#pragma once

#include "Renderer.h"

class Texture
{

private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_width, m_Height, m_BPP;

public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const; // optionaler parameter wenn man nichts eingibt = 0 /man hat begrenzte texture slots
	void UnBind() const;

	inline int GetWidth() const { return m_width; }
	inline int GetHeigth() const { return m_Height; }
};
