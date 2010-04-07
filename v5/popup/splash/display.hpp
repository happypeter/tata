#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <QWidget>
#include "screen.hpp"

class QTimer;
class Screen;
class QStringList;
class QString;
class QLineEdit;
class QPushButton;

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:                                                                                
    DisplayWidget();
    QSize sizeHint() const;
    void   run();
    void   peter_fullscreenshow();
    void   peter_setbackgroundpixmap();
    double readCurveData();
    void   readFile();
      
private slots:
    void tick();
    void start();
    void stop();

private:
    enum { Margin = 40 };

    QLineEdit *lineEdit;
    QPushButton *startButton, *stopButton;
    Screen *screen1;

    QTimer *timer;
    QString str;

    int time;
    double yval;
};

#endif // DISPLAY_HPP
