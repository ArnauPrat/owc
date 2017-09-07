
#ifndef _OWC_H_
#define _OWC_H_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>

#include <Compositor/OgreCompositorManager2.h>


union SDL_Event;
class SDL_Window;

namespace owc {

extern Ogre::Root*                 root;
extern Ogre::Camera*               camera;
extern Ogre::SceneManager*         scenemgr;

extern Ogre::CompositorManager2*   compositor;
extern Ogre::CompositorWorkspace*  workspace;
extern Ogre::RenderWindow*         window;

extern bool shutdown;

void start(void);

}


#endif 
