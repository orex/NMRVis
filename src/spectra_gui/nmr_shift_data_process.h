/* 
 * File:   nmr_shift_data_process.h
 * Author: kirill
 *
 * Created on September 17, 2013, 1:09 PM
 */

#ifndef NMR_SHIFT_DATA_PROCESS_H
#define	NMR_SHIFT_DATA_PROCESS_H

#include "nmr_shift_data.h"
#include <set>

class nmr_shift_data_process : public nmr_shift_data
{
protected:
public:
  nmr_shift_data_process();
  void process();
  std::set<std::string> get_elem_symbols();
  std::vector<nmr_shift_item> get_elem_by_symbol(const std::string &symb);
  virtual ~nmr_shift_data_process();
public:
  static std::pair<double, double> get_range_by_elem(const std::string &symb);
};

#endif	/* NMR_SHIFT_DATA_PROCESS_H */

