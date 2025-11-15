#include "../../inc/Feature/FeaFilletOpt.h"

FeaFilletOpt::FeaFilletOpt(QWidget *parent)
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
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &FeaFilletOpt::on_PushButton_ok);
	connect(ui.radioButton, &QRadioButton::clicked, this, &FeaFilletOpt::radioButtonSlots);   //�ź����ѡ��
	connect(ui.radioButton_2, &QRadioButton::clicked, this, &FeaFilletOpt::radioButtonSlots);
}

FeaFilletOpt::~FeaFilletOpt()
{}

void FeaFilletOpt::radioButtonSlots()
{
	//�� switch ����������
	switch (m_btnGroup->checkedId())
	{
	case 0:
		emit makefillet_choose_entity();
		qDebug() << 0;
		break;

	case 1:
		emit makefillet_choose_edge();
		qDebug() << 1;
		break;
	}
}

void FeaFilletOpt::on_PushButton_ok() {
	qDebug() << 2;
	emit makefillet_radius(ui.lineEdit->text().toDouble());

}