#ifndef DISPLAY_H
#define DISPLAY_H

#ifndef QT_H
#include <qwidget.h>
#endif // QT_H
#include "screen.h"
class QTimer;
class Screen;
class QStringList;
class QString;
class QLineEdit;
class QPushButton;
class DisplayWidget : public QWidget {
    Q_OBJECT
public:                                                                                DisplayWidget();
       QSize sizeHint() const;
void   run();
void   peter_fullscreenshow();
void   peter_setbackgroundpixmap();
double readCurveData();
void   readFile();
protected:
      
private slots:
        void tick();
        void start();
        void stop();

private:
        QLineEdit *lineEdit;
        QPushButton *startButton, *stopButton;
        Screen *screen1;

        QTimer *timer;
        enum { Margin = 40};
        QString str;
//       QStringList strlist;
//       QStringList ::Iterator it;
        int time;
        double yval;


};
#endif // PLOT_H
