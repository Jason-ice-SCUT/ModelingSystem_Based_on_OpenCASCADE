#include "../../inc/CSG/CsgSphereDesign.h"

CsgSphereDesign::CsgSphereDesign(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit_p0x->clear();
	ui.lineEdit_p0x->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_p0x->setEnabled(true);
	ui.lineEdit_p0y->clear();
	ui.lineEdit_p0y->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_p0y->setEnabled(true);
	ui.lineEdit_p0z->clear();
	ui.lineEdit_p0z->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_p0z->setEnabled(true);
	ui.lineEdit_R->clear();
	ui.lineEdit_R->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_R->setEnabled(true);

	/*connect*/
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &CsgSphereDesign::on_PushButton_ok);
}

CsgSphereDesign::~CsgSphereDesign()
{}

/*slot*/
void CsgSphereDesign::on_PushButton_ok() {

	emit csg_create_sphere_signal(
		ui.lineEdit_p0x->text().toDouble(),
		ui.lineEdit_p0y->text().toDouble(),
		ui.lineEdit_p0z->text().toDouble(),
		ui.lineEdit_R->text().toDouble()
	);


}