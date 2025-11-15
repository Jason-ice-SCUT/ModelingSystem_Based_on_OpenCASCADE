#include "../../inc/Feature/FeaCircleArrayOpt.h"

FeaCircleArrayOpt::FeaCircleArrayOpt(QWidget *parent)
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
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &FeaCircleArrayOpt::on_PushButton_ok);
	connect(ui.radioButton, &QRadioButton::clicked, this, &FeaCircleArrayOpt::radioButtonSlots);   //�ź����ѡ��
	connect(ui.radioButton_2, &QRadioButton::clicked, this, &FeaCircleArrayOpt::radioButtonSlots);
}

FeaCircleArrayOpt::~FeaCircleArrayOpt()
{}

void FeaCircleArrayOpt::radioButtonSlots()
{
	//�� switch ����������
	switch (m_btnGroup->checkedId())
	{
	case 0:
		emit CircleArray_choice_mode_entity();
		break;

	case 1:
		emit CircleArray_choice_mode_ax1();
		qDebug() << 1;
		break;
	}
}

void FeaCircleArrayOpt::on_PushButton_ok() {
	qDebug() << 2;
	emit CircleArray_num_signal(ui.lineEdit->text().toDouble());

}

