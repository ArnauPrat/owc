
#ifndef _CLIENT_CLIENT_H_
#define _CLIENT_CLIENT_H_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreFrameListener.h>
#include <OgreWindowEventUtilities.h>

#include <Compositor/OgreCompositorManager2.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

namespace owc {
namespace client {

class Client : public Ogre::FrameListener, 
                     public Ogre::WindowEventListener, 
                     public OIS::KeyListener, 
                     public OIS::MouseListener
{
public:
    Client(void);
    virtual ~Client(void);

    virtual void go(void);

protected:
    virtual bool setup();
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
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

    virtual bool keyPressed(const OIS::KeyEvent &arg) override;
    virtual bool keyReleased(const OIS::KeyEvent &arg) override;
    virtual bool mouseMoved(const OIS::MouseEvent &arg) override;
    virtual bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;
    virtual bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;

    // Adjust mouse clipping area
    virtual void windowResized(Ogre::RenderWindow* rw) override;
    // Unattach OIS before window shutdown (very important under Linux)
    virtual void windowClosed(Ogre::RenderWindow* rw) override;


    Ogre::Root*                 m_root;
    Ogre::Camera*               m_camera;
    Ogre::SceneManager*         m_scenemgr;
    Ogre::RenderWindow*         m_window;
    Ogre::String                m_resourcescfg;
    Ogre::String                m_pluginscfg;

    Ogre::CompositorManager2*   m_compositor;
    Ogre::CompositorWorkspace*   m_workspace;

    bool                        m_shutdown;

    //OIS Input devices
    OIS::InputManager*          m_inputmanager;
    OIS::Mouse*                 m_mouse;
    OIS::Keyboard*              m_keyboard;

    // Added for Mac compatibility
    Ogre::String                m_resourcepath;
};

}
}


#endif 
