

#include <cassert>
#include <utility>
#include "memory/memory.h"

namespace furious {

extern uint8_t bitmap_masks[8];

template<typename TComponent, typename...Args>
  void  Table::insert_element(uint32_t id, Args&&...args) {
    
    assert(sizeof(TComponent) == this->m_esize);
    BTree<TBlock>* btree = get_btree(id);
    uint8_t block_id = id / TABLE_BLOCK_SIZE;
    TBlock* block = btree->get(block_id);
    if (block == nullptr) {
      block = new TBlock();
      block->p_data = static_cast<uint8_t*>(numa_alloc(0, m_esize*TABLE_BLOCK_SIZE ));
      block->m_start = id / TABLE_BLOCK_SIZE * TABLE_BLOCK_SIZE;
      block->m_num_elements = 0;
      block->m_esize = m_esize;
      memset(&block->m_exists[0], '\0', TABLE_BLOCK_BITMAP_SIZE);
      btree->insert(block_id, block);
    }
    uint32_t offset = id - block->m_start;
    uint32_t bitmap_offset = offset / (sizeof(uint8_t)*8);
    uint32_t mask_index = offset % (sizeof(uint8_t)*8);
    if((block->m_exists[bitmap_offset] & bitmap_masks[mask_index]) == 0x00) {
      m_num_elements++;
      block->m_num_elements++;
    }
    block->m_exists[bitmap_offset] = block->m_exists[bitmap_offset] | bitmap_masks[mask_index];
    new (&block->p_data[offset*m_esize]) TComponent{std::forward<Args>(args)...};
  }
  
} /* furious  */ 
