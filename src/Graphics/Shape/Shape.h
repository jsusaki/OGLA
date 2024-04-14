#pragma once

#include "../Mesh/Mesh.h"

class Triangle : public Mesh
{
public:
	Triangle()
	{
		m_vertices = {
			{{-0.5f,-0.5f,0.0f },{0.0f, 0.0f, 1.0f},{ 0.0f, 0.0f },{0.0f, 0.0f, 1.0f}}, // bottom left
			{{0.5f,-0.5f, 0.0f },{0.0f, 0.0f, 1.0f},{ 1.0f, 0.0f },{0.0f, 1.0f, 0.0f}}, // bottom right
			{{0.0f, 0.5f, 0.0f },{0.0f, 0.0f, 1.0f},{ 0.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, // top 
		};

		m_indices = {
			0, 1, 2, // triangle
		};

		m_def.Add<vf3>(); // position
		m_def.Add<vf3>(); // normal
		m_def.Add<vf2>(); // texture
		m_def.Add<vf3>(); // color

		m_vbo = std::make_shared<VertexBuffer>(m_vertices, STATIC_DRAW);
		m_ibo = std::make_shared<IndexBuffer>(m_indices, STATIC_DRAW);
		m_vao = std::make_shared<VertexArray>(*m_vbo, *m_ibo, m_def);
	}
};

class Quad : public Mesh
{
public:
	Quad()
	{
		m_vertices = {
			{{ 0.5f, 0.5f, 0.0f },{0.0f, 0.0f, 1.0f},{ 1.0f, 1.0f },{1.0f, 0.0f, 0.0f}},   // top right
			{{ 0.5f,-0.5f, 0.0f },{0.0f, 0.0f, 1.0f},{ 1.0f, 0.0f },{0.0f, 1.0f, 0.0f}},   // bottom right
			{{-0.5f,-0.5f, 0.0f },{0.0f, 0.0f, 1.0f},{ 0.0f, 0.0f },{0.0f, 0.0f, 1.0f}},   // bottom left
			{{-0.5f, 0.5f, 0.0f },{0.0f, 0.0f, 1.0f},{ 0.0f, 1.0f },{1.0f, 0.0f, 0.0f}},   // top left
		};

		m_indices = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		m_def.Add<vf3>(); // position
		m_def.Add<vf3>(); // normal
		m_def.Add<vf2>(); // texture
		m_def.Add<vf3>(); // color

		m_vbo = std::make_shared<VertexBuffer>(m_vertices, STATIC_DRAW);
		m_ibo = std::make_shared<IndexBuffer>(m_indices, STATIC_DRAW);
		m_vao = std::make_shared<VertexArray>(*m_vbo, *m_ibo, m_def);
	}
};

class Cube : public Mesh
{
public:
	Cube()
	{
		// Unit cube      
		// A cube has 6 sides and each side has 4 vertices, therefore, the total number
		// of vertices is 24 (6 sides * 4 verts), and 72 floats in the vertex array
		// since each vertex has 3 components (x,y,z) (= 24 * 3)
		//    v6----- v5  
		//   /|      /|   
		//  v1------v0|   
		//  | |     | |   
		//  | v7----|-v4  
		//  |/      |/    
		//  v2------v3   

		// Create Cube Vertices
		m_vertices = {
			// Front
			{{ 0.5f, 0.5f, 0.5f},{0.0f, 0.0f, 1.0f},{ 1.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v0
			{{-0.5f, 0.5f, 0.5f},{0.0f, 0.0f, 1.0f},{ 0.0f, 0.0f },{0.0f, 1.0f, 0.0f}}, //v1
			{{-0.5f,-0.5f, 0.5f},{0.0f, 0.0f, 1.0f},{ 0.0f, 1.0f },{0.0f, 0.0f, 1.0f}}, //v2
			{{ 0.5f,-0.5f, 0.5f},{0.0f, 0.0f, 1.0f},{ 1.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v3
			// Right
			{{ 0.5f, 0.5f, 0.5f},{1.0f, 0.0f, 0.0f},{ 0.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v0
			{{ 0.5f,-0.5f, 0.5f},{1.0f, 0.0f, 0.0f},{ 0.0f, 1.0f },{0.0f, 1.0f, 0.0f}}, //v3
			{{ 0.5f,-0.5f,-0.5f},{1.0f, 0.0f, 0.0f},{ 1.0f, 1.0f },{0.0f, 0.0f, 1.0f}}, //v4
			{{ 0.5f, 0.5f,-0.5f},{1.0f, 0.0f, 0.0f},{ 1.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v5
			// Top
			{{ 0.5f, 0.5f, 0.5f},{0.0f, 1.0f, 0.0f},{ 1.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v0   
			{{ 0.5f, 0.5f,-0.5f},{0.0f, 1.0f, 0.0f},{ 1.0f, 0.0f },{0.0f, 1.0f, 0.0f}}, //v5
			{{-0.5f, 0.5f,-0.5f},{0.0f, 1.0f, 0.0f},{ 0.0f, 0.0f },{0.0f, 0.0f, 1.0f}}, //v6
			{{-0.5f, 0.5f, 0.5f},{0.0f, 1.0f, 0.0f},{ 0.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v1
			// Left
			{{-0.5f, 0.5f, 0.5f},{-1.0f, 0.0f, 0.0f},{ 1.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v1  
			{{-0.5f, 0.5f,-0.5f},{-1.0f, 0.0f, 0.0f},{ 0.0f, 0.0f },{0.0f, 1.0f, 0.0f}}, //v6
			{{-0.5f,-0.5f,-0.5f},{-1.0f, 0.0f, 0.0f},{ 0.0f, 1.0f },{0.0f, 0.0f, 1.0f}}, //v7
			{{-0.5f,-0.5f, 0.5f},{-1.0f, 0.0f, 0.0f},{ 1.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v2
			// Bottom
			{{-0.5f,-0.5f,-0.5f},{0.0f,-1.0f, 0.0f},{ 0.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v7 
			{{ 0.5f,-0.5f,-0.5f},{0.0f,-1.0f, 0.0f},{ 1.0f, 1.0f },{0.0f, 1.0f, 0.0f}}, //v4
			{{ 0.5f,-0.5f, 0.5f},{0.0f,-1.0f, 0.0f},{ 1.0f, 0.0f },{0.0f, 0.0f, 1.0f}}, //v3
			{{-0.5f,-0.5f, 0.5f},{0.0f,-1.0f, 0.0f},{ 0.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v2
			// Back
			{{ 0.5f,-0.5f,-0.5f},{0.0f, 0.0f,-1.0f},{ 0.0f, 1.0f },{1.0f, 0.0f, 0.0f}}, //v4 
			{{-0.5f,-0.5f,-0.5f},{0.0f, 0.0f,-1.0f},{ 1.0f, 1.0f },{0.0f, 1.0f, 0.0f}}, //v7
			{{-0.5f, 0.5f,-0.5f},{0.0f, 0.0f,-1.0f},{ 1.0f, 0.0f },{0.0f, 0.0f, 1.0f}}, //v6
			{{ 0.5f, 0.5f,-0.5f},{0.0f, 0.0f,-1.0f},{ 0.0f, 0.0f },{1.0f, 0.0f, 0.0f}}, //v5
		};
		// Create Cube Indices
		m_indices = {
			// Front
			0, 1, 2,  //v0-v1-v2 
			2, 3, 0,  //v2-v3-v0 
			// right
			4, 5, 6,  //v0-v3-v4 
			6, 7, 4,  //v4-v5-v0 
			// top
			8, 9,10,  //v0-v5-v6   
			10,11,8,  //v6-v1-v0
			// left
			12,13,14, //v1-v6-v7 
			14,15,12, //v7-v2-v1
			// bottom
			16,17,18, //v7-v4-v3
			18,19,16, //v3-v2-v7
			// back
			20,21,22, //v4-v7-v6  
			22,23,20  //v6-v5-v4
		};

		// Create Vertex Buffer Definition
		m_def.Add<vf3>(); // position
		m_def.Add<vf3>(); // normal
		m_def.Add<vf2>(); // texture
		m_def.Add<vf3>(); // color

		m_vbo = std::make_shared<VertexBuffer>(m_vertices, STATIC_DRAW);
		m_ibo = std::make_shared<IndexBuffer>(m_indices, STATIC_DRAW);
		m_vao = std::make_shared<VertexArray>(*m_vbo, *m_ibo, m_def);
	}
};