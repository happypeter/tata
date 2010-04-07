#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <iostream>
#include <stdlib.h>
#include "popup/splash/screen.hpp"
#include "popup/splash/display.hpp"
#include "popup/popup.hpp"

#include <QLCDNumber>
#include <QSlider>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QPixmap pixmap("good1.xpm");

    QSplashScreen splash(pixmap);
    splash.show();
    app.processEvents();
    
    Frame window;

    window.show();

// TH:
// How can we show the splash screen for one or two seconds
// without explicitly using the sleep() function ??
// Without something like this, the splash screen will disappear
// almost immediately. Is there a Qt feature for this ?
//    sleep(1);

    splash.finish(&window);

    return app.exec();
}
