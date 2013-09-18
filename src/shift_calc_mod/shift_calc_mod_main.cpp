/* 
 * File:   shift_calc_mod_main.cpp
 * Author: kirill
 *
 * Created on August 27, 2013, 1:17 PM
 */

#include <cstdlib>
#include <vector>
#include <iostream>
#include <iomanip>

#include <execinfo.h>
#include <signal.h>

#include <boost/format.hpp>
#include <boost/regex.hpp>

#include <flowvr/module.h>
#include <fstream>
#include "port_data_base.h"

#include "proj_folders.h"

#include "others/file_utils.h"

#include "nmr_shift_data_parse.h"

using namespace std;
using namespace flowvr;

void handler(int sig) 
{
  void *array[10];
  size_t size;

  // get void*'s for all entries on the stack
  size = backtrace(array, 10);

  // print out all the frames to stderr
  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

/*
 * 
 */
int main(int argc, char** argv)
{
  signal(SIGTERM, handler);
  
  flowvr::InputPort  p_pdb_in("pdb_in");
  flowvr::OutputPort p_spc_out("spc_out");
  
  std::vector<flowvr::Port*> ports;
  ports.push_back(&p_pdb_in);
  ports.push_back(&p_spc_out);
  
  flowvr::ModuleAPI* flowvr_api = flowvr::initModule(ports);

  if (flowvr_api == NULL)
    return 1;

  int it=0;
  
  cout << "Spectra calculator started" << endl;
  
  while (flowvr_api->wait())
  {

    flowvr::Message m_pdb_in;
    flowvr_api->get(&p_pdb_in, m_pdb_in);

    string pdb_str_old;

    parse_message(m_pdb_in, pdb_str_old);
    
    string pdb_str = nmr_shift_data_parse::correct_pdb(pdb_str_old);
    
    nmr_shift_data_parse nsp;
    
    nsp.parse_pdb(pdb_str);
    
    string t_pdb_file_name = get_temporary_file_name("", "sh2_", ".pdb");
    //string t_pdb_tmp_name = get_temporary_file_name("", "sh2_", ".pdb");
    
    ofstream t_pdb_file(t_pdb_file_name.c_str(), ofstream::out);
    //ofstream t_pdb_tmp(t_pdb_tmp_name.c_str(), ofstream::out);
    
    
    //t_pdb_tmp << pdb_str_old;
    
    t_pdb_file << pdb_str;

    //string cmd_str = boost::str( 
    //        boost::format("kdiff3 %1% %2%")
    //        % t_pdb_tmp_name 
    //        % t_pdb_file_name );

    
    string cmd_str = boost::str( 
            boost::format("python %1%/shiftx2.py -i %2% -e")
            % SHIFT_CALC_PROJECT_FOLDER 
            % t_pdb_file_name );
    
    int rc_sh2 = system(cmd_str.c_str());
    
    if(rc_sh2 == 0)
    {  
      cout << "spectra calculated" << endl;
      string cs_str = readAllFiletoString(t_pdb_file_name + ".cs");
      nsp.add_shifts(cs_str);
    }
    
    flowvr::MessageWrite * m_pdb_out = create_message(flowvr_api, nsp);

    flowvr_api->put(&p_spc_out, *m_pdb_out);

    delete m_pdb_out;    

    ++it;
  }

  flowvr_api->close();

  return 0;
  
}

