
#include <OGRE/Ogre.h>
#include <iostream>
#include "client.h"
#include "owc.h"

int main(int argc, char *argv[])
{
  owc::Client client;
  owc::start();
  owc::stop();
  
  return 0;
}
