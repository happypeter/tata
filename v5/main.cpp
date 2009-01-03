#include "splashscreen.h"
#include <qapplication.h>
#include <qmainwindow.h>
#include "./popup/popup.h"
#include "./xpm/good1.xpm"
int main( int argc, char **argv )
    {
        QApplication app( argc, argv );
	QPixmap pixmap( good1_xpm);
	SplashScreen *splash = new SplashScreen( pixmap );
	QMainWindow *mainWin = new QMainWindow;
	Frame *frame=new Frame;
//	app.setMainWidget( mainWin );
	app.setMainWidget(frame);
//	mainWin->show();
	splash->show();
	splash->finish( frame );
	frame->show();
	delete splash;
        return app.exec();
    }
