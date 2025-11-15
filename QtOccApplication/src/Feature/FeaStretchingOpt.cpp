#include "../../inc/Feature/FeaStretchingOpt.h"

FeaStretchingOpt::FeaStretchingOpt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit_H->clear();
	ui.lineEdit_H->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_H->setEnabled(true);
	m_btnGroup = new QButtonGroup(this);
	m_btnGroup->addButton(ui.radioButton_1, 0);	//��radioButton_1���ڵ�0��λ��
	m_btnGroup->addButton(ui.radioButton_2, 1);
	m_btnGroup->addButton(ui.radioButton_3, 2);

	/*connect*/
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &FeaStretchingOpt::on_PushButton_ok);
	connect(ui.radioButton_1, &QRadioButton::clicked, this, &FeaStretchingOpt::radioButtonSlots);   //�ź����ѡ��
	connect(ui.radioButton_2, &QRadioButton::clicked, this, &FeaStretchingOpt::radioButtonSlots);
	connect(ui.radioButton_3, &QRadioButton::clicked, this, &FeaStretchingOpt::radioButtonSlots);
}

FeaStretchingOpt::~FeaStretchingOpt()
{}


void FeaStretchingOpt::radioButtonSlots()
{
	//�� switch ����������
	switch (m_btnGroup->checkedId())
	{
	case 0:
		flag = 0;
			break;

	case 1:
		flag = 1;
			break;

	case 2:
		flag = 2;
			break;
	}
}


void FeaStretchingOpt::on_PushButton_ok() {

	emit stretching_H_signal(ui.lineEdit_H->text().toDouble(), flag);
	qDebug() << flag;
}