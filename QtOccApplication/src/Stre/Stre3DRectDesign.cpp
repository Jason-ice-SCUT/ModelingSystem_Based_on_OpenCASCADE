#include "../../inc/Stre/Stre3DRectDesign.h"

Stre3DRectDesign::Stre3DRectDesign(QWidget *parent)
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
	ui.lineEdit_L->clear();
	ui.lineEdit_L->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_L->setEnabled(true);
	ui.lineEdit_W->clear();
	ui.lineEdit_W->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_W->setEnabled(true);

	/*connect*/
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &Stre3DRectDesign::on_PushButton_ok);
}

Stre3DRectDesign::~Stre3DRectDesign()
{}


void Stre3DRectDesign::on_PushButton_ok() {
	gp_Pnt p0(
		ui.lineEdit_p0x->text().toDouble(),
		ui.lineEdit_p0y->text().toDouble(),
		ui.lineEdit_p0z->text().toDouble()
	);
	emit stre_create_3drect_signal(
		p0,
		ui.lineEdit_L->text().toDouble(),
		ui.lineEdit_W->text().toDouble()
	);

}