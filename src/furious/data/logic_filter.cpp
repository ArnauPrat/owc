

#include <data/logic_filter.h>

namespace furious {
namespace data {

LogicFilter::LogicFilter(LogicPlanNodePtr table) : p_table(table) {
}

void LogicFilter::accept( LogicPlanVisitor& visitor ) { 
  visitor.visit(*this); 
};

std::string LogicFilter::str() const { 
  std::stringstream ss;
  ss << "LogicFilter()";
  return ss.str();
};

uint32_t LogicFilter::num_children() const { 
  return 1; 
};

LogicPlanNodePtr LogicFilter::child( uint32_t i ) const { 
  assert(i == 0);
  return p_table;
};
  
} /* data */ 
} /* furious  */ 
