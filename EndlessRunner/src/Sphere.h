#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>

#include "Graphics/ResMgr.h"
#include "Collideable.h"
#include "Graphics/Sprite.h"
#include "Hero.h"
#include "Graphics/Renderable.h"
#include "Graphics/Renderer.h"

#define DECLARE_SPHERE_STATE_METHODS(stateName) \
   void stateName##_onEnter(const State); \
   void stateName##_onExit(const State); \
   void stateName##_update(float);

class Sphere
      : public Collideable,
        public fhl::Renderable
{
public:
   enum State
   {
      State_Idle,
      State_Thrown,
      State_Return,

      StateCount
   };

public:
   explicit Sphere(Hero* _owner);

   std::shared_ptr<Collider> getCollider(CollideableObjType _objType) override;
   void onCollision(CollideableObjType _objType) override { }

   void render(const fhl::RenderConf &) const override;
   void update(float dt);
   void changeState(const State _newState);

   State getState() { return m_currentState; }
   fhl::Vec2f getPosition() { return m_sprite.getPosition(); }

   void setDirection(fhl::Vec2f _dir) { m_direction = _dir; }

private:
   DECLARE_SPHERE_STATE_METHODS(Idle)
   DECLARE_SPHERE_STATE_METHODS(Thrown)
   DECLARE_SPHERE_STATE_METHODS(Return)

   void (Sphere:: *m_onEnter[StateCount])(const State);
   void (Sphere:: *m_onExit[StateCount])(const State);
   void (Sphere:: *m_update[StateCount])(float);

private:
   fhl::Sprite m_sprite;

   fhl::Vec2f m_direction;
   float m_startVelociy;
   float m_velocity;
   Hero* m_owner;
   State m_currentState;
};

#endif // SPHERE_H
