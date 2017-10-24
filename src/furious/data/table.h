
#ifndef _FURIOUS_TABLE_IMPL_H_
#define _FURIOUS_TABLE_IMPL_H_ 

#include "common.h"
#include "btree.h"
#include <vector>
#include <string>
#include <set>

namespace furious {


/**
 * @brief The number of elements per block. The current number, 16 is not
 * arbitrarily chosen. Assuming a cahce line of 64 bytes long, 16 4byte elements
 * can be stored in a line.
 */
constexpr size_t TABLE_BLOCK_SIZE = 512;
constexpr size_t TABLE_BLOCK_BITMAP_SIZE=(TABLE_BLOCK_SIZE + 7) >> 3;

/**
 * @brief Represents a block of data in a table
 */
struct TBlock {
  uint8_t*          p_data;                           // The pointer to the block data
  uint32_t          m_start;                          // The id of the first element in the block
  size_t            m_size;
  uint32_t          m_esize;
  uint8_t           m_exists[TABLE_BLOCK_BITMAP_SIZE];  // A vector of bits used to test whether an element is in the block or not
};

/**
 * @brief Tests if a block contains element with the given id
 *
 * @param block The block to check the element
 * @param id The id of the element to check
 *
 * @return Returns true if the block contains such element
 */
bool has_element(const TBlock* block, uint32_t id);


/**
 * @brief Gets the element of a block
 *
 * @param block The block to get the element from
 *
 * @return Returns a pointer to the element. Returns nullptr if the element does
 * not exist in the block
 */
void* get_element(const TBlock* block, uint32_t id);

class Table {

public:
  class Iterator {
  public:
    Iterator(BTree<TBlock>* btree);
    virtual ~Iterator();

    /**
     * @brief Checks whether there is a another block in the table.
     *
     * @return Returns true if there is another block in the table.
     */
    bool has_next() const;

    /**
     * @brief Gets the next block in the table
     *
     * @return Returns the next block in the table. Returns nullptr if it does
     * not exist
     */
    TBlock* next();
    
  private:
    BTree<TBlock>::Iterator* p_iterator;
  };


public:
  Table(const std::string& name, size_t esize);
  virtual ~Table();

  /**
   * @brief Clears the table
   */
  void clear();

  /**
   * @brief Gets the element with the given id
   *
   * @param id The id of the element to get
   *
   * @return Returns a pointer to the element. Returns nullptr if the element
   * does not exist in the table
   */
  void* get_element(uint32_t id) const ;

  /**
   * @brief Copies the contents of the pointed element and inserts it to the
   * table with the given id
   *
   * @param id The id of the element
   * @param element A pointer to the element to copy
   */
  void  insert_element(uint32_t id, void* element);

  /**
   * @brief Drops the element with the given id
   *
   * @param id
   */
  void  drop_element(uint32_t id);

  /**
   * @brief Gets an iterator of the table
   *
   * @return Returns an iterator of the table.
   */
  Iterator* iterator();

  /**
   * @brief Gets the name of the table
   *
   * @return Returns the name of the able
   */
  std::string table_name() const;

  size_t size() const;

private:
  std::string              m_name;   // The name of the table
  size_t                   m_esize;  // The size of each element in bytes
  BTree<TBlock>*           p_btree;  // A BTree storing the blocks of the table          
  size_t                   m_num_elements;
};


} /* furious */ 

#endif

