/* 
 * File:   c_flowvr_event_loop.h
 * Author: kirill
 *
 * Created on August 21, 2013, 5:19 PM
 */

#ifndef C_FLOWVR_EVENT_LOOP_H
#define	C_FLOWVR_EVENT_LOOP_H

#include <QtCore/QObject>
#include <QtCore/QVector>
#include <QtCore/QThread>

#include <QtGui/QApplication>

#include <flowvr/module.h>

#include <fstream>

class c_flowvr_event_loop : public QObject
{
   Q_OBJECT
private:
  bool _terminate;
protected:
  flowvr::InputPort * pSelect;      
  flowvr::ModuleAPI * flowvr_var;
  std::vector<flowvr::Port*> ports;  

  std::ofstream ofs_log;
public slots:
  void execute();
  void flowvr_terminate();
  
signals:
  void flowvr_terminated();
  void flowvr_new_selection( QVector<int> );

public:
  c_flowvr_event_loop(QApplication &app, QThread &thread);
  bool initialize_flowvr();
  c_flowvr_event_loop(const c_flowvr_event_loop& orig);
  virtual ~c_flowvr_event_loop();
private:

};

#endif	/* C_FLOWVR_EVENT_LOOP_H */

