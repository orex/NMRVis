/*
 * File:   NMRVis.cpp
 * Author: kirill
 *
 * Created on August 20, 2013, 5:06 PM
 */

#include <iostream>
#include <fstream>

#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>

#include <QtGui/QApplication>
#include <QtCore/QThread>
#include <QMetaType>

#include "nmr_plot.h"
#include "c_flowvr_event_loop.h"
#include "nmr_shift_data_process.h"

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

int main(int argc, char *argv[])
{
  signal(SIGSEGV, handler);
  // initialize resources, if needed
  // Q_INIT_RESOURCE(resfile);

  QApplication app(argc, argv);
  
  // create and show your widgets here
  
  nmr_plot * main_window = new nmr_plot();
  QThread * flowvr_thread = new QThread();
  c_flowvr_event_loop * flowvr_loop = new c_flowvr_event_loop(app, *flowvr_thread);

  qRegisterMetaType< QVector<int> >("QVector<int>");
  
  QObject::connect(flowvr_loop, SIGNAL(flowvr_new_selection( QVector<int> )), main_window, SLOT(new_selection( QVector<int> )));
  QObject::connect(flowvr_loop, SIGNAL(flowvr_new_spc(nmr_shift_data_process * )), main_window, SLOT(new_spc(nmr_shift_data_process * )));
  
  //Qt signal aboutToQuit() is not emmited bu unknown reason.
  //QObject::connect(&app, SIGNAL(aboutToQuit()), flowvr_loop, SLOT(flowvr_terminate()));
  //QObject::connect(&app, SIGNAL(aboutToQuit()), main_window, SLOT(quit_rec()));  
  
  if(! flowvr_loop->initialize_flowvr() )
    return 1;

  flowvr_loop->moveToThread(flowvr_thread);
  flowvr_thread->start();

  main_window->show();
  
  int result = app.exec();
  
  flowvr_loop->flowvr_terminate();
  
  while(flowvr_thread->isRunning() )
    sleep(1);
  
  delete flowvr_loop;
  delete main_window;
  delete flowvr_thread;  
  
  return result;  
}
