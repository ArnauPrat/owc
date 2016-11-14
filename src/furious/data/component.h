
#ifndef _FURIOUS_COMPONENT_H_
#define _FURIOUS_COMPONENT_H_  

namespace furious
{
  namespace data
  {

    class Component {
      public:
        /**
         * Gets the name of the component
         */
        virtual std::string name() = 0;
    };
    
  } /* data */ 
} /* furious */ 
#endif
