#include "../../inc/CSG/CsgCylinderBodyDesign.h"

CsgCylinderBodyDesign::CsgCylinderBodyDesign(QWidget *parent)
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
	ui.lineEdit_R1->clear();
	ui.lineEdit_R1->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_R1->setEnabled(true);
	ui.lineEdit_R2->clear();
	ui.lineEdit_R2->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_R2->setEnabled(true);
	ui.lineEdit_H->clear();
	ui.lineEdit_H->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_H->setEnabled(true);

	/*connect*/
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &CsgCylinderBodyDesign::on_PushButton_ok);
}

CsgCylinderBodyDesign::~CsgCylinderBodyDesign()
{}

/*slot*/
void CsgCylinderBodyDesign::on_PushButton_ok() {

	emit csg_create_cone_signal(
		ui.lineEdit_p0x->text().toDouble(),
		ui.lineEdit_p0y->text().toDouble(),
		ui.lineEdit_p0z->text().toDouble(),
		ui.lineEdit_R1->text().toDouble(),
		ui.lineEdit_R2->text().toDouble(),
		ui.lineEdit_H->text().toDouble()
	);
	//qDebug() << ui.lineEdit_L->text().toDouble();

}
