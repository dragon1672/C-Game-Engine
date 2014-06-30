#include <Qt/qapplication.h>
#include "testing.h"
#include <Engine\BasicGui.h>


int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	BasicGui GUI;

	Testing widg;

	GUI.addScene(&widg);
	GUI.show();
	return app.exec();
}