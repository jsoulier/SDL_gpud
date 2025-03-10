
vec4 get_color(const uint color_)
{
    vec4 color;
    color.r = float((color_ >> 24) & 0xFF) / 255.0f;
    color.g = float((color_ >> 16) & 0xFF) / 255.0f;
    color.b = float((color_ >>  8) & 0xFF) / 255.0f;
    color.a = float((color_ >>  0) & 0xFF) / 255.0f;
    return color;
}