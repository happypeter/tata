#ifndef DISPLAY_H
#define DISPLAY_H

#ifndef QT_H
#include <qwidget.h>
#endif // QT_H

class QTimer;
class Screen;
class QStringList;
class QString;
class QLineEdit;
class QPushButton;

class DisplayWidget : public QWidget {
    Q_OBJECT
public:
    DisplayWidget( QWidget *parent=0, const char *name=0 );

    QSize sizeHint() const;
        double readCurveDate();
        void readFile();
    void run();
protected:
        //virtual void showEvent ( QShowEvent * );
private slots:
          void start();
        void stop();

private:
    Screen *screen1;
        Screen *screen2;
        Screen *screen3;
   
        QLineEdit *lineEdit;
        QPushButton *startButton, *stopButton;
                QTimer *timer;
                enum { Margin = 40};        
        QString str;
        int time;
        double yval;
};

#endif // PLOT_H
