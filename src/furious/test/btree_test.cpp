
#include <gtest/gtest.h>
#include "../common/common.h"
#include "../common/impl/btree_impl.h"

namespace furious {

constexpr uint8_t MAX_KEY = 255;
struct TestValue {
  uint8_t val;
};

TEST(BTreeTest, node_size) {
  ASSERT_EQ(sizeof(BTNode), 64);
}

TEST(BTreeTest, btree_create) {
  BTNode* internal = btree_create_internal();
  for (uint8_t i = 0; i < BTREE_MAX_ARITY; ++i) {
    ASSERT_EQ(internal->m_internal.m_children[i], nullptr);
  }

  for (uint8_t i = 0; i < BTREE_MAX_ARITY-1; ++i) {
    ASSERT_EQ(internal->m_internal.m_keys[i], 0);
  }

  ASSERT_EQ(internal->m_internal.m_nchildren, 0);
  btree_destroy_node(internal);

  BTNode* leaf = btree_create_internal();
  for (uint8_t i = 0; i < BTREE_MIN_ARITY; ++i) {
    ASSERT_EQ(leaf->m_leaf.m_leafs[i], nullptr);
    ASSERT_EQ(leaf->m_leaf.m_keys[i], 0);
  }

  ASSERT_EQ(leaf->m_leaf.m_nleafs, 0);
  ASSERT_EQ(leaf->m_leaf.m_next, nullptr);
  btree_destroy_node(leaf);
}

TEST(BTreeTest, btree_next_internal) {

  BTNode* node = btree_create_internal();

  for (uint8_t i = 0; i < BTREE_MAX_ARITY; ++i) {
    node->m_internal.m_children[i] = btree_create_leaf();
    node->m_internal.m_nchildren++;
  }

  for (uint8_t i = 1; i < BTREE_MAX_ARITY; ++i) {
    node->m_internal.m_keys[i-1] = i*10;
  }

  for (uint8_t i = 0; i < BTREE_MAX_ARITY; ++i) {
    ASSERT_EQ(btree_next_internal(node,i*10), i);
  }

  for (uint8_t i = 0; i < BTREE_MAX_ARITY; ++i) {
    btree_destroy_node(node->m_internal.m_children[i] = btree_create_leaf());
  }
  btree_destroy_node(node);

}

TEST(BTreeTest, btree_next_leaf) {

  BTNode* node = btree_create_leaf();

  for (uint8_t i = 0; i < BTREE_MIN_ARITY; ++i) {
    node->m_leaf.m_leafs[i] = new TestValue{i};
    node->m_leaf.m_keys[i] = i;
    node->m_leaf.m_nleafs++;
  }

  for (uint8_t i = 0; i < BTREE_MIN_ARITY; ++i) {
    ASSERT_EQ(btree_next_leaf(node,i), i);
  }

  for (uint8_t i = 0; i < BTREE_MIN_ARITY; ++i) {
    delete static_cast<TestValue*>(node->m_leaf.m_leafs[i]);
  }
  btree_destroy_node(node);

}

TEST(BTreeTest, btree_split_internal) {

  BTNode* node = btree_create_internal();

  for (uint8_t i = 0; i < BTREE_MAX_ARITY; ++i) {
    node->m_internal.m_children[i] = btree_create_leaf();
    node->m_internal.m_nchildren++;
  }

  for (uint8_t i = 1; i < BTREE_MAX_ARITY; ++i) {
    node->m_internal.m_keys[i-1] = i*10;
  }

  uint8_t sibling_key;
  BTNode* sibling = btree_split_internal(node, &sibling_key);

  uint8_t LEFT = (BTREE_MAX_ARITY+2-1)/2;
  uint8_t RIGHT = (BTREE_MAX_ARITY/2);

  ASSERT_EQ(node->m_internal.m_nchildren, LEFT );
  ASSERT_EQ(sibling->m_internal.m_nchildren, RIGHT);
  ASSERT_EQ(sibling_key, (LEFT)*10);

  for (uint8_t i = 0; i < LEFT - 1 ; ++i) {
    ASSERT_EQ(node->m_internal.m_keys[i], (i+1)*10);
  }

  for (uint8_t i = LEFT; i < BTREE_MAX_ARITY ; ++i) {
    ASSERT_EQ(node->m_internal.m_children[i], nullptr);
  }

  for (uint8_t i = 0; i < RIGHT - 1 ; ++i) {
    ASSERT_EQ(sibling->m_internal.m_keys[i], (LEFT+i+1)*10);
  }

  for (uint8_t i = RIGHT; i < BTREE_MAX_ARITY; ++i) {
    ASSERT_EQ(sibling->m_internal.m_children[i], nullptr);
  }

  for (uint8_t i = 0; i < LEFT; ++i) {
    btree_destroy_node(node->m_internal.m_children[i]);
  }

  for (uint8_t i = 0; i < RIGHT; ++i) {
    btree_destroy_node(sibling->m_internal.m_children[i]);
  }

  btree_destroy_node(sibling);
  btree_destroy_node(node);

}

TEST(BTreeTest, btree_split_leaf) {

  BTNode* node = btree_create_leaf();

  for (uint8_t i = 0; i < BTREE_MIN_ARITY; ++i) {
    node->m_leaf.m_leafs[i] = new TestValue{i};
    node->m_leaf.m_keys[i] = i;
    node->m_leaf.m_nleafs++;
  }

  uint8_t sibling_key;
  BTNode* sibling = btree_split_leaf(node, &sibling_key);


  uint8_t LEFT = (BTREE_MIN_ARITY+2-1)/2;
  uint8_t RIGHT= BTREE_MIN_ARITY - LEFT;

  ASSERT_EQ(node->m_leaf.m_nleafs, LEFT);
  ASSERT_EQ(sibling->m_leaf.m_nleafs, RIGHT);
  ASSERT_EQ(sibling_key, LEFT);

  for (uint8_t i = 0; i < LEFT; ++i) {
    ASSERT_EQ(node->m_leaf.m_keys[i], i);
  }

  for (uint8_t i = LEFT; i < BTREE_MIN_ARITY ; ++i) {
    ASSERT_EQ(node->m_leaf.m_leafs[i], nullptr);
  }

  for (uint8_t i = 0; i < RIGHT ; ++i) {
    ASSERT_EQ(sibling->m_leaf.m_keys[i], (LEFT+i));
  }

  for (uint8_t i = RIGHT; i < BTREE_MIN_ARITY; ++i) {
    ASSERT_EQ(sibling->m_leaf.m_leafs[i], nullptr);
  }

  for (uint8_t i = 0; i < LEFT; ++i) {
    delete static_cast<TestValue*>(node->m_leaf.m_leafs[i]);
  }

  for (uint8_t i = 0; i < RIGHT; ++i) {
    delete static_cast<TestValue*>(sibling->m_leaf.m_leafs[i]);
  }

  btree_destroy_node(sibling);
  btree_destroy_node(node);

}

} /* furious */ 

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
