#include "../../inc/Stre/StreRectDesign.h"

StreRectDesign::StreRectDesign(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit_p0x->clear();
	ui.lineEdit_p0x->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_p0x->setEnabled(true);
	ui.lineEdit_p0y->clear();
	ui.lineEdit_p0y->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_p0y->setEnabled(true);
	ui.lineEdit_L->clear();
	ui.lineEdit_L->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_L->setEnabled(true);
	ui.lineEdit_W->clear();
	ui.lineEdit_W->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_W->setEnabled(true);

	/*connect*/
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &StreRectDesign::on_PushButton_ok);
}

StreRectDesign::~StreRectDesign()
{}


void StreRectDesign::on_PushButton_ok() {
	emit stre_create_rect_signal(
		ui.lineEdit_p0x->text().toDouble(),
		ui.lineEdit_p0y->text().toDouble(),
		ui.lineEdit_L->text().toDouble(),
		ui.lineEdit_W->text().toDouble()
	);
	
}
void StreRectDesign::CloseEvent(QCloseEvent *event) {

	emit toEntity();
	qDebug() << 1;
}