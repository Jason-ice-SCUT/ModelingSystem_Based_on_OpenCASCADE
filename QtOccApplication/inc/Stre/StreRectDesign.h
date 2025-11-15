#pragma once
#include "../OCCModeling.h"
#include <QWidget>
#include <QCloseEvent>
#include "ui_StreRectDesign.h"
#include "qdebug.h"

class StreRectDesign : public QWidget
{
	Q_OBJECT

public:
	StreRectDesign(QWidget *parent = nullptr);
	~StreRectDesign();

private:
	Ui::StreRectDesignClass ui;
	void CloseEvent(QCloseEvent *event);

signals:
	void stre_create_rect_signal(double p0_u, double p0_v, double length, double width);
	void toEntity();

private slots:
	void on_PushButton_ok();
};
