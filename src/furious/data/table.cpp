

#include "table.h"
#include <cmath>

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
  uint32_t block_id = id / TABLE_BLOCK_SIZE;
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

Table::Iterator::Iterator(std::vector<BTree<TBlock>*>* btrees) : 
  m_next_btree(0),
  p_btrees(btrees),
  p_iterator((*p_btrees)[m_next_btree]->iterator())
{
  m_next_btree++;
}

Table::Iterator::~Iterator() {
  delete p_iterator;
}

bool Table::Iterator::advance_iterator() const {
  while(m_next_btree < p_btrees->size() && (*p_btrees)[m_next_btree] == nullptr) {
    m_next_btree++;
  }

  if(m_next_btree < p_btrees->size()) {
    delete p_iterator;
    p_iterator = (*p_btrees)[m_next_btree]->iterator();
    m_next_btree++;
    return true;
  } 
  return false;
}

bool Table::Iterator::has_next() const { 
  if(!p_iterator->has_next()) {
    if(advance_iterator()) {
      return p_iterator->has_next();
    }
    return false;
  }
  return true;
}

TBlock* Table::Iterator::next() {
  TBlock* next = p_iterator->next();
  if(next == nullptr) {
    advance_iterator();
    return p_iterator->next();
  }
  return next;
}

Table::Table(std::string& name, size_t esize) :
  m_name(name),
  m_esize(esize),
  m_num_elements(0) {
    m_btrees.push_back(new BTree<TBlock>());
  }

Table::Table(std::string&& name, size_t esize) :
  m_name(name),
  m_esize(esize),
  m_num_elements(0) {
    m_btrees.push_back(new BTree<TBlock>());
  }

Table::~Table() {
  for (auto btree : m_btrees) {
    if(btree != nullptr) {
      auto iterator = btree->iterator();
      while(iterator->has_next()) {
        TBlock* block = iterator->next();
        numa_free(block->p_data);
        delete block;
      }
      delete btree;
    }
  }
}

size_t Table::size() const {
  return m_num_elements;
}

void Table::clear() {
  for (auto btree : m_btrees) {
    if(btree != nullptr) {
      BTree<TBlock>::Iterator * iterator = btree->iterator();
      while(iterator->has_next()) {
        delete iterator->next();
      }
      btree->clear();
    }
  }
  m_num_elements = 0;
}

BTree<TBlock>* Table::get_btree(uint32_t id) const {
  uint32_t btree_bits = sizeof(uint8_t)*8;
  uint32_t block_bits = std::log2(TABLE_BLOCK_SIZE);
  uint32_t btree_index = id >> (btree_bits + block_bits);
  if(btree_index >= m_btrees.size()) {
    m_btrees.resize(btree_index+1, nullptr);
  }
  if(m_btrees[btree_index] == nullptr) {
    m_btrees[btree_index] = new BTree<TBlock>();
  }
  return m_btrees[btree_index];
}

void* Table::get_element(uint32_t id) const {
  BTree<TBlock>* btree = get_btree(id);
  uint8_t block_id = id / TABLE_BLOCK_SIZE;
  TBlock* block = btree->get(block_id);
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

void* Table::alloc_element(uint32_t id) {
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
  return &block->p_data[offset*m_esize];
}

void  Table::remove_element(uint32_t id) {
  BTree<TBlock>* btree = get_btree(id);
  uint8_t block_id = id / TABLE_BLOCK_SIZE;
  TBlock* block = btree->get(block_id);
  if (block == nullptr) {
    return;
  }
  uint32_t offset = id - block->m_start;
  uint32_t bitmap_offset = offset / (sizeof(uint8_t)*8);
  uint32_t mask_index = offset % (sizeof(uint8_t)*8);
  if((block->m_exists[bitmap_offset] & bitmap_masks[mask_index]) != 0x00) {
    m_num_elements--;
    block->m_num_elements--;
  }
  block->m_exists[bitmap_offset] = block->m_exists[bitmap_offset] & ~(bitmap_masks[mask_index]);
  memset(&block->p_data[offset*m_esize], '\0', m_esize);
}

Table::Iterator* Table::iterator() {
  return new Iterator{&m_btrees};
}

std::string Table::table_name() const {
  return m_name;
}
  
} /* furious */ 
