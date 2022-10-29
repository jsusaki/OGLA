#pragma once

#include "Type.h"

// TODO: What is the standard vertex design? 
// position, normal, tangents, uv;
struct Vertex 
{
    vf3 position;
    color col;
    vf2 texture;

    //vf3 normal;
    //vf3 tangent;
    //vf2 uv;
};
