
#include <gtest/gtest.h>
#include <terrain.h>

namespace tnasdk {

TEST(TerrainTest, TerrainType) {
}

}  

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
