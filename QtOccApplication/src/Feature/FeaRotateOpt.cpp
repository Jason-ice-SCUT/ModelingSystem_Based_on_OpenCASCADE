#include "../../inc/Feature/FeaRotateOpt.h"

FeaRotateOpt::FeaRotateOpt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit->clear();
	ui.lineEdit->setEchoMode(QLineEdit::Normal);
	ui.lineEdit->setEnabled(true);

	m_btnGroup = new QButtonGroup(this);
	m_btnGroup->addButton(ui.radioButton, 0);	//��radioButton_1���ڵ�0��λ��
	m_btnGroup->addButton(ui.radioButton_2, 1);
	/*connect*/
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &FeaRotateOpt::on_PushButton_ok);
	connect(ui.radioButton, &QRadioButton::clicked, this, &FeaRotateOpt::radioButtonSlots);   //�ź����ѡ��
	connect(ui.radioButton_2, &QRadioButton::clicked, this, &FeaRotateOpt::radioButtonSlots);
}

FeaRotateOpt::~FeaRotateOpt()
{}


void FeaRotateOpt::radioButtonSlots()
{
	//�� switch ����������
	switch (m_btnGroup->checkedId())
	{
	case 0:
		emit rotate_choice_mode_wire();
		break;

	case 1:
		emit rotate_choice_mode_ax1();
		qDebug() << 1;
		break;
	}
}

void FeaRotateOpt::on_PushButton_ok() {
	qDebug() << 2;
	emit rotate_angle_signal(ui.lineEdit->text().toDouble());

}
