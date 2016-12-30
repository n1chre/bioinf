//
// Created by Zvonimir Medic on 28/12/2016.
//

#ifndef BIOINF_ZMEDI_NODE_H
#define BIOINF_ZMEDI_NODE_H

#include "data.h"

class balanced_node {
 private:
  data *d;
 public:
  balanced_node(data *d);
  const uint32_t get_count(char c) const;
  const wavelet *get_wave() const;
  const uint32_t get_starting_idx(void) const;
  const uint32_t get_ending_idx(void) const;
};

#endif //BIOINF_ZMEDI_NODE_H
