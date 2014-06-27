#include <Qt/qapplication.h>
#include "MyWindow.h"
#include "MyGUI.h"

int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	MyGUI widg;
	//MyWindow widg;
	//widg.init();
	widg.show();
	return app.exec();
}