


#include <data/logic_map.h>

namespace furious {
namespace data {

LogicMap::LogicMap( SystemId system, LogicPlanNodePtr table ) : 
  m_system(system), 
  p_table(table) {

  }

void LogicMap::accept( LogicPlanVisitor& visitor ) { 
  visitor.visit(*this); 
};

std::string LogicMap::str() const { 
  std::stringstream ss;
  ss << "LogicMap(" << m_system << ")";
  return ss.str();
};

uint32_t LogicMap::num_children() const { 
  return 1; 
};

LogicPlanNodePtr LogicMap::child( uint32_t i ) const { 
  assert(i == 0);
  return p_table;
};


} /* data */ 
} /* furious */ 
