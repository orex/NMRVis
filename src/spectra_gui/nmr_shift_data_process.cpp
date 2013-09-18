/* 
 * File:   nmr_shift_data_process.cpp
 * Author: kirill
 * 
 * Created on September 17, 2013, 1:09 PM
 */

#include "nmr_shift_data_process.h"

#include <map>

using namespace std;

nmr_shift_data_process::nmr_shift_data_process()
{
}

std::set<std::string> nmr_shift_data_process::get_elem_symbols()
{
  std::set<std::string> result;
  
  for(int i = 0; i < items.size(); i++)
    result.insert(items[i].elem_symbol);
  
  return result;
}

std::vector<nmr_shift_item> nmr_shift_data_process::get_elem_by_symbol(const std::string &symb)
{
  std::vector<nmr_shift_item> result;
  
  for(int i = 0; i < items.size(); i++)
  {
    if(items[i].elem_symbol == symb)
      result.push_back(items[i]);
  }  
  
  return result;
}

nmr_shift_data_process::~nmr_shift_data_process()
{
}

std::pair<double, double> nmr_shift_data_process::get_range_by_elem(const std::string &symb)
{
  std::pair<double, double> result(0,0);
  
  std::map<string, std::pair<double, double> > range_ppm;
  
  range_ppm["H"] = make_pair(-1, 12);
  range_ppm["Li"] = make_pair(-10, 5);
  range_ppm["Li"] = make_pair(-10, 5);
  range_ppm["B"] = make_pair(-120, 100);
  range_ppm["C"] = make_pair(-10, 240);
  range_ppm["N"] = make_pair(-500, 1200);
  range_ppm["O"] = make_pair(-100, 1400);
  range_ppm["F"] = make_pair(-300, 100);
  range_ppm["Na"] = make_pair(-60, 10);
  range_ppm["Al"] = make_pair(-200, 200);
  range_ppm["Si"] = make_pair(-400, 100);
  range_ppm["P"] = make_pair(-200, 230);
  range_ppm["Ca"] = make_pair(-140, 40);
  range_ppm["V"] = make_pair(-2000, 0);
  range_ppm["Zn"] = make_pair(-2700, 100);
  range_ppm["Se"] = make_pair(-1000, 1600);
  range_ppm["Nb"] = make_pair(-2000, 0);
  range_ppm["Ru"] = make_pair(-3000, 3000);
  range_ppm["Sn"] = make_pair(-3000, 5000);
  range_ppm["Sb"] = make_pair(-2700, 1000);
  range_ppm["Xe"] = make_pair(-6000, 2000);
  range_ppm["Cs"] = make_pair(-300, 300);
  range_ppm["Pt"] = make_pair(-6000, 9000);
  range_ppm["Hg"] = make_pair(-3000, 500);  
  
  if( range_ppm.count(symb) > 0)
    result = range_ppm[symb];
  
  return result;
}

