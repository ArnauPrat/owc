
#include <gtest/gtest.h>
#include <vector.h>
#include <cmath>
#include <iostream>

namespace tnasdk {

TEST(VectorTest, RotateTest) {

  // Testing equality and assignment
  Vector2f vec_a = {0.0f, 0.0f};
  Vector2f vec_b = {0.0f, 0.0f};
  ASSERT_EQ(vec_a, vec_b);
  vec_b = {1.0f, 1.0f};
  ASSERT_NE(vec_a, vec_b);
  vec_a = vec_b;
  ASSERT_EQ(vec_a, vec_b);


  // Testing rotations
  Vector2f rotated = rotate( Vector2f{1.0f, 0.0f}, 90.0f );
  ASSERT_TRUE(std::abs(rotated.x - 0.0f) < 0.001);
  ASSERT_TRUE(std::abs(rotated.y - 1.0f) < 0.001);

  rotated = rotate( Vector2f{0.0f, -1.0f}, 90.0f );
  ASSERT_TRUE(std::abs(rotated.x - 1.0f) < 0.001);
  ASSERT_TRUE(std::abs(rotated.y - 0.0f) < 0.001);

}


}  

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
