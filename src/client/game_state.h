
#ifndef _OWC_GAME_STATE_H_
#define _OWC_GAME_STATE_H_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>

#include <Compositor/OgreCompositorManager2.h>
#include <furious/furious.h>

union SDL_Event;

namespace owc {

class GameState : public Ogre::FrameListener, 
                  public Ogre::WindowEventListener
{
public:
    GameState(void) = default;
    virtual ~GameState(void) = default;

    virtual bool initialize();
    virtual bool release();

protected:

    virtual bool frameStarted(const Ogre::FrameEvent& evt) override;
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

    virtual void windowResized(Ogre::RenderWindow* rw) override;

    virtual void onKeywordEvent( const SDL_Event& event );
    virtual void onMouseEvent( const SDL_Event& event );

private:

};

}


#endif 
