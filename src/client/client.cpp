
#include <client.h>
#include <OgreCommon.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>
#include <OgreLogManager.h>
#include <tnasdk.h>
#include <bullet/cebullet.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

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
  m_sdl_window(nullptr)
{
  m_resourcepath = "";
}

Client::~Client(void) {

}

bool Client::configure(void) {

	if( SDL_Init( SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS ) != 0 ) {
		OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot initialize SDL2!", "GraphicsSystem::initialize" );
	}   

  Ogre::String pluginsPath;

  m_root = new Ogre::Root(m_pluginscfg);

  setupResources();

  // Show the configuration dialog and initialise the system.
  // You can skip this and use root.restoreConfig() to load configuration
  // settings if you were sure there are valid ones saved in ogre.cfg.
  if(m_root->showConfigDialog()) {
    // If returned true, user clicked OK so initialise.
    // Here we choose to let the system create a default rendering window by passing 'true'.
    m_window = m_root->initialise(false, "OWC");
    Ogre::ConfigOptionMap& cfgOpts = m_root->getRenderSystem()->getConfigOptions();

    int width   = 1280;
    int height  = 720;

    Ogre::ConfigOptionMap::iterator opt = cfgOpts.find( "Video Mode" );
    if( opt != cfgOpts.end() )
    {
      //Ignore leading space
      const Ogre::String::size_type start = opt->second.currentValue.find_first_of("012356789");
      //Get the width and height
      Ogre::String::size_type widthEnd = opt->second.currentValue.find(' ', start);
      // we know that the height starts 3 characters after the width and goes until the next space
      Ogre::String::size_type heightEnd = opt->second.currentValue.find(' ', widthEnd+3);
      // Now we can parse out the values
      width   = Ogre::StringConverter::parseInt( opt->second.currentValue.substr( 0, widthEnd ) );
      height  = Ogre::StringConverter::parseInt( opt->second.currentValue.substr(
                                                                                 widthEnd+3, heightEnd ) );
    }

    Ogre::NameValuePairList params;
    bool fullscreen = Ogre::StringConverter::parseBool( cfgOpts["Full Screen"].currentValue );
    int screen = 0;
    int posX = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
    int posY = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);

    if(fullscreen)
    {
      posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
      posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
    }

    m_sdl_window = SDL_CreateWindow(
                                  "OWC",    // window title
                                  posX,               // initial x position
                                  posY,               // initial y position
                                  width,              // width, in pixels
                                  height,             // height, in pixels
                                  SDL_WINDOW_SHOWN
                                  | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE );

    //Get the native whnd
    SDL_SysWMinfo wmInfo;
    SDL_VERSION( &wmInfo.version );

    if( SDL_GetWindowWMInfo( m_sdl_window, &wmInfo ) == SDL_FALSE )
    {
      OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR,
                   "Couldn't get WM Info! (SDL2)",
                   "GraphicsSystem::initialize" );
    }

    Ogre::String winHandle;
    switch( wmInfo.subsystem )
    {
#ifdef WIN32
    case SDL_SYSWM_WINDOWS:
      // Windows code
      winHandle = Ogre::StringConverter::toString( (uintptr_t)wmInfo.info.win.window );
      break;
#elif __MACOSX__
    case SDL_SYSWM_COCOA:
      //required to make OGRE play nice with our window
      params.insert( std::make_pair("macAPI", "cocoa") );
      params.insert( std::make_pair("macAPICocoaUseNSView", "true") );

      winHandle  = Ogre::StringConverter::toString(WindowContentViewHandle(wmInfo));
      break;
#else
    case SDL_SYSWM_X11:
      winHandle = Ogre::StringConverter::toString( (uintptr_t)wmInfo.info.x11.window );
      break;
#endif
    default:
      OGRE_EXCEPT( Ogre::Exception::ERR_NOT_IMPLEMENTED,
                   "Unexpected WM! (SDL2)",
                   "GraphicsSystem::initialize" );
      break;
    }

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    params.insert( std::make_pair("externalWindowHandle",  winHandle) );
#else
    params.insert( std::make_pair("parentWindowHandle",  winHandle) );
#endif

    params.insert( std::make_pair("title", "OWC") );
    params.insert( std::make_pair("gamma", "true") );
    params.insert( std::make_pair("FSAA", cfgOpts["FSAA"].currentValue) );
    params.insert( std::make_pair("vsync", cfgOpts["VSync"].currentValue) );

    m_window = Ogre::Root::getSingleton().createRenderWindow( "OWC", width, height,
                                                                   fullscreen, &params );

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

void Client::setupCompositor(void) {
  m_compositor = m_root->getCompositorManager2();

  const Ogre::String workspaceName( "Owc Workspace" );
  if(!m_compositor->hasWorkspaceDefinition( workspaceName ) ) {
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
  size_t windowHnd = 0;
  std::ostringstream windowHndStr;

  m_window->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;

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
  cleanup();
}

bool Client::setup(void) {


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

  // Initializes tnasdk library
  tnasdk::init_tnasdk(180*CMS_TO_INCHES, 120*CMS_TO_INCHES);

  // Create the scene
  createScene();

  createFrameListener();

  return true;
};

bool Client::cleanup(void) {
  tnasdk::release_tnasdk();

  // Remove ourself as a Window listener
  Ogre::WindowEventUtilities::removeWindowEventListener(m_window, this);
  windowClosed(m_window);
  delete m_root;
  SDL_SetWindowFullscreen(m_sdl_window,0);
  SDL_DestroyWindow(m_sdl_window);
	SDL_Quit();
  return true;
}

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
      m_shutdown = true;
      break;
		default:
			break;
    }
  }
  return true;
}

bool Client::frameRenderingQueued(const Ogre::FrameEvent& evt) {
  if(m_window->isClosed())
    return false;

  if(m_shutdown)
    return false;
  return true;
}

void Client::onKeywordEvent( const SDL_Event& event ) {
  Ogre::LogManager::getSingleton().logMessage("KeyEvent");
  switch(event.type) {
  case SDL_KEYDOWN:
    switch (event.key.keysym.sym) {
    case SDLK_ESCAPE:  
      m_shutdown = true;
    }

    break;
  }
}

void Client::onMouseEvent( const SDL_Event& event ) {
  Ogre::LogManager::getSingleton().logMessage("MouseEvent");
}

/*bool Client::keyPressed( const OIS::KeyEvent &arg ) {
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
*/
//---------------------------------------------------------------------------
// Adjust mouse clipping area
void Client::windowResized(Ogre::RenderWindow* rw)
{
  unsigned int width, height, depth;
  int left, top;
  rw->getMetrics(width, height, depth, left, top);

 /* const OIS::MouseState &ms = m_mouse->getMouseState();
  ms.width = width;
  ms.height = height;
  */
}

void Client::createScene(void) {
}
}
} /* owc */ 
