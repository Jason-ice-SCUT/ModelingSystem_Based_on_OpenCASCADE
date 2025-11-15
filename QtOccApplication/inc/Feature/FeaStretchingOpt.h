#pragma once

#include <QWidget>
#include <QButtonGroup>
#include <QDebug>
#include "ui_FeaStretchingOpt.h"
#include <QAbstractButton>  
//QAbstractButton���ǰ�ť�����ĳ�����࣬�ṩ�˰�ť�����еĹ���.
//QAbstractButton�ṩ�˵���͹�ѡ��ť��QRadioButton��QCheckBox��ֻ�ṩ�˹�ѡ��ť

class FeaStretchingOpt : public QWidget
{
	Q_OBJECT

public:
	FeaStretchingOpt(QWidget *parent = nullptr);
	~FeaStretchingOpt();

private:
	Ui::FeaStretchingOptClass ui;
	QButtonGroup *m_btnGroup;
	int flag = 0;

signals:
	void stretching_H_signal(double h, int flag);

private Q_SLOT:
	void radioButtonSlots();
	void on_PushButton_ok();
};
