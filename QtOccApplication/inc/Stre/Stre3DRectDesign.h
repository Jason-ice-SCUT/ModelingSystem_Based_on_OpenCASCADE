#pragma once

#include <QWidget>
#include "ui_Stre3DRectDesign.h"
#include "../OCCModeling.h"

class Stre3DRectDesign : public QWidget
{
	Q_OBJECT

public:
	Stre3DRectDesign(QWidget *parent = nullptr);
	~Stre3DRectDesign();

private:
	Ui::Stre3DRectDesignClass ui;

signals:
	void stre_create_3drect_signal(gp_Pnt p0, double length, double width);

private slots:
	void on_PushButton_ok();
};
