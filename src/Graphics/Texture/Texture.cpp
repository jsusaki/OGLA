#include "Texture.h"


Texture::Texture()
{

}
/*
Texture::Texture(const std::string& filepath, bool vertical_flip)
{
    m_buffer = LoadFromFile(filepath, vertical_flip);
    Create(m_width, m_height, m_buffer);
    stbi_image_free(m_buffer);
}
*/
Texture::Texture(const std::string& filepath, const std::string& type, bool vertical_flip)
{
	m_type = type;
    m_filepath = filepath;
    m_buffer = LoadFromFile(filepath, vertical_flip);
	Create(m_width, m_height, m_buffer);
	stbi_image_free(m_buffer);
}
    
Texture::~Texture()
{
    glDeleteTextures(1, &m_texture_id);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

u32 Texture::GetID()
{
    return m_texture_id;
}

std::string Texture::GetType()
{
    return m_type;
}

std::string Texture::GetPath()
{
    return m_filepath;
}

void Texture::Create(u32 width, u32 height, const u8* data, const bool filtered, const bool clamped)
{    
    // Create Texture
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    // Set Image Format
    switch (m_channel)
    {
    case 1: m_format = GL_ALPHA;     break;
    case 2: m_format = GL_LUMINANCE; break;
    case 3: m_format = GL_RGB;       break;
    case 4: m_format = GL_RGBA;      break;
    }
    
    // Set Texture Filtering Parameter
    if (filtered) m_filter = GL_LINEAR;
    else          m_filter = GL_NEAREST;

    // Set Texture Wrap Parameter
    if (clamped) m_clamp = GL_CLAMP;
    else         m_clamp = GL_REPEAT;

    // Apply Texture Filtering Parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter);

    // Apply Texture Wrap Parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_clamp);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_clamp);

    // Generate Texture
    glTexImage2D(GL_TEXTURE_2D, 0, m_format, width, height, 0, m_format, GL_UNSIGNED_BYTE, data);

    if (m_mipmap) glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

u8* Texture::LoadFromFile(const std::string& filepath, bool vertical_flip)
{
    stbi_set_flip_vertically_on_load(vertical_flip);
    int w = 0, h = 0, ch = 0;
    const char* path = filepath.c_str();
    u8* data = stbi_load(path, &w, &h, &ch, 0);
    if (data == nullptr)
        std::cout << "Failed to load texture " << filepath << "\n";

    m_width   = w;
    m_height  = h;
    m_channel = ch;

    return data;
}
