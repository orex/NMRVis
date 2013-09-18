/* 
 * File:   nmr_shift_data_parse.cpp
 * Author: kirill
 * 
 * Created on September 11, 2013, 3:43 PM
 */

#include "nmr_shift_data_parse.h"

#include <boost/regex.hpp>
#include <boost/format.hpp>
#include <scanf_pp/base.hpp>

#include "others/string_utils.h"
#include "scanf_pp/base.hpp"

using namespace std;
using namespace boost;

std::string nmr_shift_data_parse::correct_pdb(const std::string &pdb_str)
{
  const regex re("^(ATOM\\s*\\d*\\s*)OC\\d(.{1,3}GLY)");
  const string new_format("\\1O  \\2"); 
  return regex_replace(pdb_str, re, new_format, match_default | boost::format_all);
}


nmr_shift_data_parse::nmr_shift_data_parse()
{
}



bool nmr_shift_data_parse::parse_pdb(const std::string &pdb_str)
{
  regex re_atom_find("^ATOM.{40,80}$");
  //regex re_atom("ATOM\\s*([0-9]+)\\s+(\\w+)\\s+(\\w+)\\s+(\\d+)\\s+.{25,65}$");
  
  sregex_token_iterator it(pdb_str.begin(), pdb_str.end(), re_atom_find);
  sregex_token_iterator it_end;
  
  items.clear(); 
  
  scanf_pp::regex_scanf rs("ATOM\\s*([0-9]+)\\s+(\\w+)\\s+(\\w+)\\s+(\\d+)\\s+.{25,65}$");
  scanf_pp::regex_scanf r_elem("\\s*\\d?([CHNOS])\\w*\\s*");  
  for(; it != it_end; ++it)
  {
    smatch what;
    bool regex_matched = rs.regex_match(*it);
    assert(regex_matched);
    
    nmr_shift_item nh;
    
    rs >> nh.atom_index >> nh.atom_name >> nh.res_name >> nh.res_index;
    
    if(! r_elem.regex_match(nh.atom_name) )
    {
      cout << "Unknown element: " << nh.atom_name << endl;
    }
    else
      r_elem >> nh.elem_symbol;
    
    //boost::format
    items.push_back(nh);
  } 
}

void nmr_shift_data_parse::add_shift(int res_index, std::string atom_name, double shift)
{
  int it_find;
  int count = 0;
  
  map<int, int> mult_find;
  mult_find.clear();

  scanf_pp::regex_scanf rs1(atom_name + "(\\d)");
  scanf_pp::regex_scanf rs2("(\\d)" + atom_name);
  for(int i = 0; i < items.size(); i++)
  {
    if( items[i].res_index == res_index )
    {  
       if( items[i].atom_name == atom_name ) 
       {
         it_find = i;
         count++;
       }
       
       if( rs1.regex_match(items[i].atom_name) )
       {
         int index;
         rs1 >> index;
         mult_find[index] = i;
       }
       if( rs2.regex_match(items[i].atom_name) )
       {
         int index;
         rs2 >> index;
         mult_find[index] = i;
       }
    }
  }
  
  string shift_name = boost::lexical_cast<string>(res_index) + "_" + atom_name;
  
  if(count == 0)
  {  
    if( (mult_find.size() == 3) && mult_find.count(1) * mult_find.count(2) * mult_find.count(3) > 0)
    {
      for(int i = 1; i <= 3; i++)
        items[mult_find[i]].shift = shift;
    }
    else
      cout << "WARNING: Shift is not assigned: " << shift_name << endl;
  }  
 
  if(count > 1)
    cout << "WARNING: Multiple assignment: " << shift_name << endl;
  
  if(count == 1)
  {
    if(items[it_find].shift.assigned())
      cout << "WARNING: Shift assigned: " << shift_name << endl;
    else
      items[it_find].shift = shift;
  }
}

bool nmr_shift_data_parse::add_shifts(const std::string &shiftx2_str)
{
  vector<string> lines = split_string_vector(shiftx2_str, "\n");
  
  scanf_pp::regex_scanf rs("(\\d+),(\\w+),(\\w+),([\\.\\d]+)");
  for(int i = 1; i < lines.size(); i++)
  {
    bool matched = rs.regex_match(lines[i]);
    assert(matched);
    
    int res_index;
    string atom_name;
    double shift;
    
    rs >> res_index >> NULL >> atom_name >> shift;    
    
    add_shift(res_index, atom_name, shift);
  }  
}

nmr_shift_data_parse::~nmr_shift_data_parse()
{
}

