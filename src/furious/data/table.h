


#ifndef _FURIOUS_TABLE_H_
#define _FURIOUS_TABLE_H_ 

#include "common.h"
#include "common/btree.h"
#include <vector>
#include <string>
#include <set>

namespace furious {


/**
 * @brief The number of elements per block. The current number, 16 is not
 * arbitrarily chosen. Assuming a cahce line of 64 bytes long, 16 4byte elements
 * can be stored in a line.
 */
constexpr size_t BLOCK_SIZE = 16;

/**
 * @brief Represents a block of data in a table
 */
struct TBlock {
  uint8_t*          p_data;                           // The pointer to the block data
  uint32_t          m_start;                          // The id of the first element in the block
  uint8_t           m_exists[(BLOCK_SIZE + 7) >> 3];  // A vector of bits used to test whether an element is in the block or not
};


class Table {

public:
  Table(const std::string& name, size_t esize){}
  virtual ~Table() {}

  uint32_t size(); 

  void clear();

  void* get_element(uint32_t id);

  void drop_element(uint32_t id);

  std::string table_name() { return m_name; };

private:
  std::string                           m_name;   // The name of the table
  size_t                                m_esize;  // The size of each element in bytes
};

} /* furious */ 

#endif

