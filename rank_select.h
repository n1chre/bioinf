//
// Created by Zvonimir Medic on 28/12/2016.
//

#ifndef BIOINF_TREE_H
#define BIOINF_TREE_H

#include <cstdint>

/**
 * Interface that supports rank and select operations
 */
class rank_select {
 public:

  /**
   * @return number of elements equal to elem found on indexes smaller than idx
   */
  virtual const uint32_t rank(char elem, uint32_t idx) const = 0;

  /**
   * @return index of idx-th elem
   */
  virtual const uint32_t select(char elem, uint32_t idx) const = 0;
};

#endif //BIOINF_TREE_H
