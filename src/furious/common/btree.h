

#ifndef _FURIOUS_BTREE_H_
#define _FURIOUS_BTREE_H_ value
#include "types.h"
#include <stdlib.h>

namespace furious {

struct BTNode;

class BTree {
public: 
  BTree();
  BTree(const BTree&) = delete;
  BTree(BTree&&) = delete;
  virtual ~BTree();
  
  void operator=(const BTree&) = delete;
  void operator=(BTree&&) = delete;

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  

  /**
   * @brief Inserts an element to the btree. Replaces the element if this
   * already existed
   *
   * @param key The key of the element to add 
   * @param element A pointer to the element to insert
   *
   * @return Returns a pointer to the replaced element. nullptr otherwise.
   */
  void insert(uint32_t key, void* element);
  

  /**
   * @brief Removes an element from the tree
   *
   * @param key The key of the element to remove 
   *
   * @return Returns a pointer to the removed element
   */
  void* remove(uint32_t key);

  /**
   * @brief Gets the element with the given key
   *
   * @param key The key of the element to search for
   *
   * @return Returns a pointer to the element with the given key. nullptr if it
   * does not exist
   */
  void* get(uint32_t key);

  /**
   * @brief Checks if an element exists
   *
   * @param key The key to of the element to look for
   *
   * @return Retursn true if the element exists. false otherwise
   */
  bool exists(uint32_t key);

  /**
   * @brief Gets the size of the btree (i.e. the number of elements)
   *
   * @return Returns the size of the btree
   */
  size_t size();

private:
   BTNode*    p_root;
   size_t     m_size;
};
  
} /* furious */ 
#endif /* ifndef  _FURIOUS_BTREE_H_ */
