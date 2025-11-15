#pragma once

#include <QWidget>
#include <QDebug>
#include "ui_CsgCubeDesign.h"
#include "../../SARibbonBar_amalgamate/SARibbon.h"
#include "../OCCModeling.h"


class CsgCubeDesign : public QWidget
{
	Q_OBJECT

public:
	CsgCubeDesign(QWidget *parent = nullptr);
	~CsgCubeDesign();

signals:
	void csg_create_cube_signal_new(double px, double py, double pz, double l, double w, double h);

private:
	Ui::CsgCubeDesignClass ui;


private slots:
	void on_PushButton_ok();
};
