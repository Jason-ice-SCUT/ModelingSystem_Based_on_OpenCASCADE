#pragma once

#include <QWidget>
#include "ui_StreCircleDesign.h"

class StreCircleDesign : public QWidget
{
	Q_OBJECT

public:
	StreCircleDesign(QWidget *parent = nullptr);
	~StreCircleDesign();

private:
	Ui::StreCircleDesignClass ui;

signals:
	void stre_create_circle_signal(double p0_u, double p0_v, double r);

private slots:
	void on_PushButton_ok();
};
