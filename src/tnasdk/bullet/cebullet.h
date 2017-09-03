
#ifndef _TNASDK_CEBULLET_H
#define _TNASDK_CEBULLET_H

#include <common.h>
#include <collision_engine.h>
#include <vector>
#include <bbox.h>

class btCollisionConfiguration;
class btCollisionDispatcher;
class btBroadphaseInterface;
class btCollisionWorld;
class btCollisionObject;
class btBoxShape;

class BFObject;

namespace tnasdk {

class CbBBox : public BBox {
public:
  CbBBox() = delete;
  CbBBox( BFObject* user_data, btCollisionWorld* world );
  virtual ~CbBBox();

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////

  void transform(Vector2f position, float_t rotation) override;

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

  BBox* create_bbox( BFObject* user_data ) override;

  void destroy_bbox( BBox* bbox ) override;

  std::vector<Collision> detect_collisions() override;

  std::vector<BBox*>  bboxes() override;

private:
  std::vector<BBox*>        m_bboxes;
  btCollisionConfiguration* m_configuration;
  btCollisionDispatcher*    m_dispatcher;
  btBroadphaseInterface*    m_broadphase;
  btCollisionWorld*         m_world;
};

} /* tnasdk */ 

#endif /* _TNASDK_CEBULLET_H */
