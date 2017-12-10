
#include "furious.h"

struct TestComponentA {
  float x; 
  float y;
  float z;
};

struct TestComponentB {
  float x; 
  float y;
  float z;
};

struct TestSystem {
  void run(TestComponentA  * componentA, const TestComponentB*  componentB) {
    componentA->x = componentA->x + componentB->x;
    componentA->y = componentA->y + componentB->y;
    componentA->z = componentA->z + componentB->z;
  }
};

int main(int argc, char** argv) {

  furious::init();

  furious::add_component<TestComponentA>();
  furious::add_component<TestComponentB>();
  furious::add_system<TestSystem>();

  furious::Entity entity = furious::create_entity();

  furious::release();

  return 0;
}
