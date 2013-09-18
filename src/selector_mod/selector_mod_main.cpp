#include <vector>
#include <iostream>

#include <flowvr/module.h>
#include <unistd.h>
#include "port_data_base.h"

using namespace std;

int main(int argc, const char** argv)
{
  flowvr::InputPort  p_ids_in("ids_in");
  p_ids_in.setNonBlockingFlag(true);
  
  flowvr::OutputPort p_ids_out("ids_out");
  std::vector<flowvr::Port*> ports;
  ports.push_back(&p_ids_in);
  ports.push_back(&p_ids_out);
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
    
    flowvr::Message m_in;
    
    flowvr_api->get(&p_ids_in, m_in);
    
    if(m_in.data.getSize() > 0)
      flowvr::parse_message(m_in, test_ids);
    
    //for(int i = 0; i < 5; i++)
      //test_ids.push_back(rand() % 20);
    
    if(it % 60 == 0)
      test_ids.clear();
    
    flowvr::MessageWrite * m = flowvr::create_message(flowvr_api, test_ids);
    
    // Send message
    flowvr_api->put(&p_ids_out, *m);
    
    delete m;

    // Log info
    usleep(1E5);
    ++it;
  }

  flowvr_api->close();

  return 0;
}
