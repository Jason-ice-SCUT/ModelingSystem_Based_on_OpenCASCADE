#include "../../inc/CSG/CsgBooleanOpt.h"

CsgBooleanOpt::CsgBooleanOpt(QWidget *parent)
	: QWidget(parent)
{
	CBO_ui.setupUi(this);
	connect(CBO_ui.pushButton_and, &QPushButton::clicked, this, &CsgBooleanOpt::on_pushBotton_and);
	connect(CBO_ui.pushButton_differ, &QPushButton::clicked, this, &CsgBooleanOpt::on_pushBotton_differ);
	connect(CBO_ui.pushButton_intersert, &QPushButton::clicked, this, &CsgBooleanOpt::on_pushBotton_intersert);
}

CsgBooleanOpt::~CsgBooleanOpt()
{}


void CsgBooleanOpt::csg_receive_boolopt_model(TopoDS_Shape boolopt_model) {
	check_num++;
	//在显示框显示“已选择模型<1><2>”


	//接收boolopt_model
	if (check_num % 2 != 0) {
		boolopt_model_1 = boolopt_model;
	}
	else
	{
		boolopt_model_2 = boolopt_model;
	}
}

void CsgBooleanOpt::on_pushBotton_and(){

	emit boolopt_signal_and(boolopt_model_1, boolopt_model_2);
}

void CsgBooleanOpt::on_pushBotton_differ() {

	emit boolopt_signal_differ(boolopt_model_1, boolopt_model_2);
}

void CsgBooleanOpt::on_pushBotton_intersert() {

	emit boolopt_signal_intersert(boolopt_model_1, boolopt_model_2);
}

void CsgBooleanOpt::on_show_boolopt_text() {
	if (OSBT == 0) {
		CBO_ui.selected_status->append("You have chosen an entity which will be operated.");
		OSBT = 1;
	}
	else
	{
		CBO_ui.selected_status->append("You have chosen an entity which will be used to operate.");
		OSBT = 0;
	}


};