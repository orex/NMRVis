/* 
 * File:   c_flowvr_event_loop.cpp
 * Author: kirill
 * 
 * Created on August 21, 2013, 5:19 PM
 */

#include "c_flowvr_event_loop.h"
#include "port_data_base.h"
#include "nmr_shift_data_process.h"
#include <algorithm>

#include <vector>

#include <QtCore/QDebug>

//#include "port_data_base.h"

using namespace std;

void c_flowvr_event_loop::execute()
{
  ofs_log << "My enter" << endl;
  
  int it = 0;
  
  vector<int> select_old;

  int curr_spc_message = -1;
  
  while ( flowvr_var->wait() && (! _terminate) )
  {
    // Get Message
    
    cout << "Inside flowvr loop" << endl;
    ofs_log << "My flowvr" << endl;
    
    flowvr::Message m_spc_in;
    flowvr_var->get(p_spc_in, m_spc_in);
    
    int mit;
    m_spc_in.stamps.read(p_spc_in->stamps->it, mit);
    
    if( (curr_spc_message != mit) && (!m_spc_in.data.empty()))
    {
      cout << "New spectra Signal sent" << endl;
      nmr_shift_data_process * nmrp = new nmr_shift_data_process;
      
      flowvr::parse_message(m_spc_in, *nmrp);
      
      cout << "New spectra Signal sent" << endl;
      emit flowvr_new_spc(nmrp);
      
      curr_spc_message = mit;  
    }  

    ++it;
  }
  
  ofs_log << "My exit" << endl;  
  
  flowvr_var->close();
  
  emit flowvr_terminated();
}

void c_flowvr_event_loop::flowvr_terminate() 
{ 
  qDebug() << "About to quit";
  _terminate = true; 
}

c_flowvr_event_loop::c_flowvr_event_loop(QApplication &app, QThread &thread)
{
  connect(this, SIGNAL(flowvr_terminated()), &app, SLOT(quit()));  
  connect(&thread, SIGNAL(started()), this, SLOT(execute()));
  connect(this, SIGNAL(flowvr_terminated()), &thread, SLOT(deleteLater()));  

  _terminate = false;
  p_ids_in = NULL;
  p_ids_out = NULL;
  p_spc_in = NULL;
  flowvr_var = NULL;
}

bool c_flowvr_event_loop::initialize_flowvr()
{
  ofs_log.open("/home/kirill/temp/flowver.log", fstream::out);
  
  //pSelect = new flowvr::InputPort("test_ids");      
  
  //ports.push_back(pSelect);
  
  p_spc_in = new flowvr::InputPort("spc_in");
  ports.push_back(p_spc_in);
  
  p_ids_in  = new flowvr::InputPort("ids_in");
  ports.push_back(p_ids_in);
  
  p_ids_out = new flowvr::OutputPort("ids_out");
  ports.push_back(p_ids_out);
  
  flowvr_var = flowvr::initModule(ports);
  return flowvr_var != NULL;
}

c_flowvr_event_loop::c_flowvr_event_loop(const c_flowvr_event_loop& orig)
{
}

c_flowvr_event_loop::~c_flowvr_event_loop()
{
}

    //flowvr::Message mSelect;
    //flowvr_var->get(pSelect,  mSelect);
    
    
    
    /*
    flowvr::Message mSelect;
    flowvr_var->get(pSelect,  mSelect);

    // Read data
    vector<int> select;
    
    flowvr::parse_message(mSelect, select);    
    
    bool new_selection = lexicographical_compare(select.begin(), select.end(), 
                                                 select_old.begin(), select_old.end()) ||
                         lexicographical_compare(select_old.begin(), select_old.end(), 
                                                 select.begin(), select.end());    
    cout << "Recieved: " << endl;
    for(int i = 0; i < select.size(); i++)
      cout << select[i] << " " ;
    
    cout << endl;
        
    if( new_selection )
    {  
      select_old = select;
      QVector<int> select_ids = QVector<int>::fromStdVector(select);
      
      ofs_log << "Before emit" << endl;
      emit flowvr_new_selection( select_ids );
      ofs_log << "After emit" << endl;      
    }  
    
    usleep(1E5);
    */
