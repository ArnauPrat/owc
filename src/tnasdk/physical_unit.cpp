

#include <physical_unit.h>

namespace tnasdk {

PhysicalUnit::PhysicalUnit( uint8_t num_ranks, 
                            uint8_t num_files,
                            uint8_t troop_width,
                            uint8_t troop_height) :
  m_num_ranks(num_ranks),
  m_num_files(num_files),
  m_troop_width(troop_width),
  m_troop_height(troop_height)
{
  m_toop_mask.resize(m_num_ranks*m_num_files,false);
}

} /* tnasdk */ 
