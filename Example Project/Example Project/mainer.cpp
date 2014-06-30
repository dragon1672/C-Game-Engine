#include <Qt/qapplication.h>
#include "testing.h"


int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	Testing widg;
	widg.init();
	widg.show();
	return app.exec();
}