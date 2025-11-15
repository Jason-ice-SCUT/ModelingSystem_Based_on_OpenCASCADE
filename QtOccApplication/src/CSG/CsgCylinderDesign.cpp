#include "../../inc/CSG/CsgCylinderDesign.h"

CsgCylinderDesign::CsgCylinderDesign(QWidget *parent)
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
	ui.lineEdit_H->clear();
	ui.lineEdit_H->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_H->setEnabled(true);

	/*connect*/
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &CsgCylinderDesign::on_PushButton_ok);
}

CsgCylinderDesign::~CsgCylinderDesign()
{}

/*slot*/
void CsgCylinderDesign::on_PushButton_ok() {

	emit csg_create_cylinder_signal(
		ui.lineEdit_p0x->text().toDouble(),
		ui.lineEdit_p0y->text().toDouble(),
		ui.lineEdit_p0z->text().toDouble(),
		ui.lineEdit_R->text().toDouble(),
		ui.lineEdit_H->text().toDouble()
	);
	//qDebug() << ui.lineEdit_L->text().toDouble();

}