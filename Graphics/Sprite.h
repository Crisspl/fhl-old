#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <memory>

#include "../Utility/ResMgr.h"
#include "Vao.h"
#include "Texture.h"
#include "Shader.h"
#include "Color.h"
#include "Configurator.h"
#include "Transformable.h"
#include "Sizeable.h"
#include "Drawable.h"
#include "Litable.h"

namespace ut { class Rect; class OrientedRect; }

namespace gr
{

class Sprite
      : public Transformable,
        public Sizeable,
        public Drawable,
        public Litable
{
public:
   Sprite();
   explicit Sprite(Texture& _tex);

private:
   enum class AttLoc : GLuint
   {
      Position = 0,
      TexCoords
   };

public:
   const Texture& getTexture() const { return *m_ptexture; }

   void setShader(Shader& _shader = ut::ResMgr::getShader(SHADER_NAME)) override;
   void setTexture(Texture& _tex);
   void setTextureRect(ut::Rect _rect, bool _changeSize = false);
   void setColor(const Color _color) { m_color = _color; }
   void setLight(const Light& _light) override;
   void draw() const override;
   ut::Rect getAABB() const;
   ut::OrientedRect getOBB() const;

private:
   void initTexCoordsArray();
   void uploadTexCoordsArray();
   void setUp();

private:
   std::shared_ptr<Vao> m_vao;

   Texture* m_ptexture;
   Color m_color;
   glm::vec2 m_texCoordsArray[4];
   bool m_usingOriginalShader;

   static bool LIGHT_SHADER_LOADED;

   constexpr static const char* SHADER_NAME = "spriteShader";
   constexpr static const char* VSHADER_PATH = "Graphics/Shaders/sprite_vs.glsl";
   constexpr static const char* FSHADER_PATH = "Graphics/Shaders/sprite_fs.glsl";

   constexpr static const char* LIGHT_SHADER_NAME = "spriteLightShader";
   constexpr static const char* LIGHT_VSHADER_PATH = "Graphics/Shaders/spriteLight_vs.glsl";
   constexpr static const char* LIGHT_FSHADER_PATH = "Graphics/Shaders/spriteLight_fs.glsl";
};

} // ns