
#include <data/logic_scan.h>

namespace furious {
namespace data {

LogicScan::LogicScan(TableId table) : 
  m_table(table) {
  }

void LogicScan::accept( LogicPlanVisitor& visitor ) { 
  visitor.visit(*this);
};

std::string LogicScan::str() const { 
  std::stringstream ss;
  ss << "LogicScan(" << m_table << ")";
  return ss.str();
};

uint32_t LogicScan::num_children() const { 
  return 0; 
};

LogicPlanNodePtr LogicScan::child( uint32_t i ) const { 
  assert(false);
  return nullptr;
};

} /* data */ 
} /* furious */ 
