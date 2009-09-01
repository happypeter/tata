#ifndef POPUP_HPP
#define POPUP_HPP

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>

#include "splash/display.h"

class Frame : public QFrame
{
    Q_OBJECT

public:
    Frame( QWidget *parent=0, const char*  name=0);

private slots:
    void button1Clicked();
    void button3Clicked();
     
private:
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    DisplayWidget *display;       
};

#endif // POPUP_HPP
