//
// Created by Filip Hrenic on 28/12/2016.
//

#ifndef BIOINF_BITMASK_H
#define BIOINF_BITMASK_H

#include <cstdint>
#include <functional>

class bitmask;

/**
 * Interface that provides some methods needed by wavelet, such as rank0/1, select01...
 */
class bitmask {

 private:
  static std::function<bitmask *(uint32_t)> CREATOR;

 public:

  /**
   * @param creator used bitmask creator
   */
  static void set_creator(std::function<bitmask *(uint32_t)> creator);

  /**
   * Creates new bitmask
   *
   * @param size size of bitmask to create
   * @return created bitmask
   */
  static bitmask *create(uint32_t size);

  /**
   * Set idx-th bit to b
   *
   * @param idx index
   * @param b   value
   * @return this bitmask
   */
  virtual bitmask &set(uint32_t idx, bool b) = 0;

  /**
   * @param idx index
   * @return bit value at index
   */
  virtual const bool get(uint32_t idx) const = 0;

  /**
   * @param idx index
   * @param b   value
   * @return index of idx-th value b in this bitmask
   */
  virtual const uint32_t select01(uint32_t idx, bool b) const = 0;

  /**
   * @param idx index
   * @return number of 0's before given index
   */
  virtual const uint32_t rank0(uint32_t idx) const = 0;

  /**
   * @param idx index
   * @return numuber of 1's before given index
   */
  virtual const uint32_t rank1(uint32_t idx) const = 0;

  /**
   * @return size of bitmask
   */
  virtual const uint32_t size(void) const = 0;

};

#endif //BIOINF_BITMASK_H
