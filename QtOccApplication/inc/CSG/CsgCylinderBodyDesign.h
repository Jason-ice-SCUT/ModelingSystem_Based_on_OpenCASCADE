#pragma once

#include <QWidget>
#include "ui_CsgCylinderBodyDesign.h"

class CsgCylinderBodyDesign : public QWidget
{
	Q_OBJECT

public:
	CsgCylinderBodyDesign(QWidget *parent = nullptr);
	~CsgCylinderBodyDesign();

signals:
	void csg_create_cone_signal(double px, double py, double pz, double r1, double r2, double h);

private:
	Ui::CsgCylinderBodyDesignClass ui;

private slots:
	void on_PushButton_ok();

};
