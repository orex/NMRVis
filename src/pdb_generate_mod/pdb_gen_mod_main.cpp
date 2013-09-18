/* 
 * File:   pdb_gen_mod_main.cpp
 * Author: kirill
 *
 * Created on August 29, 2013, 10:58 AM
 */

#include <vector>
#include <iostream>

#include <boost/filesystem.hpp>

#include <flowvr/module.h>
#include <unistd.h>
#include "port_data_base.h"

#include "others/file_utils.h"
#include "others/rnd_utils.h"

#include "proj_folders.h"

using namespace std;
using namespace boost;
using namespace boost::filesystem;

int main(int argc, const char** argv)
{
  flowvr::OutputPort pOut("pdb_out");
  std::vector<flowvr::Port*> ports;
  ports.push_back(&pOut);
  flowvr::ModuleAPI* flowvr_api = flowvr::initModule(ports);

  if (flowvr_api == NULL)
    return 1;

  int it=0;
  
  mt19937 rnd_gen = create_rnd_gen();
  
  path example_folder(PDB_FRAMES_FOLDER);
            
  vector<path> ex_files;

  copy(directory_iterator(example_folder), 
       directory_iterator(), back_inserter(ex_files));

  cout << "PDB Gen started" << endl;
  cout << argv[1] << endl;
  
  while (flowvr_api->wait())
  {
    cout << "PDB iter" << endl;
    
    string ex_file_name = ex_files[get_rnd_int_value_in_interval(rnd_gen, 0, ex_files.size() - 1)].string();
    
    // Build data
    string pdb_str = readAllFiletoString(ex_file_name.c_str());
    
    flowvr::MessageWrite * m = flowvr::create_message(flowvr_api, pdb_str);
    
    // Send message
    flowvr_api->put(&pOut, *m);
    
    delete m;

    // Log info
    //int mit;
    //m->stamps.read(pOut.stamps->it,mit);
    
    //cout<<"Sent " << " (it="<< mit <<")" << endl;

    sleep(10);
    ++it;
  }

  flowvr_api->close();

  return 0;
}
