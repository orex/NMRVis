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

#include <boost/lexical_cast.hpp>

#include "nmr_plot.h"
#include "math_utils.h"

using namespace std;        

nmr_plot::nmr_plot()
{
  ui.setupUi(this);
  zoomer = new QwtPlotZoomer(ui.qwtp_Spectra->canvas(), true);
}

void nmr_plot::new_selection( QVector<int> select_ids )
{
  cout << "Signal received!!!" << endl;
  
  string str;
  for(int i = 0; i < select_ids.count(); i++)
  {  
    str += boost::lexical_cast<string>(select_ids[i]) + " ";
  }
  ui.lblTest->setText( QString::fromStdString( str ) );
  
  ui.qwtp_Spectra->detachItems();
  
  vector<double> rpc_spc;
  
  rpc_spc.resize(100, 0);
  rpc_spc[49] = 1;
  
  rpc_spc = math_utils::brd_Gaussian(rpc_spc, 5);
  
  for(int i = 0; i < select_ids.count(); i++)
  {  
    QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1");
    QwtPointSeriesData* myData = new QwtPointSeriesData;
    QVector<QPointF>* samples = new QVector<QPointF>;
    
    for(int j = 0; j < rpc_spc.size(); j++)
    {
      double xb = j - 49 + 20 * select_ids[i];
      double yb = rpc_spc[j];

      samples->push_back(QPointF(xb, yb));
    }
  
    myData->setSamples(*samples);
    curve1->setData(myData);
 
    curve1->attach(ui.qwtp_Spectra);
  }  
  
  ui.qwtp_Spectra->setAxisAutoScale(QwtPlot::yLeft);
  ui.qwtp_Spectra->setAxisAutoScale(QwtPlot::xBottom);
  ui.qwtp_Spectra->replot();
  
  zoomer->setZoomBase();
}

void nmr_plot::quit_rec()
{
  ui.lblTest->setText( " Exiting... " );
  sleep(5);
}

nmr_plot::~nmr_plot()
{
}
