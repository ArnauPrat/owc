
#ifndef _CLIENT_CLIENT_H_
#define _CLIENT_CLIENT_H_

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

class Client : public Ogre::FrameListener, 
               public Ogre::WindowEventListener
{
public:
    Client(void) = default;
    virtual ~Client(void) = default;

protected:

    virtual bool frameStarted(const Ogre::FrameEvent& evt) override;
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;


    // Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw) override;

    virtual void onKeywordEvent( const SDL_Event& event );
    virtual void onMouseEvent( const SDL_Event& event );

};

}


#endif 
