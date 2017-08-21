
#include <client.h>
#include <OgreCommon.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>

namespace owc {
namespace client {
  
Client::Client(void) :
  m_root(nullptr),
  m_camera(nullptr),
  m_scenemgr(nullptr),
  m_window(nullptr),
  m_resourcescfg(Ogre::BLANKSTRING),
  m_pluginscfg(Ogre::BLANKSTRING),
  m_compositor(nullptr),
  m_workspace(nullptr),
  m_shutdown(false),
  m_inputmanager(nullptr),
  m_mouse(nullptr),
  m_keyboard(nullptr)
{
  m_resourcepath = "";
}

Client::~Client(void) {

  // Remove ourself as a Window listener
  Ogre::WindowEventUtilities::removeWindowEventListener(m_window, this);
  windowClosed(m_window);
  delete m_root;
}

bool Client::configure(void) {
  // Show the configuration dialog and initialise the system.
  // You can skip this and use root.restoreConfig() to load configuration
  // settings if you were sure there are valid ones saved in ogre.cfg.
  if(m_root->showConfigDialog()) {
    // If returned true, user clicked OK so initialise.
    // Here we choose to let the system create a default rendering window by passing 'true'.
    m_window = m_root->initialise(true, "OWC");

    return true;
  }
  else {
    return false;
  }
}

void Client::chooseSceneManager(void) {
  // Get the SceneManager, in this case a generic one
  m_scenemgr = m_root->createSceneManager("DefaultSceneManager",
                                          1,
                                          Ogre::INSTANCING_CULLING_SINGLETHREAD);
}

void Client::createCamera(void) {
  // Create the camera
  m_camera = m_scenemgr->createCamera("PlayerCam");

  // Position it at 500 in Z direction
  m_camera->setPosition(Ogre::Vector3(0,0,80));
  // Look back along -Z
  m_camera->lookAt(Ogre::Vector3(0,0,-300));
  m_camera->setNearClipDistance(5);

}

void Client::setupCompositor(void)
{
  m_compositor = m_root->getCompositorManager2();

  const Ogre::String workspaceName( "Owc Workspace" );
  if(!m_compositor->hasWorkspaceDefinition( workspaceName ) )
  {
    m_compositor->createBasicWorkspaceDef( workspaceName, Ogre::ColourValue{0.0,0.0,1.0,1.0},
                                                Ogre::IdString() );
  }

  m_workspace =  m_compositor->addWorkspace( m_scenemgr, 
                                             m_window, 
                                             m_camera,
                                             workspaceName, 
                                             true );
}

void Client::createFrameListener(void) {
  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
  OIS::ParamList pl;
  size_t windowHnd = 0;
  std::ostringstream windowHndStr;

  m_window->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

  m_inputmanager = OIS::InputManager::createInputSystem(pl);

  m_keyboard = static_cast<OIS::Keyboard*>(m_inputmanager->createInputObject(OIS::OISKeyboard, true));
  m_mouse = static_cast<OIS::Mouse*>(m_inputmanager->createInputObject(OIS::OISMouse, true));

  m_mouse->setEventCallback(this);
  m_keyboard->setEventCallback(this);

  // Set initial mouse clipping size
  windowResized(m_window);

  // Register as a Window listener
  Ogre::WindowEventUtilities::addWindowEventListener(m_window, this);

  m_root->addFrameListener(this);
}

void Client::destroyScene(void) {
}

void Client::createViewports(void) {
  // Create one viewport, entire window
  Ogre::Viewport* vp = new Ogre::Viewport(m_window,0,0,1,1);
  //vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

  // Alter the camera aspect ratio to match the viewport
  m_camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
  
}

void Client::setupResources(void) {
  // Load resource paths from config file
  Ogre::ConfigFile cf;
  cf.load(m_resourcescfg);

  // Go through all sections & settings in the file
  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

  Ogre::String sec_name, typeName, archName;
  while (seci.hasMoreElements()) {
    sec_name = seci.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i) {
      typeName = i->first;
      archName = i->second;
      Ogre::ResourceGroupManager::getSingleton().
                                  addResourceLocation(archName, 
                                                      typeName, 
                                                      sec_name);
    }
  }
}

void Client::createResourceListener(void) {
}

void Client::loadResources(void) {
  //Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//---------------------------------------------------------------------------
void Client::go(void) {
#ifdef _DEBUG
  m_resourcescfg = m_resourcepath + "resources_d.cfg";
  m_pluginscfg = m_resourcepath + "plugins_d.cfg";
#else
  m_resourcescfg = m_resourcepath + "resources.cfg";
  m_pluginscfg = m_resourcepath + "plugins.cfg";
#endif

  if (!setup()) {
    return;
  }

  m_root->startRendering();

  // Clean up
  destroyScene();
}

bool Client::setup(void) {
  m_root = new Ogre::Root(m_pluginscfg);

  setupResources();

  bool carry_on = configure();
  if (!carry_on) return false;

  chooseSceneManager();
  createCamera();
  setupCompositor();
  createViewports();

  // Set default mipmap level (NB some APIs ignore this)
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

  // Create any resource listeners (for loading screens)
  createResourceListener();
  // Load resources
  loadResources();

  // Create the scene
  createScene();

  createFrameListener();

  return true;
};

bool Client::frameRenderingQueued(const Ogre::FrameEvent& evt) {
  if(m_window->isClosed())
    return false;

  if(m_shutdown)
    return false;

  // Need to capture/update each device
  m_keyboard->capture();
  m_mouse->capture();

  return true;
}

bool Client::keyPressed( const OIS::KeyEvent &arg ) {
  if (arg.key == OIS::KC_ESCAPE)
  {
    m_shutdown = true;
  }

  return true;
}

bool Client::keyReleased(const OIS::KeyEvent &arg)
{
  return true;
}
//---------------------------------------------------------------------------
bool Client::mouseMoved(const OIS::MouseEvent &arg)
{
  return true;
}
//---------------------------------------------------------------------------
bool Client::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
  return true;
}
//---------------------------------------------------------------------------
bool Client::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
  return true;
}
//---------------------------------------------------------------------------
// Adjust mouse clipping area
void Client::windowResized(Ogre::RenderWindow* rw)
{
  unsigned int width, height, depth;
  int left, top;
  rw->getMetrics(width, height, depth, left, top);

  const OIS::MouseState &ms = m_mouse->getMouseState();
  ms.width = width;
  ms.height = height;
}
//---------------------------------------------------------------------------
// Unattach OIS before window shutdown (very important under Linux)
void Client::windowClosed(Ogre::RenderWindow* rw)
{
  // Only close for window that created OIS (the main window in these demos)
  if(rw == m_window) {
    if(m_inputmanager) {
      m_inputmanager->destroyInputObject(m_mouse);
      m_inputmanager->destroyInputObject(m_keyboard);

      OIS::InputManager::destroyInputSystem(m_inputmanager);
      m_inputmanager = 0;
    }
  }
}

void Client::createScene(void) {
}
}
} /* owc */ 
