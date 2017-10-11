
#include <gtest/gtest.h>
#include "../common/btree.h"
#include "../common/common.h"
#include "../common/impl/btree_impl.h"
#include <iostream>

namespace furious {

constexpr uint8_t MAX_KEY = 255;
struct TestValue {
  uint8_t m_val;
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

TEST(BTreeTest, btree_get) {
 
  BTNode* node = btree_create_internal();

  for (uint8_t i = 0; i < BTREE_MAX_ARITY; ++i) {
    BTNode* leaf = btree_create_leaf();
    node->m_internal.m_children[i] = leaf;
    for (uint8_t j = 0; j < BTREE_MIN_ARITY; ++j) {
      uint8_t key = i*BTREE_MIN_ARITY+j;
      leaf->m_leaf.m_leafs[j] = new TestValue{key};
      leaf->m_leaf.m_keys[j] = key; 
      leaf->m_leaf.m_nleafs++; 
    }
    node->m_internal.m_nchildren++;
    if( i >= 1 ) {
      node->m_internal.m_keys[i-1] = leaf->m_leaf.m_keys[0];
    }
  }

  for( uint8_t i = 0; i < BTREE_MAX_ARITY; ++i ) {
    for ( uint8_t j = 0; j < BTREE_MIN_ARITY; ++j) {
      uint8_t key = i*BTREE_MIN_ARITY+j;
      TestValue* value = static_cast<TestValue*>(btree_get(node, (i*BTREE_MIN_ARITY+j)));
      ASSERT_NE(value, nullptr);
      ASSERT_EQ(value->m_val, key);
    }
  }

  for (uint8_t i = 0; i < BTREE_MAX_ARITY; ++i) {
    BTNode* leaf = node->m_internal.m_children[i];
    for (uint8_t j = 0; j < BTREE_MIN_ARITY; ++j) {
      delete static_cast<TestValue*>(leaf->m_leaf.m_leafs[j]);
    }
  }

  delete node;
}

TEST(BTreeTest, btree_shift_insert_internal) {

  BTNode* node = btree_create_internal();
  BTNode* child = btree_create_internal();
  node->m_internal.m_children[0] = child;
  node->m_internal.m_nchildren++;

  BTNode* child2 = btree_create_internal();
  btree_shift_insert_internal(node, 1, child2, 10);
  ASSERT_EQ(node->m_internal.m_nchildren, 2);
  ASSERT_EQ(node->m_internal.m_children[0], child);
  ASSERT_EQ(node->m_internal.m_children[1], child2);
  ASSERT_EQ(node->m_internal.m_keys[0], 10);

  BTNode* child3 = btree_create_internal();
  btree_shift_insert_internal(node, 1, child3, 5);
  ASSERT_EQ(node->m_internal.m_nchildren, 3);
  ASSERT_EQ(node->m_internal.m_children[0], child);
  ASSERT_EQ(node->m_internal.m_children[1], child3);
  ASSERT_EQ(node->m_internal.m_children[2], child2);
  ASSERT_EQ(node->m_internal.m_keys[0], 5);
  ASSERT_EQ(node->m_internal.m_keys[1], 10);

  btree_destroy_node(node);
  
}

TEST(BTreeTest, btree_shift_insert_leaf) {

  BTNode* node = btree_create_leaf();
  TestValue* child = new TestValue{0};
  node->m_leaf.m_leafs[0] = child;
  node->m_leaf.m_keys[0] = 0;
  node->m_leaf.m_nleafs++;

  TestValue* child2 = new TestValue{10};
  btree_shift_insert_leaf(node, 1, child2, 10);
  ASSERT_NE(node->m_leaf.m_leafs[0], nullptr);
  ASSERT_NE(node->m_leaf.m_leafs[1], nullptr);
  ASSERT_EQ(node->m_leaf.m_keys[0], 0);
  ASSERT_EQ(node->m_leaf.m_keys[1], 10);
  ASSERT_EQ(static_cast<TestValue*>(node->m_leaf.m_leafs[0])->m_val, 0 );
  ASSERT_EQ(static_cast<TestValue*>(node->m_leaf.m_leafs[1])->m_val, 10 );

  TestValue* child3 = new TestValue{5};
  btree_shift_insert_leaf(node, 1, child3, 5);

  ASSERT_NE(node->m_leaf.m_leafs[0], nullptr);
  ASSERT_NE(node->m_leaf.m_leafs[1], nullptr);
  ASSERT_NE(node->m_leaf.m_leafs[1], nullptr);
  ASSERT_EQ(node->m_leaf.m_keys[0], 0);
  ASSERT_EQ(node->m_leaf.m_keys[1], 5);
  ASSERT_EQ(node->m_leaf.m_keys[2], 10);
  ASSERT_EQ(static_cast<TestValue*>(node->m_leaf.m_leafs[0])->m_val, 0 );
  ASSERT_EQ(static_cast<TestValue*>(node->m_leaf.m_leafs[1])->m_val, 5 );
  ASSERT_EQ(static_cast<TestValue*>(node->m_leaf.m_leafs[2])->m_val, 10 );

  delete child;
  delete child2;
  delete child3;
  btree_destroy_node(node);
  
}

TEST(BTreeTest, btree_insert) {

  BTNode* node = btree_create_internal();
  TestValue* element = new TestValue{0};
  btree_insert(node, 0, element );
  ASSERT_NE(node->m_internal.m_children[0], nullptr);
  ASSERT_EQ(node->m_internal.m_children[0]->m_leaf.m_leafs[0], element);
  ASSERT_EQ(node->m_internal.m_children[0]->m_leaf.m_keys[0], 0);

  TestValue* element2 = new TestValue{1};
  btree_insert(node, 1, element2 );
  ASSERT_EQ(node->m_internal.m_children[0]->m_leaf.m_leafs[1], element2);
  ASSERT_EQ(node->m_internal.m_children[0]->m_leaf.m_keys[1], 1);

  TestValue* element3 = new TestValue{2};
  btree_insert(node, 2, element3 );
  ASSERT_EQ(node->m_internal.m_children[0]->m_leaf.m_leafs[2], element3);
  ASSERT_EQ(node->m_internal.m_children[0]->m_leaf.m_keys[2], 2);

  delete element;
  delete element2;
  delete element3;
  btree_destroy_node(node);
  
}

TEST(BTreeTest, BTree) {
  BTree btree;

  uint32_t BTREE_MAX_KEY=255;

  TestValue* values[BTREE_MAX_KEY];

  for (uint32_t i = 0; i <= BTREE_MAX_KEY; ++i) {
    values[i] = new TestValue{static_cast<uint8_t>(i)};
    btree.insert(static_cast<uint8_t>(i), values[i]);
  }

  for (uint32_t i = 0; i <= BTREE_MAX_KEY; ++i) {
    TestValue* value = static_cast<TestValue*>(btree.get(i));
    ASSERT_EQ(value, values[i]);
  }

}

} /* furious */ 

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}
