
#include <gtest/gtest.h>
#include <unit.h>
#include <tnasdk.h>
#include <bullet/cebullet.h>
#include <cmath>

namespace tnasdk {

TEST(DeployTest, Deploy) {
  CollisionEngine* cengine = new Cebullet(180,120);
  init_tnasdk(cengine,180,120);
  Unit* unit = create_unit(TroopType::E_INFANTRY, 5, 7, 20.0f*MMS_TO_INCHES, 20.0f*MMS_TO_INCHES );
  ASSERT_TRUE(std::abs(unit->p_bbox->width() - 14*CMS_TO_INCHES) < 0.001);
  ASSERT_TRUE(std::abs(unit->p_bbox->height() - 10*CMS_TO_INCHES) < 0.001);

  unit->p_bbox->width(10.0f*CMS_TO_INCHES);
  ASSERT_TRUE(std::abs(unit->p_bbox->width() - 10*CMS_TO_INCHES) < 0.001);

  unit->p_bbox->height(10.0f*CMS_TO_INCHES);
  ASSERT_TRUE(std::abs(unit->p_bbox->height() - 10*CMS_TO_INCHES) < 0.001);

  unit->p_bbox->position(Vector2f{1.0f, 2.0f});
  Vector2f position = unit->p_bbox->position();
  ASSERT_EQ(position.x, 1.0f);
  ASSERT_EQ(position.y, 2.0f);

  unit->p_bbox->rotation(180.5f);
  ASSERT_EQ(unit->p_bbox->rotation(), 180.5f);

  destroy_unit(unit);
  delete cengine;
}

}  

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
