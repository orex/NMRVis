/******* COPYRIGHT ************************************************
*                                                                 *
*                             FlowVR                              *
*                     Application Library                         *
*                                                                 *
*-----------------------------------------------------------------*
 * COPYRIGHT (C) 2003-2011                by                       *
* INRIA                                                           *
* ALL RIGHTS RESERVED.	                                          *
*                                                                 *
* This source is covered by the GNU LGPL, please refer to the     *
* COPYING file for further information.                           *
*                                                                 *
*-----------------------------------------------------------------*
*                                                                 *
*  Original Contributors:                                         *
*    Jeremie Allard,                                              *
*    Thomas Arcila,                                               *
*    Jean-Denis Lesage.                                           *
*    Clement Menier,                                              *
*    Bruno Raffin                                                 *
*                                                                 *
*******************************************************************
*                                                                 *
* File: put.cpp                                                   *
*                                                                 *
* Contacts:                                                       *
*  26/02/2004 Jeremie Allard <Jeremie.Allard@imag.fr>             *
*                                                                 *
******************************************************************/
#include <vector>
#include <iostream>

#include <flowvr/module.h>
#include <unistd.h>
#include "port_data_base.h"

using namespace std;

int main(int argc, const char** argv)
{
  flowvr::OutputPort pOut("test_ids");
  std::vector<flowvr::Port*> ports;
  ports.push_back(&pOut);
  flowvr::ModuleAPI* flowvr_api = flowvr::initModule(ports);
  if (flowvr_api == NULL)
  {
    return 1;
  }

  int it=0;
  while (flowvr_api->wait())
  {
    // Build data
    vector<int> test_ids;
    
    for(int i = 0; i < 5; i++)
      test_ids.push_back(rand() % 20);
    
    flowvr::MessageWrite * m = flowvr::create_message(flowvr_api, test_ids);
    
    // Send message
    flowvr_api->put(&pOut, *m);
    
    delete m;

    // Log info
    int mit;
    m->stamps.read(pOut.stamps->it,mit);
    
    cout<<"Sent " << " (it="<< mit <<")" << endl;

    sleep(1);
    ++it;
  }

  flowvr_api->close();

  return 0;
}
