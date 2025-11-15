#pragma once

#include <QWidget>
#include "ui_CsgCylinderDesign.h"

class CsgCylinderDesign : public QWidget
{
	Q_OBJECT

public:
	CsgCylinderDesign(QWidget *parent = nullptr);
	~CsgCylinderDesign();

signals:
	void csg_create_cylinder_signal(double px, double py, double pz, double r, double h);


private:
	Ui::CsgCylinderDesignClass ui;

private slots:
	void on_PushButton_ok();
};
