#include "QtOccApplication.h"
#include "SubC3dWidget.h"
#include "OCCModeling.h"
#include <QtWidgets/QApplication>

using namespace std;

int main(int argc, char *argv[])
{
	QApplication::setAttribute(Qt::AA_DisableShaderDiskCache);

	QApplication a(argc, argv);
    QtOccApplication w;

	
    w.show();
	
    return a.exec();

}
