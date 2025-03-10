#version 450

#include "color.glsl"

layout(location = 0) in flat uint i_color;
layout(location = 0) out vec4 o_color;

void main()
{
    o_color = get_color(i_color);
}