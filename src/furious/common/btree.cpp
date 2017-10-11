
#include "btree.h"
#include "impl/btree_impl.h"
#include <string.h>
#include <cassert>

namespace furious {
BTree::BTree() : p_root(btree_create_internal()),
                 m_size(0)
{

}

BTree::~BTree() {
  if(p_root != nullptr) {
    btree_destroy_node(p_root);
    p_root = nullptr;
  }
}

void BTree::insert(uint8_t key, void* element) {
  btree_insert_root(&p_root, key, element);
}

void* BTree::remove(uint8_t key) {
  return btree_remove(p_root, key);
}

void* BTree::get(uint8_t key){
  return btree_get(p_root, key);
}

bool BTree::exists(uint8_t key){
  return get(key) != nullptr;
}

} /* furious */ 
