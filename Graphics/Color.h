#pragma once

#include <glm/glm.hpp>
#include <algorithm>

namespace gr
{

class Color
{
public:
   Color(float _r = 0.f, float _g = 0.f, float _b = 0.f, float _a = 255.f);
   Color(glm::vec4 _color);

   glm::vec4 asNormalizedVec4() const { return m_color; }
   glm::vec4 asVec4() const { return m_color * 255.f; }

private:
   glm::vec4 m_color;

public:
   static const Color White;
   static const Color Black;
   static const Color Red;
   static const Color Green;
   static const Color Blue;
   static const Color Transparent;
};

} // ns
