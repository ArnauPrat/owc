
#include <OGRE/Ogre.h>
#include <iostream>
#include <client.h>

int main(int argc, char *argv[])
{
  owc::client::Client client;
  client.go();
  
  return 0;
}
