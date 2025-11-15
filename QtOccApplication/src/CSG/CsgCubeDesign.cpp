#include "../../inc/CSG/CsgCubeDesign.h"



CsgCubeDesign::CsgCubeDesign(QWidget *parent)
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
	ui.lineEdit_H->clear();
	ui.lineEdit_H->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_H->setEnabled(true);


	/*connect*/
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &CsgCubeDesign::on_PushButton_ok);

	
}

CsgCubeDesign::~CsgCubeDesign()
{}

/*signal*/



/*slot*/
void CsgCubeDesign::on_PushButton_ok() {
	
	emit csg_create_cube_signal_new(
		ui.lineEdit_p0x->text().toDouble(),
		ui.lineEdit_p0y->text().toDouble(),
		ui.lineEdit_p0z->text().toDouble(),
		ui.lineEdit_L->text().toDouble(),
		ui.lineEdit_W->text().toDouble(),
		ui.lineEdit_H->text().toDouble()
	); 
	//qDebug() << ui.lineEdit_L->text().toDouble();
	
}