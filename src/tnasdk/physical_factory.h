

#ifndef _TNASDK_PHYSICAL_FACTORY_H_
#define _TNASDK_PHYSICAL_FACTORY_H_

namespace tnasdk {

class PhysicalUnit;

class PhysicalFactory {
public:
  PhysicalFactory () = default;
  virtual ~PhysicalFactory () = default;

  /**
   * @brief Creates a physical unit
   *
   * @param num_ranks The number of ranks of the physical unit
   * @param num_files The number of files of the physical unit
   *
   * @return Returns a newly created physical unit
   */
  virtual PhysicalUnit* create_punit( uint8_t num_ranks,
                                      uint8_t num_files) = 0;

  /**
   * @brief Destroys an existing physical unit
   *
   * @param punit A pointer to the physical unit to destroy
   */
  virtual void destroy_punit( PhysicalUnit* punit ) = 0;


};

} /* tnasdk */ 
#endif /* _TNASDK_PHYSICAL_FACTORY_H_ */
