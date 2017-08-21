

#include <btBulletDynamicsCommon.h>
#include <cebullet.h>

namespace tnasdk {

CbBBox::CbBBox(btCollisionWorld* world ) : 
  m_world(world) {
  m_cobject = new btCollisionObject();
  m_shape = new btBoxShape(btVector3{0.5f, 0.5f, 0.5f});
  m_cobject->setCollisionShape(m_shape);
  m_cobject->getWorldTransform().setOrigin(btVector3{0.0f, 0.0f, 0.0f});
  btQuaternion rotation;
  rotation.setRotation(btVector3{0.0f,0.0f,1.0}, 0.0f);
  m_cobject->getWorldTransform().setRotation(rotation);
}

CbBBox::~CbBBox() {
  m_world->removeCollisionObject(m_cobject);
  delete m_cobject;
  delete m_shape;
}

bool_t CbBBox::transform(Transform transform) {
  width(transform.m_scale.x);
  height(transform.m_scale.y);
  m_cobject->getWorldTransform().setOrigin( btVector3{transform.m_position.x, 
                                                     transform.m_position.y, 
                                                     0.0} );
  btQuaternion rotation;
  rotation.setRotation(btVector3{0.0f,0.0f,1.0}, transform.m_rotation*DEGREES_TO_RADS);
  m_cobject->getWorldTransform().setRotation(rotation);
  m_world->performDiscreteCollisionDetection();
  int numManifolds = m_world->getDispatcher()->getNumManifolds();
  //For each contact manifold
  for (int i = 0; i < numManifolds; i++) {
    btPersistentManifold* contactManifold = m_world->getDispatcher()->getManifoldByIndexInternal(i);
    const btCollisionObject* obA = static_cast<const btCollisionObject*>(contactManifold->getBody0());
    const btCollisionObject* obB = static_cast<const btCollisionObject*>(contactManifold->getBody1());
    if (obA == m_cobject || obB == m_cobject) return true;
  }
  return false;
}

Transform CbBBox::transform() const {
  Vector2f position {m_cobject->getWorldTransform().getOrigin().getX(),
                     m_cobject->getWorldTransform().getOrigin().getY()}; 
  float_t rotation = m_cobject->getWorldTransform().getRotation().getAngle();
  btTransform transform;
  btVector3 minAABB;
  btVector3 maxAABB;
  m_cobject->getCollisionShape()->getAabb(transform,minAABB,maxAABB);
  Vector2f scale = {maxAABB.getX() - minAABB.getX(), maxAABB.getY() - minAABB.getY()};
  return Transform{position,rotation*RADS_TO_DEGREES,scale};
}

void CbBBox::position( Vector2f position ) {
  m_cobject->getWorldTransform().setOrigin(btVector3{position.x, position.y, 0.0f});
} 

Vector2f CbBBox::position() const {
  btVector3 position = m_cobject->getWorldTransform().getOrigin();
  return Vector2f{position.getX(), position.getY()};
} 

void CbBBox::rotation( float_t angle ) {
  btQuaternion rotation;
  rotation.setRotation(btVector3{0.0f,0.0f,1.0}, angle*DEGREES_TO_RADS);
  m_cobject->getWorldTransform().setRotation(rotation);
} 

float_t CbBBox::rotation() const {
  btQuaternion quaternion =  m_cobject->getWorldTransform().getRotation();
  return quaternion.getAngle()*RADS_TO_DEGREES;
} 

void CbBBox::width( float_t width ) {
  btTransform transform;
  transform.setIdentity();
  btVector3 minAABB;
  btVector3 maxAABB;
  m_shape->getAabb(transform, minAABB, maxAABB);
  float_t height = maxAABB.getY() - minAABB.getY();
  delete m_shape;
  m_shape = new btBoxShape(btVector3{width/2.0f, height/2.0f, 0.5});
  m_cobject->setCollisionShape(m_shape);
}

float_t CbBBox::width() {
  btTransform transform;
  transform.setIdentity();
  btVector3 minAABB;
  btVector3 maxAABB;
  m_shape->getAabb(transform, minAABB, maxAABB);
  return maxAABB.getX() - minAABB.getX();
}

void CbBBox::height( float_t height ) {
  btTransform transform;
  transform.setIdentity();
  btVector3 minAABB;
  btVector3 maxAABB;
  m_shape->getAabb(transform, minAABB, maxAABB);
  float_t width = maxAABB.getX() - minAABB.getX();
  delete m_shape;
  m_shape = new btBoxShape(btVector3{width/2.0f, height/2.0f, 0.5});
  m_cobject->setCollisionShape(m_shape);
}

float_t CbBBox::height() {
  btTransform transform;
  transform.setIdentity();
  btVector3 minAABB;
  btVector3 maxAABB;
  m_shape->getAabb(transform, minAABB, maxAABB);
  return maxAABB.getY() - minAABB.getY();
}

void CbBBox::enable() {
  if(!m_enabled) {
    m_world->addCollisionObject(m_cobject);
    m_enabled = true;
  }
}

void CbBBox::disable() {
  if(m_enabled) {
    m_world->removeCollisionObject(m_cobject);
    m_enabled = false;
  }
}

Cebullet::Cebullet (uint32_t width, uint32_t height) {
  int32_t max_objects = 512;
  btVector3 worldAabbMin(-width/2, -height/2, -1);
  btVector3 worldAabbMax(width/2, height/2, 1);
  bt_collision_configuration = new btDefaultCollisionConfiguration();
  bt_dispatcher = new btCollisionDispatcher(bt_collision_configuration);
  bt_broadphase = new bt32BitAxisSweep3(worldAabbMin, worldAabbMax, max_objects, 0, true);
  bt_collision_world = new btCollisionWorld(bt_dispatcher, bt_broadphase, bt_collision_configuration);
}

Cebullet::~Cebullet () {
  delete bt_collision_world;
  delete bt_broadphase;
  delete bt_dispatcher;
  delete bt_collision_configuration;
}

BBox* Cebullet::create_bbox() {
  return new CbBBox(bt_collision_world);
}

void Cebullet::destroy_bbox( BBox* bbox ) {
  delete bbox;
}
  
} /* tnasdk */ 
