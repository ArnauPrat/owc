
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

class Client;

extern Ogre::Root*                 root;
extern Ogre::Camera*               camera;
extern Ogre::SceneManager*         scenemgr;
extern Ogre::RenderWindow*         window;
extern Ogre::String                resourcescfg;
extern Ogre::String                pluginscfg;

extern Ogre::CompositorManager2*   compositor;
extern Ogre::CompositorWorkspace*  workspace;

extern bool                        shutdown;

// Added for Mac compatibility
extern Ogre::String                resourcepath;
extern SDL_Window*                 sdl_window;

void start(void);
void stop(void);


}


#endif 
