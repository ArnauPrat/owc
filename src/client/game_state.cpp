
#include "game_state.h"
#include "owc.h"

#include <OgreCommon.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>
#include <OgreLogManager.h>

#include <tnasdk/tnasdk.h>
#include <furious/furious.h>

#include <SDL2/SDL.h>

namespace owc {

bool GameState::initialize() {
  // Initializes tnasdk library
  tnasdk::init_tnasdk(180*CMS_TO_INCHES, 120*CMS_TO_INCHES);
  return true;
}

bool GameState::release() {
  // Release resources and shutdown
  tnasdk::release_tnasdk();
  return true;
}
  
bool GameState::frameStarted(const Ogre::FrameEvent& evt) {
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

bool GameState::frameRenderingQueued(const Ogre::FrameEvent& evt) {
  if(window->isClosed())
    return false;

  if(shutdown)
    return false;
  return true;
}

void GameState::onKeywordEvent( const SDL_Event& event ) {
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

void GameState::onMouseEvent( const SDL_Event& event ) {
  Ogre::LogManager::getSingleton().logMessage("MouseEvent");
}

// Adjust mouse clipping area
void GameState::windowResized(Ogre::RenderWindow* rw) {
  unsigned int width, height, depth;
  int left, top;
  rw->getMetrics(width, height, depth, left, top);

 /* const OIS::MouseState &ms = m_mouse->getMouseState();
  ms.width = width;
  ms.height = height;
  */
}

} /* owc */ 
