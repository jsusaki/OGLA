#pragma once
#include <iostream>
#include <string>

#include <stb/stb_image.h>
#include <glad/glad.h>

#include "../../Core/Common.h"

// review these formats
enum Format
{
	RGB  = GL_RGB,
	RGBA = GL_RGBA,
};

enum Wrapping
{
	CLAMP_EDGE		= GL_CLAMP_TO_EDGE,
	CLAMP_BORDER    = GL_CLAMP_TO_BORDER,
	REPEAT          = GL_REPEAT,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT
};

enum Filter
{
	NEAREST                = GL_NEAREST,
	LINEAR                 = GL_LINEAR,
	NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	LINEAR_MIPMAP_NEAREST  = GL_LINEAR_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR  = GL_NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_LINEAR   = GL_LINEAR_MIPMAP_LINEAR
};

class Texture
{
public:
	Texture();
	//Texture(const std::string& filepath, bool vertical_flip = false);
	Texture(const std::string& filepath, const std::string& type, bool vertical_flip = false);
	~Texture();
		
public:
	void Bind();
	void Unbind();
	u32 GetID();

	// TODO: place holder until material system
	std::string GetType();
	std::string m_type;
	std::string GetPath();
	std::string m_filepath;

public:
	u8* LoadFromFile(const std::string& filepath, bool vertical_flip);
	void Create(u32 width, u32 height, const u8* data, const bool filtered = true, const bool clamped = false);

private:
	u32 m_texture_id;
	u32 m_width;
	u32 m_height;
	u32 m_channel;
	u8  m_mipmap = true;
	u8* m_buffer = nullptr;
	s32 m_clamp;
	s32 m_filter;
	s32 m_format;
};