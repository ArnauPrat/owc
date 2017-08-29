

#include <btBulletDynamicsCommon.h>
#include <cebullet.h>
#include <iostream>

namespace tnasdk {

CbBBox::CbBBox(btCollisionWorld* world ) : 
  m_world(world) {
  m_cobject = new btCollisionObject();
  m_cobject->setUserPointer(this);
  m_shape = new btBoxShape(btVector3{0.5f, 0.5f, 0.5f});
  m_shape->setMargin(0.0f);
  m_cobject->setCollisionShape(m_shape);
  m_cobject->getWorldTransform().setOrigin(btVector3{0.0f, 0.0f, 0.0f});
  btQuaternion rotation;
  rotation.setRotation(btVector3{0.0f,0.0f,1.0}, 0.0f);
  m_cobject->getWorldTransform().setRotation(rotation);
  m_world->addCollisionObject(m_cobject);
}

CbBBox::~CbBBox() {
  m_world->removeCollisionObject(m_cobject);
  delete m_cobject;
  delete m_shape;
}

void CbBBox::transform(Vector2f position, float_t rotation) {
  m_cobject->getWorldTransform().setOrigin( btVector3{position.x, 
                                                      position.y, 
                                                      0.0} );
  btQuaternion rotation_qt;
  rotation_qt.setRotation(btVector3{0.0f,0.0f,1.0}, rotation*DEGREES_TO_RADS);
  m_cobject->getWorldTransform().setRotation(rotation_qt);
  /*
  m_world->performDiscreteCollisionDetection();

  int numManifolds = m_world->getDispatcher()->getNumManifolds();
  for (int i = 0; i < numManifolds; i++) {
    btPersistentManifold* contactManifold = m_world->getDispatcher()->getManifoldByIndexInternal(i);
    const btCollisionObject* obA = static_cast<const btCollisionObject*>(contactManifold->getBody0());
    const btCollisionObject* obB = static_cast<const btCollisionObject*>(contactManifold->getBody1());
    if ((obA == m_cobject || obB == m_cobject) && contactManifold->getNumContacts() > 0 ) {
      return true;
    }
  }
  return false; */
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
  m_configuration = new btDefaultCollisionConfiguration();
  m_dispatcher = new btCollisionDispatcher(m_configuration);
  m_broadphase = new bt32BitAxisSweep3(worldAabbMin, worldAabbMax, max_objects, 0, true);
  m_world = new btCollisionWorld(m_dispatcher, m_broadphase, m_configuration);
}

Cebullet::~Cebullet () {
  delete m_world;
  delete m_broadphase;
  delete m_dispatcher;
  delete m_configuration;
}

BBox* Cebullet::create_bbox() {
  return new CbBBox(m_world);
}

void Cebullet::destroy_bbox( BBox* bbox ) {
  delete bbox;
}


std::vector<Collision> Cebullet::detect_collisions() {
  std::vector<Collision> collisions;
  m_world->performDiscreteCollisionDetection();
  int numManifolds = m_world->getDispatcher()->getNumManifolds();
  for (int i = 0; i < numManifolds; i++) {
    btPersistentManifold* contactManifold = m_world->getDispatcher()->getManifoldByIndexInternal(i);
    const btCollisionObject* obA = static_cast<const btCollisionObject*>(contactManifold->getBody0());
    const btCollisionObject* obB = static_cast<const btCollisionObject*>(contactManifold->getBody1());
    if (contactManifold->getNumContacts() > 0 ) {
      collisions.push_back( Collision{static_cast<CbBBox*>(obA->getUserPointer()), static_cast<CbBBox*>(obB->getUserPointer())});
    }
  }
  return collisions;
}
  
} /* tnasdk */ 
