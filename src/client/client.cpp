
#include "client.h"
#include "owc.h"

#include <OgreCommon.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>
#include <OgreLogManager.h>

#include <tnasdk/tnasdk.h>
#include <SDL2/SDL.h>

namespace owc {

  
bool Client::frameStarted(const Ogre::FrameEvent& evt) {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      onKeywordEvent(event);
      break;
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEMOTION:
      onMouseEvent(event);
      break;
    case SDL_QUIT:
      shutdown = true;
      break;
		default:
			break;
    }
  }
  return true;
}

bool Client::frameRenderingQueued(const Ogre::FrameEvent& evt) {
  if(window->isClosed())
    return false;

  if(shutdown)
    return false;
  return true;
}

void Client::onKeywordEvent( const SDL_Event& event ) {
  Ogre::LogManager::getSingleton().logMessage("KeyEvent");
  switch(event.type) {
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:  
      shutdown = true;
    }

    break;
  }
}

void Client::onMouseEvent( const SDL_Event& event ) {
  Ogre::LogManager::getSingleton().logMessage("MouseEvent");
}

// Adjust mouse clipping area
void Client::windowResized(Ogre::RenderWindow* rw) {
  unsigned int width, height, depth;
  int left, top;
  rw->getMetrics(width, height, depth, left, top);

 /* const OIS::MouseState &ms = m_mouse->getMouseState();
  ms.width = width;
  ms.height = height;
  */
}

} /* owc */ 
