/*
	Describes the vertex data
	Ideally, this should be done using reflections to describe the Vertex struct.
*/
#pragma once

#include <glad/glad.h>
#include <vector>

#include "Type.h"
#include "Vertex.h"

// Do we need all this types?
enum VertexAttributeType
{
	BYTE = GL_BYTE,
	UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
	SHORT = GL_SHORT,
	UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
	INT = GL_INT,
	UNSIGNED_INT = GL_UNSIGNED_INT,
	FLOAT = GL_FLOAT,
	DOUBLE = GL_DOUBLE
};

struct VertexAttribute
{
	u32 count;
	VertexAttributeType type;
	u32 offset;
};

class VertexData
{
public:
	VertexData();

public:
	template<typename T>
	void Add() {}
public:
	u32 GetStride() const;
	u32 GetOffset(const u32 index) const;
	u32 GetType(const u32 index) const;
	u32 GetCount(const u32 index) const;
	u32 Size() const;

private:
	std::vector<VertexAttribute> m_attributes;
	u32 m_stride = 0;
};

// template specializations
template<>
inline void VertexData::Add<vf2>()
{
	m_attributes.push_back({ 2, FLOAT, sizeof(vf2) });
	m_stride += sizeof(vf2);
}

template<>
inline void VertexData::Add<vf3>()
{
	m_attributes.push_back({ 3, FLOAT, sizeof(vf3) });
	m_stride += sizeof(vf3);
}

template<>
inline void VertexData::Add<vf4>()
{
	m_attributes.push_back({ 4, FLOAT, sizeof(vf4) });
	m_stride += sizeof(vf4);
}