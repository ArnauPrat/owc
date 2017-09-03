
#include <gtest/gtest.h>
#include <unit.h>
#include <tnasdk.h>
#include <bullet/cebullet.h>
#include <cmath>

namespace tnasdk {

class BattlefieldTest : public ::testing::Test {

      protected:
        virtual void SetUp() {
          cengine = new Cebullet(180*CMS_TO_INCHES,120*CMS_TO_INCHES);
          init_tnasdk(cengine,180*CMS_TO_INCHES,120*CMS_TO_INCHES);
        }

        virtual void TearDown() {
          release_tnasdk();
          delete cengine;
        }

        CollisionEngine* cengine;
};

TEST_F(BattlefieldTest, Deploy) {

  Unit* unit_a = create_unit(TroopType::E_INFANTRY, 5, 5, 20.0f*MMS_TO_INCHES, 20.0f*MMS_TO_INCHES );
  Vector2f pos_a{0.0f, 0.0f};
  float_t rot_a{45.0f};
  ASSERT_TRUE(deploy(unit_a, pos_a, rot_a));
  ASSERT_EQ(pos_a, unit_a->position());
  ASSERT_TRUE(std::abs(unit_a->rotation() - rot_a) < 0.001);

  Unit* unit_b = create_unit(TroopType::E_INFANTRY, 5, 5, 20.0f*MMS_TO_INCHES, 20.0f*MMS_TO_INCHES );
  Vector2f pos_b{0.0f, 0.0f};
  float_t rot_b{45.0f};
  ASSERT_FALSE(deploy(unit_b, pos_b, rot_b));

  remove(unit_a);

  ASSERT_TRUE(deploy(unit_b, pos_b, rot_b));
  ASSERT_EQ(pos_b, unit_b->position());
  ASSERT_TRUE(std::abs(unit_b->rotation() - rot_b) < 0.001);

  ASSERT_FALSE(deploy(unit_a, pos_a, rot_a));

  remove(unit_b);

  ASSERT_TRUE(deploy(unit_a, pos_a, rot_a));
  ASSERT_EQ(pos_a, unit_a->position());
  ASSERT_TRUE(std::abs(unit_a->rotation() - rot_a) < 0.001);

  remove(unit_a);

  pos_a = {12.0f,12.0f};
  rot_a = 0.0f;
  ASSERT_TRUE(deploy(unit_a, pos_a, rot_a));
  ASSERT_EQ(unit_a->position(), pos_a);
  ASSERT_TRUE(std::abs(unit_a->rotation() - rot_a) < 0.001);

  pos_b = {18.0f,18.0f};
  rot_b = 90.0f;
  ASSERT_TRUE(deploy(unit_b, pos_b, rot_b));
  ASSERT_EQ(unit_b->position(), pos_b);
  ASSERT_TRUE(std::abs(unit_b->rotation() - rot_b) < 0.001);

  remove(unit_a);
  remove(unit_b);

  destroy_unit(unit_a);
  destroy_unit(unit_b);
}

TEST_F(BattlefieldTest, IsValidTest) {
  Unit* unit_a = create_unit(TroopType::E_INFANTRY, 5, 5, 20.0f*MMS_TO_INCHES, 20.0f*MMS_TO_INCHES );
  Vector2f position{0.0f, 0.0f};
  float_t rotation{45.0f};
  ASSERT_TRUE(deploy(unit_a, position, rotation));

  Unit* unit_b = create_unit(TroopType::E_INFANTRY, 5, 5, 20.0f*MMS_TO_INCHES, 20.0f*MMS_TO_INCHES );
  ASSERT_FALSE(is_valid(unit_b, position, rotation));

  ASSERT_TRUE(is_valid(unit_b, Vector2f{18.0f, 18.0f}, rotation));

  remove(unit_a);
  destroy_unit(unit_a);
  destroy_unit(unit_b);
}

TEST_F(BattlefieldTest, UnitSpacingTest) {
  Unit* unit_a = create_unit(TroopType::E_INFANTRY, 5, 5, 20.0f*MMS_TO_INCHES, 20.0f*MMS_TO_INCHES );
  Unit* unit_b = create_unit(TroopType::E_INFANTRY, 5, 5, 20.0f*MMS_TO_INCHES, 20.0f*MMS_TO_INCHES );

  float_t unit_width = 20.0f*MMS_TO_INCHES*5;

  ASSERT_TRUE(deploy(unit_a, Vector2f{0.0f, 0.0f}, 0.0f));

  ASSERT_FALSE(deploy(unit_b, Vector2f{unit_width, 0.0}, 0.0f));
  ASSERT_FALSE(deploy(unit_b, Vector2f{unit_width+0.5f, 0.0f}, 0.0f));
  ASSERT_FALSE(deploy(unit_b, Vector2f{unit_width+0.75f, 0.0f}, 0.0f));
  ASSERT_FALSE(deploy(unit_b, Vector2f{unit_width+0.90f, 0.0f}, 0.0f));
  ASSERT_TRUE(deploy(unit_b, Vector2f{unit_width+1.0f, 0.0}, 0.0f));

  remove(unit_a);
  remove(unit_b);
  destroy_unit(unit_a);
  destroy_unit(unit_b);
}

TEST_F(BattlefieldTest, TerrainTest) {
  Terrain* terrain_a = create_terrain( TerrainFeature::E_IMPASSABLE, 10.0f, 5.0f );
  ASSERT_TRUE(deploy(terrain_a, Vector2f{0.0f, 0.0f}, 0.0f));

  Terrain* terrain_b = create_terrain( TerrainFeature::E_IMPASSABLE, 10.0f, 5.0f );
  ASSERT_FALSE(deploy(terrain_b, Vector2f{0.0f, 0.0f}, 0.0f));
  ASSERT_FALSE(deploy(terrain_b, Vector2f{10.0f, 0.0f}, 0.0f));
  ASSERT_TRUE(deploy(terrain_b, Vector2f{11.0f, 0.0f}, 0.0f));
  
  remove(terrain_a);
  remove(terrain_b);

  destroy_terrain(terrain_a);
  destroy_terrain(terrain_b);
}

}  

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
