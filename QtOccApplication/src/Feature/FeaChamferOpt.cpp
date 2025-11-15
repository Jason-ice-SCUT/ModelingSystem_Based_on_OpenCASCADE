#include "../../inc/Feature/FeaChamferOpt.h"

FeaChamferOpt::FeaChamferOpt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.lineEdit->clear();
	ui.lineEdit->setEchoMode(QLineEdit::Normal);
	ui.lineEdit->setEnabled(true);
	ui.lineEdit_2->clear();
	ui.lineEdit_2->setEchoMode(QLineEdit::Normal);
	ui.lineEdit_2->setEnabled(true);

	m_btnGroup = new QButtonGroup(this);
	m_btnGroup->addButton(ui.radioButton, 0);	//��radioButton_1���ڵ�0��λ��
	m_btnGroup->addButton(ui.radioButton_2, 1);
	m_btnGroup->addButton(ui.radioButton_3, 2);
	/*connect*/
	connect(ui.pushButton_ok, &QPushButton::clicked, this, &FeaChamferOpt::on_PushButton_ok);
	connect(ui.radioButton, &QRadioButton::clicked, this, &FeaChamferOpt::radioButtonSlots);   //�ź����ѡ��
	connect(ui.radioButton_2, &QRadioButton::clicked, this, &FeaChamferOpt::radioButtonSlots);
	connect(ui.radioButton_3, &QRadioButton::clicked, this, &FeaChamferOpt::radioButtonSlots);
}

FeaChamferOpt::~FeaChamferOpt()
{}

void FeaChamferOpt::radioButtonSlots()
{
	//�� switch ����������
	switch (m_btnGroup->checkedId())
	{
	case 0:
		emit makechamfer_choose_entity();
		qDebug() << 0;
		break;

	case 1:
		emit makechamfer_choose_edge();
		qDebug() << 1;
		break;
	case 2:
		emit makechamfer_choose_face();
		qDebug() << 2;
		break;
	}
}

void FeaChamferOpt::on_PushButton_ok() {
	qDebug() << 3;
	emit makechamfer_dis(ui.lineEdit->text().toDouble(), ui.lineEdit_2->text().toDouble());

}