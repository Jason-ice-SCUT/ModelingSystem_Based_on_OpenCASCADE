#pragma once

#include <QWidget>
#include <QButtonGroup>
#include "ui_FeaExcisionOpt.h"
#include <QAbstractButton>  
class FeaExcisionOpt : public QWidget
{
	Q_OBJECT

public:
	FeaExcisionOpt(QWidget *parent = nullptr);
	~FeaExcisionOpt();

private:
	Ui::FeaExcisionOptClass ui;
	QButtonGroup *m_btnGroup;
	int flag = 0;
	
signals:
	void excision_H_signal(double h, int flag);

private Q_SLOT:
	void radioButtonSlots();
	void on_PushButton_ok();
};
