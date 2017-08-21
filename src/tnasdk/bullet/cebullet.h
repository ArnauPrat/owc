
#ifndef _TNASDK_CEBULLET_H
#define _TNASDK_CEBULLET_H

#include <common.h>
#include <collision_engine.h>
#include <bbox.h>

class btCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btCollisionWorld;
class btCollisionObject;
class btBoxShape;

namespace tnasdk {

class CbBBox : public BBox {
public:
  CbBBox() = delete;
  CbBBox( btCollisionWorld* world );
  virtual ~CbBBox();

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////

  bool_t transform(Transform transform) override;

  Transform transform() const override;

  void position( Vector2f position ) override;

  Vector2f position() const override;
  
  void rotation( float_t angle ) override;

  float_t rotation() const override;

  void width( float_t width ) override;

  float_t width() override;

  void height( float_t height ) override;

  float_t height() override;

  void enable() override;

  void disable() override;

private:
  btCollisionWorld*   m_world = nullptr;
  btBoxShape*         m_shape = nullptr;
  btCollisionObject*  m_cobject = nullptr;
  bool_t              m_enabled = false;
  
};

class Cebullet : public CollisionEngine {
public:
  Cebullet (uint32_t width, uint32_t height);
  virtual ~Cebullet ();

  BBox* create_bbox() override;

  void destroy_bbox( BBox* bbox ) override;

private:
  btCollisionConfiguration* bt_collision_configuration;
  btCollisionDispatcher*    bt_dispatcher;
  btBroadphaseInterface*    bt_broadphase;
  btCollisionWorld*         bt_collision_world;
};

} /* tnasdk */ 

#endif /* _TNASDK_CEBULLET_H */
