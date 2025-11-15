#pragma once

#include <QWidget>
#include <QButtonGroup>
#include <QDebug>
#include <QAbstractButton>  
#include "ui_FeaChamferOpt.h"

class FeaChamferOpt : public QWidget
{
	Q_OBJECT

public:
	FeaChamferOpt(QWidget *parent = nullptr);
	~FeaChamferOpt();

private:
	Ui::FeaChamferOptClass ui;
	QButtonGroup *m_btnGroup;

signals:
	void makechamfer_choose_entity();
	void makechamfer_choose_edge();
	void makechamfer_choose_face();
	void makechamfer_dis(double dis1, double dis2);

	private Q_SLOT:
	void radioButtonSlots();
	void on_PushButton_ok();
};
