/* 
 * File:   nmr_shift_data.h
 * Author: kirill
 *
 * Created on September 6, 2013, 11:10 AM
 */

#ifndef NMR_SHIFT_DATA_H
#define	NMR_SHIFT_DATA_H

#include <string>
#include <vector>

#include "assigned_variable/av_base.hpp"
#include "assigned_variable/av_serialize.hpp"

#include <boost/serialization/base_object.hpp>


class nmr_shift_item 
{
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {
    ar & atom_index;
    ar & elem_symbol;
    ar & atom_name;
    ar & res_name;
    ar & res_index;
    ar & shift;
  }
  
public:
  int atom_index;
  std::string elem_symbol;
  std::string atom_name;
  std::string res_name;
  int res_index;
  c_assigned_value<double> shift;
};

class nmr_shift_data 
{
  friend class boost::serialization::access;
  
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version)
  {  ar & items;  }
  
protected:
  std::vector<nmr_shift_item> items;
public:
  nmr_shift_data() {};
  virtual ~nmr_shift_data() {};
private:
};

#endif	/* NMR_SHIFT_DATA_H */

