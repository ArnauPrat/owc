

#ifndef _FURIOUS_BTREE_H_
#define _FURIOUS_BTREE_H_ value
#include "types.h"
#include <stdlib.h>

namespace furious {

/**
 * @brief This is the arity of the BTree. The number 7 is purposely choosen,
 * because we assume a cache line of size 64 bytes and we want a node to fit in it.
 * In a line of cache we can fit up to 8
 * pointers of size 8 bytes (8x8=64bytes). Since we need room for the keys,
 * which we assume of size 1 byte, and we want both pointers and keys to fit in
 * a line of cache, we choose 7 pointers and leave the last 8 bytes to store the
 * 6 needed keys, leaving 2 bytes for other stuff. 
 * This btree has a max capacity of 65K objects
 */
constexpr uint32_t BTREE_MAX_ARITY=7;
constexpr uint32_t BTREE_MIN_ARITY=(BTREE_MAX_ARITY+2-1)/2;

enum class BTNodeType : uint8_t {
  E_INTERNAL,
  E_LEAF,
};

union BTNode {

  struct __attribute__((__packed__)) {
    void*     m_children[BTREE_MAX_ARITY]; // 7*8 = 56 bytes
    uint8_t   m_keys[BTREE_MAX_ARITY-1];   // 6 bytes
    uint8_t   m_koffset;                   // 1 byte
  } m_internal; // total 63 bytes

  struct __attribute__((__packed__)) {
    void*       m_leaf[BTREE_MIN_ARITY];   // 4*8 = 32 bytes
    BTNode*     m_next;                    // 8 bytes
    uint8_t     m_koffset;                 // 1 byte
  } m_leaf; // total 41 bytes

  BTNodeType    m_type;                      // 1 byte
};


/**
 * @brief Creates a new instance of a BTNode of the given type
 *
 * @param type The type to create the node of
 *
 * @return A pointer to the newly created BTNode
 */
BTNode* create_node(BTNodeType type);

/**
 * @brief Removes a given BTNode 
 *
 * @param node The pointer to the node to remove
 */
void remove_node(BTNode* node);


using FKeyPtr = uint8_t (*) (void * );

class BTree {
public: 
  BTree() = delete;
  BTree(FKeyPtr fkey);
  BTree(const BTree&) = delete;
  BTree(BTree&&) = delete;
  virtual ~BTree() = default;
  
  void operator=(const BTree&) = delete;
  void operator=(BTree&&) = delete;

  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  ////////////////////////////////////////////////
  

  /**
   * @brief Inserts an element to the btree. Replaces the element if this
   * already existed
   *
   * @param element A pointer to the element to insert
   *
   * @return Returns a pointer to the replaced element. nullptr otherwise
   */
  void* insert(void* element);
  

  /**
   * @brief Removes an element from the tree
   *
   * @param element A pointer to the element to be removed 
   */
  void remove(void* element);

  /**
   * @brief Gets the element with the given key
   *
   * @param key The key of the element to search for
   *
   * @return Returns a pointer to the element with the given key. nullptr if it
   * does not exist
   */
  void* get(uint16_t key);

  /**
   * @brief Checks if an element exists
   *
   * @param key The key to of the element to look for
   *
   * @return Retursn true if the element exists. false otherwise
   */
  bool exists(uint16_t key);


  /**
   * @brief Gets the size of the btree (i.e. the number of elements)
   *
   * @return Returns the size of the btree
   */
  size_t size();

private:
   FKeyPtr    p_fkey;
   BTNode*    m_root;
   size_t     m_size;
};
  
} /* furious */ 
#endif /* ifndef  _FURIOUS_BTREE_H_ */
