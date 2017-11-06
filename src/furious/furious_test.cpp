
#include "furious.h"

struct TestComponentA {
  float x; 
  //float y;
  //float z;
};

struct TestComponentB {
  float x; 
  //float y;
  //float z;
};

struct TestSystem {
  void run(TestComponentA  * componentA, TestComponentB*  componentB) {
    componentA->x = componentA->x + componentB->x;
    //componentA.y = componentB.y*2.0;
    //componentA.z = componentB.z*2.0;
  }
};

int main(int argc, char** argv) {

  furious::StaticSystem<TestSystem, TestComponentA, TestComponentB> system;

  return 0;
}
