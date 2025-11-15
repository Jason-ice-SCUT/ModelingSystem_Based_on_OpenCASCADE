#pragma once

#include <QWidget>
#include <QButtonGroup>
#include <QDebug>
#include <QAbstractButton>  
#include "ui_FeaCircleArrayOpt.h"

class FeaCircleArrayOpt : public QWidget
{
	Q_OBJECT

public:
	FeaCircleArrayOpt(QWidget *parent = nullptr);
	~FeaCircleArrayOpt();

private:
	Ui::FeaCircleArrayOptClass ui;
	QButtonGroup *m_btnGroup;

signals:
	void CircleArray_choice_mode_entity();
	void CircleArray_choice_mode_ax1();
	void CircleArray_num_signal(double num);

private Q_SLOT:
	void radioButtonSlots();
	void on_PushButton_ok();
};
