#pragma once

#include <QWidget>
#include "ui_CsgBooleanOpt.h"
#include "../OCCModeling.h"

class CsgBooleanOpt : public QWidget
{
	Q_OBJECT

public:
	CsgBooleanOpt(QWidget *parent = nullptr);
	~CsgBooleanOpt();
	TopoDS_Shape boolopt_model_1;
	TopoDS_Shape boolopt_model_2;
	int check_num = 3;

public:
	Ui::CsgBooleanOptClass CBO_ui;

signals:
	void boolopt_signal_and(TopoDS_Shape model_1, TopoDS_Shape model_2);
	void boolopt_signal_differ(TopoDS_Shape model_1, TopoDS_Shape model_2);
	void boolopt_signal_intersert(TopoDS_Shape model_1, TopoDS_Shape model_2);

private Q_SLOTS:
	void csg_receive_boolopt_model(TopoDS_Shape boolopt_model);
	void on_pushBotton_and();
	void on_pushBotton_differ();
	void on_pushBotton_intersert();
	void on_show_boolopt_text();

private:
	int OSBT = 0;
};