
#include <gtest/gtest.h>
#include <unit.h>
#include <tnasdk.h>
#include <bullet/cebullet.h>
#include <cmath>

namespace tnasdk {

class BattlefieldTest : public ::testing::Test {

      protected:
        virtual void SetUp() {
          cengine = new Cebullet(180,120);
          init_tnasdk(cengine,180,120);
        }

        virtual void TearDown() {
          release_tnasdk();
          delete cengine;
        }

        CollisionEngine* cengine;
};

TEST_F(BattlefieldTest, Deploy) {
  Unit* unit_a = create_unit(TroopType::E_INFANTRY, 5, 5, 20.0f*MMS_TO_INCHES, 20.0f*MMS_TO_INCHES );
  Vector2f position{24, 24};
  float_t rotation{45.0f};
  bool_t result = deploy(unit_a, position, rotation);
  ASSERT_TRUE(result);
  ASSERT_TRUE(std::abs(rotation - unit_a->p_bbox->rotation()) < 0.0001);
  ASSERT_EQ(position, unit_a->p_bbox->position());

  Unit* unit_b = create_unit(TroopType::E_INFANTRY, 5, 5, 20.0f*MMS_TO_INCHES, 20.0f*MMS_TO_INCHES );
  result = deploy(unit_b, position, rotation);
  ASSERT_FALSE(result);

  remove(unit_a);

  result = deploy(unit_b, position, rotation);
  ASSERT_TRUE(result);
  ASSERT_EQ(position, unit_b->p_bbox->position());

  result = deploy(unit_a, position, rotation);
  ASSERT_FALSE(result);
  remove(unit_b);

  result = deploy(unit_a, position, rotation);
  ASSERT_TRUE(result);
  ASSERT_EQ(position, unit_a->p_bbox->position());
  remove(unit_a);

  result = deploy(unit_a, Vector2f{24,24}, 0.0f);
  ASSERT_TRUE(result);
  ASSERT_EQ(unit_a->p_bbox->position(), (Vector2f{24,24}));

  result = deploy(unit_b, Vector2f{48,48}, 0.0f);
  ASSERT_TRUE(result);
  ASSERT_EQ(unit_b->p_bbox->position(), (Vector2f{48,48}));

  remove(unit_a);
  remove(unit_b);

  destroy_unit(unit_a);
  destroy_unit(unit_b);
}

TEST_F(BattlefieldTest, ) {
  Unit* unit_a = create_unit(TroopType::E_INFANTRY, 5, 5, 20.0f*MMS_TO_INCHES, 20.0f*MMS_TO_INCHES );
  Vector2f position{24, 24};
  float_t rotation{45.0f};
  deploy(unit_a, position, rotation);

  Unit* unit_b = create_unit(TroopType::E_INFANTRY, 5, 5, 20.0f*MMS_TO_INCHES, 20.0f*MMS_TO_INCHES );
  bool_t result = is_valid(unit_b, position, rotation);
  ASSERT_FALSE(result);

  result = is_valid(unit_b, Vector2f{48.0f, 48.0f}, rotation);
  ASSERT_TRUE(result);


  remove(unit_a);
  destroy_unit(unit_a);
  destroy_unit(unit_b);
}

}  

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
