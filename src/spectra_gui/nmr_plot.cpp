/*
 * File:   nmr_plot.cpp
 * Author: kirill
 *
 * Created on August 20, 2013, 5:07 PM
 */

#include <iostream>

#include <QtCore/QString>
#include <qwt/qwt.h>
#include <qwt/qwt_plot.h>
#include <qwt/qwt_plot_curve.h>
#include <qwt/qwt_scale_engine.h>

#include <boost/lexical_cast.hpp>
#include <boost/format.hpp>

#include "nmr_plot.h"
#include "science/math_utils.h"
#include "others/TStatisticCollect.h"

using namespace std;        

QEvent::Type QNewSpcEvent::NewSpcEventType = QEvent::None;

nmr_plot::nmr_plot()
{
  ui.setupUi(this);
  zoomer = new QwtPlotZoomer(ui.qwtp_Spectra->canvas(), true);
  picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft, 
                             QwtPicker::VLineRubberBand, QwtPicker::AlwaysOn,
                             ui.qwtp_Spectra->canvas());
  
  nmr_shifts = NULL;
  ui.qwtp_Spectra->axisScaleEngine(QwtPlot::xBottom)->setAttribute(QwtScaleEngine::Inverted, true);  
  
  connect(ui.cb_elem_symbols, SIGNAL(currentIndexChanged(int)),
          this, SLOT(change_spectra_params()));
  
  connect(ui.dsb_broad, SIGNAL(valueChanged(double)),
          this, SLOT(change_spectra_params()));
  
}

void nmr_plot::updateSpectra()
{
  QApplication::postEvent(this, new QNewSpcEvent());
}

void nmr_plot::new_selection( QVector<int> select_ids )
{

}

void nmr_plot::quit_rec()
{
  ui.lblTest->setText( " Exiting... " );
  sleep(5);
}

void nmr_plot::new_spc(nmr_shift_data_process * nmr_shifts_v)
{
  cout << "New spectra Signal recieved" << endl;
  assert(nmr_shifts_v != NULL);
  if(nmr_shifts != NULL)
    delete nmr_shifts;
  
  nmr_shifts = nmr_shifts_v;
  
  updateSpectra();
}

void nmr_plot::repaint_spectra()
{
  assert(nmr_shifts != NULL);
  
  std::set<std::string> elem_symbols = nmr_shifts->get_elem_symbols();
  
  if(ui.cb_elem_symbols->count() == 0) 
  {  
    for(std::set<std::string>::const_iterator it = elem_symbols.begin(); 
                                              it != elem_symbols.end(); it++ )
    {
      ui.cb_elem_symbols->addItem(QString::fromStdString(*it));
    }
  }
 
  create_plot(ui.cb_elem_symbols->currentText().toStdString(), ui.dsb_broad->value());
}

void nmr_plot::change_spectra_params()
{
  if(nmr_shifts == NULL)
    return;
  
  std::string cb_elem = ui.cb_elem_symbols->currentText().toStdString();
  double dsb_val = ui.dsb_broad->value();
  
  if(cb_elem == "")
    return;
  
  if( (curr_elem != cb_elem) || ( fabs(dsb_val - curr_brd) > 0.001 ) )
  {  
    create_plot(cb_elem, dsb_val);
  }         
}

void nmr_plot::create_plot(std::string atom_symbol, double brd_size)
{
  cout << "create plot input: " << atom_symbol << " " << brd_size;
  
  ui.qwtp_Spectra->detachItems();
  
  vector<double> rpc_spc;
  
  std::pair<double, double> range_ppm = nmr_shift_data_process::get_range_by_elem(atom_symbol);
  vector<nmr_shift_item> ns = nmr_shifts->get_elem_by_symbol(atom_symbol);
  
  TRealStepStatisticCollect rst(range_ppm.first, range_ppm.second, brd_size / 6);
  
  for(int i = 0; i < ns.size(); i++)
  {  
    if(!ns[i].shift.assigned())
      continue;
    
    std::string site_name = str( boost::format("%1%: %2% (%3%) %4%") %
                                          ns[i].atom_index % 
                                          ns[i].atom_name % 
                                          ns[i].res_name %
                                          ns[i].res_index );
                            
    QwtPlotCurve *curve1 = new QwtPlotCurve(QString::fromStdString(site_name));
    curve1->setStyle(QwtPlotCurve::Sticks);
    QwtPointSeriesData* myData = new QwtPointSeriesData;
    QVector<QPointF>* samples = new QVector<QPointF>;
    
    double xb = ns[i].shift.value();
    double yb = 0.01;
    samples->push_back(QPointF(xb, yb));
    
    rst.add_point(0, xb, 1);

    myData->setSamples(*samples);
    curve1->setData(myData);
 
    curve1->attach(ui.qwtp_Spectra);
  }
  
  //Add spectra curve
  vector<double> spc;
  rst.copy_data(spc);
  spc = math_utils::brd_Gaussian(spc, 6);
  
  QwtPlotCurve *curve1 = new QwtPlotCurve("Spectra");
  curve1->setPen(* new QPen(Qt::red));
  QwtPointSeriesData* myData = new QwtPointSeriesData;
  QVector<QPointF>* samples = new QVector<QPointF>;
  
  for(int i = 0; i < spc.size(); i++)
    samples->push_back(QPointF(range_ppm.first + rst.delta_value() * i, spc[i]));

  myData->setSamples(*samples);
  curve1->setData(myData);
  curve1->attach(ui.qwtp_Spectra);
  
  ui.qwtp_Spectra->setAxisAutoScale(QwtPlot::yLeft);
  
  if(curr_elem != atom_symbol)
  {
    ui.qwtp_Spectra->setAxisScale(QwtPlot::xBottom, range_ppm.second, range_ppm.first);
    zoomer->setZoomBase();
  }  
  
  ui.qwtp_Spectra->replot();
  
  curr_elem = atom_symbol;
  curr_brd = brd_size;
}

nmr_plot::~nmr_plot()
{
}
