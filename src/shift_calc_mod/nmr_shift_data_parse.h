/* 
 * File:   nmr_shift_data_parse.h
 * Author: kirill
 *
 * Created on September 11, 2013, 3:43 PM
 */

#ifndef NMR_SHIFT_DATA_PARSE_H
#define	NMR_SHIFT_DATA_PARSE_H

#include "nmr_shift_data.h"
#include <string>


class nmr_shift_data_parse : public nmr_shift_data
{
public:
  static std::string correct_pdb(const std::string &pdb_str);
protected:
  void add_shift(int res_index, std::string atom_name, double shift);
public:
  nmr_shift_data_parse();
  bool parse_pdb(const std::string &pdb_str);
  bool add_shifts(const std::string &shiftx2_str);
  virtual ~nmr_shift_data_parse();
private:

};

#endif	/* NMR_SHIFT_DATA_PARSE_H */

