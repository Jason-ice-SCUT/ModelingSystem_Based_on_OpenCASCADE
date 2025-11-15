#pragma once

#include <QWidget>
#include <QButtonGroup>
#include <QDebug>
#include <QAbstractButton>  
#include "ui_FeaFilletOpt.h"

class FeaFilletOpt : public QWidget
{
	Q_OBJECT

public:
	FeaFilletOpt(QWidget *parent = nullptr);
	~FeaFilletOpt();

private:
	Ui::FeaFilletOptClass ui;
	QButtonGroup *m_btnGroup;

signals:
	void makefillet_choose_entity();
	void makefillet_choose_edge();
	void makefillet_radius(double r);

private Q_SLOT:
	void radioButtonSlots();
	void on_PushButton_ok();
};
