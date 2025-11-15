#pragma once

#include <QWidget>
#include <QButtonGroup>
#include <QDebug>
#include <QAbstractButton>  
#include "ui_FeaRotateOpt.h"

class FeaRotateOpt : public QWidget
{
	Q_OBJECT

public:
	FeaRotateOpt(QWidget *parent = nullptr);
	~FeaRotateOpt();

private:
	Ui::FeaRotateOptClass ui;
	QButtonGroup *m_btnGroup;

signals:
	void rotate_choice_mode_wire();
	void rotate_choice_mode_ax1();
	void rotate_angle_signal(double angle);

private Q_SLOT:
	void radioButtonSlots();
	void on_PushButton_ok();
};
