#include"display.h"
#include<qapplication.h>


int main(int argc, char **argv)

{
QApplication app(argc, argv);
DisplayWidget display;
app.setMainWidget(&display);
display.show();
return app.exec();

}