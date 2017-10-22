

#include "table.h"
#include "memory/memory.h"

namespace furious {

uint8_t bitmap_masks[8] = {0x01, 
                           0x02,
                           0x04,
                           0x08,
                           0x10,
                           0x20,
                           0x40,
                           0x80
};

Table::Table( const std::string& name, 
              size_t esize ) :
  m_name(name),
  m_esize(esize),
  p_btree(nullptr), 
  m_num_elements(0) {
    p_btree = new BTree<TBlock>();
  }

Table::~Table() {
  if(p_btree != nullptr) {
    auto iterator = p_btree->iterator();
    while(iterator->has_next()) {
      TBlock* block = iterator->next();
      numa_free(block->p_data);
      delete block;
    }
    delete p_btree;
    p_btree = nullptr;
  }
}

uint32_t Table::size() {
  return m_num_elements;
}

void Table::clear() {

}

void* Table::get_element(uint32_t id) {
  assert(id < TABLE_BLOCK_SIZE*256);
  uint8_t block_id = id / TABLE_BLOCK_SIZE;
  TBlock* block = p_btree->get(block_id);
  if (block == nullptr) {
    return nullptr;
  }
  uint32_t offset = id - block->m_start;
  uint32_t bitmap_offset = offset / sizeof(uint8_t);
  uint32_t mask_index = offset % sizeof(uint8_t);
  if((block->m_exists[bitmap_offset] & bitmap_masks[mask_index]) != 0x00) {
    return &block->p_data[offset];
  }
  return nullptr;
}

void  Table::insert_element(uint32_t id, void* element) {
  assert(id < TABLE_BLOCK_SIZE*256);
  uint8_t block_id = id / TABLE_BLOCK_SIZE;
  TBlock* block = p_btree->get(block_id);
  if (block == nullptr) {
    block = new TBlock();
    block->p_data = static_cast<uint8_t*>(numa_alloc(0, m_esize*TABLE_BLOCK_SIZE ));
    block->m_start = id / TABLE_BLOCK_SIZE * TABLE_BLOCK_SIZE;
    memset(&block->m_exists[0], '\0', TABLE_BLOCK_BITMAP_SIZE);
    p_btree->insert(block_id, block);
  }
  uint32_t offset = id - block->m_start;
  uint32_t bitmap_offset = offset / sizeof(uint8_t);
  uint32_t mask_index = offset % sizeof(uint8_t);
  if((block->m_exists[bitmap_offset] & bitmap_masks[mask_index]) == 0x00) {
    m_num_elements++;
  }
  block->m_exists[bitmap_offset] = block->m_exists[bitmap_offset] | bitmap_masks[mask_index];
  memcpy(&block->p_data[offset], element, m_esize);
}

void  Table::drop_element(uint32_t id) {
  assert(id < TABLE_BLOCK_SIZE*256);
  uint8_t block_id = id / TABLE_BLOCK_SIZE;
  TBlock* block = p_btree->get(block_id);
  if (block == nullptr) {
    return;
  }
  uint32_t offset = id - block->m_start;
  uint32_t bitmap_offset = offset / sizeof(uint8_t);
  uint32_t mask_index = offset % sizeof(uint8_t);
  if((block->m_exists[bitmap_offset] & bitmap_masks[mask_index]) != 0x00) {
    m_num_elements--;
  }
  block->m_exists[bitmap_offset] = block->m_exists[bitmap_offset] & ~(bitmap_masks[mask_index]);
  memset(&block->p_data[offset], '\0', m_esize);
}
  
} /* furious */ 
