
#include "owc.h"
#include "client.h"
#include "components/unit_component.h"

#include <OgreCommon.h>
#include <OgreTextureManager.h>
#include <OgreViewport.h>
#include <OgreLogManager.h>

#include <tnasdk/tnasdk.h>

#include <furious/furious.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include <iostream>

using namespace furious;
using namespace furious::data;

namespace owc {

Ogre::Root*                 root = nullptr;
Ogre::Camera*               camera = nullptr;
Ogre::SceneManager*         scenemgr = nullptr;
Ogre::RenderWindow*         window = nullptr;
Ogre::String                resourcescfg = Ogre::BLANKSTRING;
Ogre::String                pluginscfg = Ogre::BLANKSTRING;

Ogre::CompositorManager2*   compositor = nullptr;
Ogre::CompositorWorkspace*  workspace = nullptr;

bool                        shutdown;

// Added for Mac compatibility
Ogre::String                resourcepath;
SDL_Window*                 sdl_window;

Client*                     client = nullptr;

static void chooseSceneManager(void) {
  // Get the SceneManager, in this case a generic one
  scenemgr = root->createSceneManager("DefaultSceneManager",
                                          1,
                                          Ogre::INSTANCING_CULLING_SINGLETHREAD);
}

static void createCamera(void) {
  // Create the camera
  camera = scenemgr->createCamera("PlayerCam");

  // Position it at 500 in Z direction
  camera->setPosition(Ogre::Vector3(0,0,80));

  // Look back along -Z
  camera->lookAt(Ogre::Vector3(0,0,-300));
  camera->setNearClipDistance(5);
}

static void setupCompositor(void) {
  compositor = root->getCompositorManager2();

  const Ogre::String workspaceName( "Owc Workspace" );
  if(!compositor->hasWorkspaceDefinition( workspaceName ) ) {
    compositor->createBasicWorkspaceDef( workspaceName, Ogre::ColourValue{0.0,0.0,1.0,1.0},
                                                Ogre::IdString() );
  }

  workspace =  compositor->addWorkspace( scenemgr, 
                                         window, 
                                         camera,
                                         workspaceName, 
                                         true );
}

static void createFrameListener(void) {
  size_t windowHnd = 0;
  std::ostringstream windowHndStr;

  window->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;

  client = new Client();
  // Register as a Window listener
  Ogre::WindowEventUtilities::addWindowEventListener(window, client);
  
  root->addFrameListener(client);
}

static void createViewports(void) {
  // Create one viewport, entire window
  Ogre::Viewport* vp = new Ogre::Viewport(window,0,0,1,1);
  //vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

  // Alter the camera aspect ratio to match the viewport
  camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
  
}

static void setupResources(void) {

  // Load resource paths from config file
  Ogre::ConfigFile cf;
  cf.load(resourcescfg);

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

void start(void) {

  resourcepath = "";
#ifdef _DEBUG
  resourcescfg = resourcepath + "resources_d.cfg";
  pluginscfg = resourcepath + "plugins_d.cfg";
#else
  resourcescfg = resourcepath + "resources.cfg";
  pluginscfg = resourcepath + "plugins.cfg";
#endif


  // Initialize SDL
  if( SDL_Init( SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS ) != 0 ) {
    OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot initialize SDL2!", "GraphicsSystem::initialize" );
  }   

  root = new Ogre::Root(pluginscfg);
  setupResources();

  // Show the configuration dialog and initialise the system.
  // You can skip this and use root.restoreConfig() to load configuration
  // settings if you were sure there are valid ones saved in ogre.cfg.
  if(!root->restoreConfig() && root->showConfigDialog()) {
    std::cout << "ENTRA!" << std::endl;
    Ogre::String w_title = "OWC";
    // If returned true, user clicked OK so initialise.
    // Here we choose to let the system create a default rendering window by passing 'true'.
    window = root->initialise(false, w_title);
    Ogre::ConfigOptionMap& cfgOpts = root->getRenderSystem()->getConfigOptions();

    int width   = 1280;
    int height  = 720;

    Ogre::ConfigOptionMap::iterator opt = cfgOpts.find( "Video Mode" );
    if( opt != cfgOpts.end() ) {
      //Ignore leading space
      const Ogre::String::size_type start = opt->second.currentValue.find_first_of("012356789");
      //Get the width and height
      Ogre::String::size_type widthEnd = opt->second.currentValue.find(' ', start);
      // we know that the height starts 3 characters after the width and goes until the next space
      Ogre::String::size_type heightEnd = opt->second.currentValue.find(' ', widthEnd+3);
      // Now we can parse out the values
      width   = Ogre::StringConverter::parseInt( opt->second.currentValue.substr( 0, widthEnd ) );
      height  = Ogre::StringConverter::parseInt( opt->second.currentValue.substr( widthEnd+3, heightEnd ) );
    }

    Ogre::NameValuePairList params;
    bool fullscreen = Ogre::StringConverter::parseBool( cfgOpts["Full Screen"].currentValue );
    int screen = 0;
    int posX = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);
    int posY = SDL_WINDOWPOS_CENTERED_DISPLAY(screen);

    if(fullscreen) {
      posX = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
      posY = SDL_WINDOWPOS_UNDEFINED_DISPLAY(screen);
    }

    sdl_window = SDL_CreateWindow(
                                    w_title.c_str(),    // window title
                                    posX,               // initial x position
                                    posY,               // initial y position
                                    width,              // width, in pixels
                                    height,             // height, in pixels
                                    SDL_WINDOW_SHOWN
                                    | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_RESIZABLE );

    //Get the native whnd
    SDL_SysWMinfo wmInfo;
    SDL_VERSION( &wmInfo.version );

    if( SDL_GetWindowWMInfo( sdl_window, &wmInfo ) == SDL_FALSE ) {
      OGRE_EXCEPT( Ogre::Exception::ERR_INTERNAL_ERROR,
                   "Couldn't get WM Info! (SDL2)",
                   "GraphicsSystem::initialize" );
    }

    Ogre::String winHandle;
    switch( wmInfo.subsystem ) {
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

    params.insert( std::make_pair("title", w_title.c_str()));
    params.insert( std::make_pair("gamma", "true") );
    params.insert( std::make_pair("FSAA", cfgOpts["FSAA"].currentValue) );
    params.insert( std::make_pair("vsync", cfgOpts["VSync"].currentValue) );

    window = Ogre::Root::getSingleton().createRenderWindow( w_title, 
                                                              width, 
                                                              height,
                                                              fullscreen, 
                                                              &params );
  }
  else {
    return;
  }

  chooseSceneManager();
  createCamera();
  setupCompositor();
  createViewports();

  // Set default mipmap level (NB some APIs ignore this)
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

  // Initializes tnasdk library
  tnasdk::init_tnasdk(180*CMS_TO_INCHES, 120*CMS_TO_INCHES);

  createFrameListener();

  root->startRendering();

}


void stop(void) {

  tnasdk::release_tnasdk();

  // Remove ourself as a Window listener
  Ogre::WindowEventUtilities::removeWindowEventListener(window, client);

  delete client;
  delete root;
  SDL_SetWindowFullscreen(sdl_window,0);
  SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}

} /* owc */ 
