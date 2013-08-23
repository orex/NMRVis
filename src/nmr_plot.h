/* 
 * File:   nmr_plot.h
 * Author: kirill
 *
 * Created on August 20, 2013, 5:07 PM
 */

#ifndef _NMR_PLOT_H
#define	_NMR_PLOT_H

#include "ui_nmr_plot.h"
#include <qwt/qwt_plot_zoomer.h>

class nmr_plot : public QMainWindow 
{
  Q_OBJECT
protected:
  QwtPlotZoomer * zoomer;
public slots:
  void new_selection( QVector<int> select_ids );
  void quit_rec();
public:
  nmr_plot();
  virtual ~nmr_plot();
private:
  Ui::nmr_plot ui;
};

#endif	/* _NMR_PLOT_H */
