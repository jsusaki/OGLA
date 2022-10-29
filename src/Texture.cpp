#include "Texture.h"


Texture::Texture()
{

}

Texture::Texture(const std::string& filepath)
{
    m_buffer = LoadFromFile(filepath);

    Generate(m_width, m_height, m_buffer);

    stbi_image_free(m_buffer);
}
    
Texture::~Texture()
{
    glDeleteTextures(1, &m_TextureID);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

u32 Texture::GetID()
{
    return m_TextureID;
}

void Texture::Generate(u32 width, u32 height, const u8* data)
{    
    // Create Texture
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);

    // Set Image Format
    s32 format = 0;
    switch (m_channel)
    {
    case 1: format = GL_ALPHA;     break;
    case 2: format = GL_LUMINANCE; break;
    case 3: format = GL_RGB;       break;
    case 4: format = GL_RGBA;      break;
    }
    
    // Make parameter reconfigurable
    // Set Texture Wrap Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set Texture Filtering Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Generate Texture
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

    if (m_bMipMap)
        glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

u8* Texture::LoadFromFile(const std::string& filepath)
{
    stbi_set_flip_vertically_on_load(false);
    int w = 0, h = 0, ch = 0;
    const char* path = filepath.c_str();
    u8* data = stbi_load(path, &w, &h, &ch, 0);
    if (data == nullptr)
        std::cout << "Failed to load texture " << filepath << "\n";

    m_width = w;
    m_height = h;
    m_channel = ch;

    return data;
}
