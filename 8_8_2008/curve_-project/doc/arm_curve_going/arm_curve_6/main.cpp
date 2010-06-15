#include"display.h"
#include<qapplication.h>
#include<stdio.h>

int main(int argc, char **argv)

{
double a[2];
a[0]=1.34;
printf("%d\n",a[0]);
QApplication app(argc, argv);
DisplayWidget display;
app.setMainWidget(&display);
display.show();
return app.exec();

}
