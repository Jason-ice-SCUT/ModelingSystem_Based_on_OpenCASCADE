#pragma once

#include <QWidget>
#include <QDebug>
#include "ui_CsgSphereDesign.h"

class CsgSphereDesign : public QWidget
{
	Q_OBJECT

public:
	CsgSphereDesign(QWidget *parent = nullptr);
	~CsgSphereDesign();

signals:
	void csg_create_sphere_signal(double px, double py, double pz, double r);

private:
	Ui::CsgSphereDesignClass ui;

private slots:
	void on_PushButton_ok();
};
