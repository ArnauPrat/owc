

#include "table.h"
#include "memory/memory.h"
//#include <stdio.h>

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

bool has_element(const TBlock* block, uint32_t id) {
  return get_element(block, id) != nullptr;
}

void* get_element(const TBlock* block, uint32_t id) {
  assert(id < TABLE_BLOCK_SIZE*256);
  uint8_t block_id = id / TABLE_BLOCK_SIZE;
  if (block->m_start != block_id * TABLE_BLOCK_SIZE) {
    return nullptr;
  }
  uint32_t offset = id - block->m_start;
  uint32_t bitmap_offset = offset / (sizeof(uint8_t)*8);
  uint32_t mask_index = offset % (sizeof(uint8_t)*8);
  if((block->m_exists[bitmap_offset] & bitmap_masks[mask_index]) != 0x00) {
    return &block->p_data[offset*block->m_esize];
  }
  return nullptr;
}

Table::Iterator::Iterator(BTree<TBlock>* p_btree) : 
  p_iterator(p_btree->iterator())
{
}

Table::Iterator::~Iterator() {
  delete p_iterator;
}

bool Table::Iterator::has_next() const {
  return p_iterator->has_next();
}

TBlock* Table::Iterator::next() {
  return p_iterator->next();
}

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

size_t Table::size() const {
  return m_num_elements;
}

void Table::clear() {
  BTree<TBlock>::Iterator * iterator = p_btree->iterator();
  while(iterator->has_next()) {
    delete iterator->next();
  }
  p_btree->clear();
  m_num_elements = 0;
}

void* Table::get_element(uint32_t id) const {
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
    return &block->p_data[offset*m_esize];
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
    block->m_size = 0;
    block->m_esize = m_esize;
    memset(&block->m_exists[0], '\0', TABLE_BLOCK_BITMAP_SIZE);
    p_btree->insert(block_id, block);
  }
  uint32_t offset = id - block->m_start;
  uint32_t bitmap_offset = offset / (sizeof(uint8_t)*8);
  uint32_t mask_index = offset % (sizeof(uint8_t)*8);
  if((block->m_exists[bitmap_offset] & bitmap_masks[mask_index]) == 0x00) {
    m_num_elements++;
    block->m_size++;
  }
  block->m_exists[bitmap_offset] = block->m_exists[bitmap_offset] | bitmap_masks[mask_index];
  memcpy(&block->p_data[offset*m_esize], element, m_esize);
}

void  Table::drop_element(uint32_t id) {
  assert(id < TABLE_BLOCK_SIZE*256);
  uint8_t block_id = id / TABLE_BLOCK_SIZE;
  TBlock* block = p_btree->get(block_id);
  if (block == nullptr) {
    return;
  }
  uint32_t offset = id - block->m_start;
  uint32_t bitmap_offset = offset / (sizeof(uint8_t)*8);
  uint32_t mask_index = offset % (sizeof(uint8_t)*8);
  if((block->m_exists[bitmap_offset] & bitmap_masks[mask_index]) != 0x00) {
    m_num_elements--;
    block->m_size--;
  }
  block->m_exists[bitmap_offset] = block->m_exists[bitmap_offset] & ~(bitmap_masks[mask_index]);
  memset(&block->p_data[offset*m_esize], '\0', m_esize);
}

Table::Iterator* Table::iterator() {
  return new Iterator{p_btree};
}

std::string Table::table_name() const {
  return m_name;
}
  
} /* furious */ 
