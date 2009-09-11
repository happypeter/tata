#ifndef POPUP_H
#define POPUP_H

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QProcess>

#include "splash/display.h"

class Frame : public QFrame
{
	Q_OBJECT

public:
	Frame( QWidget *parent=0, const char*  name=0);
	~Frame();
private slots:
	void button1Clicked();
	void button2Clicked();
	void button3Clicked();
     
private:
	QPushButton *button1;
	QPushButton *button2;
	QPushButton *button3;
	DisplayWidget *display;   
	QProcess * m_processFileReader;    
};

#endif // POPUP_H
