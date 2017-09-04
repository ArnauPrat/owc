
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
namespace client {

class Client : public Ogre::FrameListener, 
                     public Ogre::WindowEventListener
{
public:
    Client(void);
    virtual ~Client(void);

    virtual void go(void);

protected:
    virtual bool setup();
    virtual bool cleanup();
    virtual bool configure(void);
    virtual void chooseSceneManager(void);
    virtual void createCamera(void);
    virtual void createFrameListener(void);
    virtual void createScene(void); 
    virtual void destroyScene(void);
    virtual void createViewports(void);
    virtual void setupResources(void);
    virtual void setupCompositor(void);
    virtual void createResourceListener(void);
    virtual void loadResources(void);
    virtual bool frameStarted(const Ogre::FrameEvent& evt) override;
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;


    // Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw) override;

    virtual void onKeywordEvent( const SDL_Event& event );
    virtual void onMouseEvent( const SDL_Event& event );



    Ogre::Root*                 m_root;
    Ogre::Camera*               m_camera;
    Ogre::SceneManager*         m_scenemgr;
    Ogre::RenderWindow*         m_window;
    Ogre::String                m_resourcescfg;
    Ogre::String                m_pluginscfg;

    Ogre::CompositorManager2*   m_compositor;
    Ogre::CompositorWorkspace*   m_workspace;

    bool                        m_shutdown;

    // Added for Mac compatibility
    Ogre::String                m_resourcepath;

    SDL_Window*                  m_sdl_window;
};

}
}


#endif 
