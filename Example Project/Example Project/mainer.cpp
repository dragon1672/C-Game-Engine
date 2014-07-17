#include <Qt/qapplication.h>
#include "testing.h"
#include <Engine\BasicGui.h>
#include <Engine\SceneManager.h>
#include "SceneOne.h"
#include "SceneTwo.h"


int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	BasicGui GUI;

	//Testing widg;
	SceneManager widg;

	SceneOne tab1;	widg.addScene(&tab1);
	SceneTwo tab2;	widg.addScene(&tab2);


	GUI.addScene(&widg);
	GUI.show();
	return app.exec();
}