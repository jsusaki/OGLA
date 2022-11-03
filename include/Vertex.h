#pragma once

#include "Type.h"

// TODO: What is the standard vertex design? 
// position, normal, tangents, uv;
struct Vertex 
{
    vf3 position;
    vf2 texture;
    vf3 col;
    //vf3 normal;
    //vf2 uv;
};
