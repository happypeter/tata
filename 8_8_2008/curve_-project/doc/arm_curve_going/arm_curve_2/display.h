#ifndef DISPLAY_H
#define DISPLAY_H

#ifndef QT_H
#include <qwidget.h>
#endif // QT_H

class QTimer;
class QStringList;
class QString;
class QLineEdit;
class QPushButton;

class DisplayWidget : public QWidget {
    Q_OBJECT
public:
    DisplayWidget( QWidget *parent=0, const char *name=0 );

private:
        QLineEdit *lineEdit;
        QPushButton *startButton, *stopButton;
              
        QString str;
       
      };

#endif // PLOT_H
