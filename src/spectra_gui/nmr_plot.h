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
#include <qwt/qwt_plot_picker.h>

#include "nmr_shift_data_process.h"

class QNewSpcEvent : public QEvent
{
private:
    static QEvent::Type NewSpcEventType;
public:
  QNewSpcEvent() : QEvent(QNewSpcEvent::type()) {};
  ~QNewSpcEvent() {};
  
  static QEvent::Type type()
  {
    if (NewSpcEventType == QEvent::None)
    {
      int generatedType = QEvent::registerEventType();
      NewSpcEventType = static_cast<QEvent::Type>(generatedType);
    }
    return NewSpcEventType;
  }
};

class nmr_plot : public QMainWindow 
{
  Q_OBJECT
private:
  std::string curr_elem;
  double curr_brd;
protected:
  QwtPlotZoomer          * zoomer;
  QwtPlotPicker          * picker;
  nmr_shift_data_process * nmr_shifts;
  void updateSpectra();
  void customEvent(QEvent * e)
  {
    if(e->type() == QNewSpcEvent::type())
      emit repaint_spectra();
  }
  void create_plot(std::string atom_symbol, double brd_size);
public slots:
  void new_selection( QVector<int> select_ids );
  void quit_rec();
  void new_spc(nmr_shift_data_process * nmr_shifts_v);
  void repaint_spectra();
  void change_spectra_params();
public:
  nmr_plot();
  virtual ~nmr_plot();
private:
  Ui::nmr_plot ui;
};

#endif	/* _NMR_PLOT_H */
