#include "VertexData.h"

VertexData::VertexData()
{

}

u32 VertexData::GetStride() const
{
	return m_stride;
}

u32 VertexData::GetOffset(const u32 index) const
{
	u32 total_offset = 0;
	for (u32 i = 0; i < index; i++)
		total_offset += m_attributes[i].offset;
	return total_offset;
}

u32 VertexData::GetType(const u32 index) const
{
	return m_attributes[index].type;
}

u32 VertexData::GetCount(const u32 index) const
{
	return m_attributes[index].count;
}

u32 VertexData::Size() const
{
	return m_attributes.size();
}