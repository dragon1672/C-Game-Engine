#include <Qt/qapplication.h>
#include "testing.h"
#include <Engine\BasicGui.h>
#include <Engine\SceneManager.h>
#include "SceneOne.h"
#include "SceneTwo.h"

#include "SceneThree.h"
#include "CoolScene.h"


int main(int argc, char * argv[]) {
	QApplication app(argc, argv);
	BasicGui GUI;

	//Testing widg;
	SceneManager widg;

	//SceneOne tab1;	widg.addScene(&tab1);
	//SceneTwo tab2;	widg.addScene(&tab2);
	//SceneThree tab3;	widg.addScene(&tab3);
	CoolScene tab4;	widg.addScene(&tab4);

	GUI.addScene(&widg);
	GUI.show();
	return app.exec();
}