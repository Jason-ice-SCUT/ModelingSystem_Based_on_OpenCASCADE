#include "../../inc/Stre/StreCircleDesign.h"

StreCircleDesign::StreCircleDesign(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit_p0x->clear();
	ui.lineEdit_p0x->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_p0x->setEnabled(true);
	ui.lineEdit_p0y->clear();
	ui.lineEdit_p0y->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_p0y->setEnabled(true);
	ui.lineEdit_R->clear();
	ui.lineEdit_R->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_R->setEnabled(true);

	/*connect*/
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &StreCircleDesign::on_PushButton_ok);

}

StreCircleDesign::~StreCircleDesign()
{}

void StreCircleDesign::on_PushButton_ok() {
	emit stre_create_circle_signal(
		ui.lineEdit_p0x->text().toDouble(),
		ui.lineEdit_p0y->text().toDouble(),
		ui.lineEdit_R->text().toDouble()
	);

}