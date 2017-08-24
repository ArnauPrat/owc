
#include <gtest/gtest.h>
#include <bbox.h>
#include <tnasdk.h>
#include <bullet/cebullet.h>
#include <cmath>

namespace tnasdk {

class BBoxTest : public ::testing::Test {

      protected:
        virtual void SetUp() {
          cengine = new Cebullet(180,120);
        }

        virtual void TearDown() {
          delete cengine;
        }

        CollisionEngine* cengine;

};


TEST_F(BBoxTest, BBoxWidth) {
  BBox* bbox = cengine->create_bbox();
  bbox->width(10.0f*CMS_TO_INCHES);
  ASSERT_TRUE(std::abs(bbox->width() - 10*CMS_TO_INCHES) < 0.001);
  cengine->destroy_bbox(bbox);
}


TEST_F(BBoxTest, BBoxHeight) {
  BBox* bbox = cengine->create_bbox();
  bbox->height(10.0f*CMS_TO_INCHES);
  ASSERT_TRUE(std::abs(bbox->height() - 10*CMS_TO_INCHES) < 0.001);
  cengine->destroy_bbox(bbox);
}

TEST_F(BBoxTest, BBoxPosition) {
  BBox* bbox = cengine->create_bbox();
  bbox->position(Vector2f{1.0f, 2.0f});
  Vector2f position = bbox->position();
  ASSERT_EQ(position.x, 1.0f);
  ASSERT_EQ(position.y, 2.0f);
  cengine->destroy_bbox(bbox);
}

TEST_F(BBoxTest, BBoxRotation) {
  BBox* bbox = cengine->create_bbox();
  float_t angle = 180.5f;
  bbox->rotation(angle);
  ASSERT_EQ(bbox->rotation(), angle);
  cengine->destroy_bbox(bbox);
}

TEST_F(BBoxTest, BBoxEnableDisable) {
  BBox* bbox = cengine->create_bbox();
  bbox->enable();
  bbox->disable();
  bbox->disable();
  bbox->enable();
  bbox->enable();
  cengine->destroy_bbox(bbox);
}

}  

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
