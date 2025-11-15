#pragma once
#ifndef QTOCCAPPLICATION_H
#define QTOCCAPPLICATION_H


#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QFileDialog>
#include <QDockWidget>
#include "ui_QtOccApplication.h"

#include "SARibbon.h"
#include "OCCModeling.h"
#include "SubC3dWidget.h"

#include "CSG/CsgCubeDesign.h"
#include "CSG/CsgCylinderDesign.h"
#include "CSG/CsgCylinderBodyDesign.h"
#include "CSG/CsgSphereDesign.h"
#include "CSG/CsgBooleanOpt.h"

#include "Stre/StreRectDesign.h"
#include "Stre/Stre3DRectDesign.h"
#include "Stre/StreCircleDesign.h"

#include "Feature/FeaStretchingOpt.h"
#include "Feature/FeaExcisionOpt.h"
#include "Feature/FeaRotateOpt.h"
#include "Feature/FeaFilletOpt.h"
#include "Feature/FeaChamferOpt.h"
#include "Feature/FeaCircleArrayOpt.h"

#include <vector>
using namespace std;


class QtOccApplication : public SARibbonMainWindow
{
    Q_OBJECT

public:
    QtOccApplication(QWidget *parent = nullptr, bool useRibbon = true);
    ~QtOccApplication();
	
	//SubC3dWidget *SW = new SubC3dWidget();
	

	
	QAction* btn_file = new QAction(QIcon(":/QtOccApplication/icon/file.svg"), tr("打开"), this);
	QAction* btn_option = new QAction(QIcon(":/QtOccApplication/icon/action.svg"), tr("选项"), this);
	QAction* btn_setting = new QAction(QIcon(":/QtOccApplication/icon/customize0.svg"), tr("设置"), this);
	QAction* btn_save = new QAction(QIcon(":/QtOccApplication/icon/save.svg"), tr("保存"), this);
	QAction* btn_deleteAll = new QAction(QIcon(":/QtOccApplication/icon/delete.svg"), tr("清除显示"), this);
	QAction* btn_adaptview = new QAction(QIcon(":/QtOccApplication/icon/adaptview.svg"), tr("自适应显示"), this);

	QAction* btn_cube = new QAction(QIcon(":/QtOccApplication/icon/cube.svg"), tr("立方体"), this);
	QAction* btn_cylinder = new QAction(QIcon(":/QtOccApplication/icon/cylinder.svg"), tr("圆柱体"), this);
	QAction* btn_sphere = new QAction(QIcon(":/QtOccApplication/icon/sphere.svg"), tr("球体"), this);
	QAction* btn_cone = new QAction(QIcon(":/QtOccApplication/icon/cylinder body.svg"), tr("圆台体"), this);
	QAction* btn_boolean_opt = new QAction(QIcon(":/QtOccApplication/icon/boolean opt.svg"), tr("布尔操作"), this);
	QAction* btn_toEntity = new QAction(QIcon(":/QtOccApplication/icon/toEntity.svg"), tr("实体化"), this);

	QAction* btn_rect = new QAction(QIcon(":/QtOccApplication/icon/rectangle.svg"), tr("矩形"), this);
	QAction* btn_circle = new QAction(QIcon(":/QtOccApplication/icon/circle.svg"), tr("圆形"), this);
	QAction* btn_line = new QAction(QIcon(":/QtOccApplication/icon/line.svg"), tr("直线"), this);
	QAction* btn_arced = new QAction(QIcon(":/QtOccApplication/icon/arced.svg"), tr("圆弧"), this);
	QAction* btn_connect = new QAction(QIcon(":/QtOccApplication/icon/connect.svg"), tr("连接"), this);
	QAction* btn_cutting = new QAction(QIcon(":/QtOccApplication/icon/cutting.svg"), tr("剪裁"), this);
	QAction* btn_3drect = new QAction(QIcon(":/QtOccApplication/icon/3dstre.svg"), tr("3D草图"), this);

	QAction* btn_stretching = new QAction(QIcon(":/QtOccApplication/icon/stretching.svg"), tr("拉伸"), this);
	QAction* btn_rotate = new QAction(QIcon(":/QtOccApplication/icon/rotate.svg"), tr("旋转拉伸"), this);
	QAction* btn_excision = new QAction(QIcon(":/QtOccApplication/icon/excision.svg"), tr("切除"), this);
	QAction* btn_pillage = new QAction(QIcon(":/QtOccApplication/icon/pillage.svg"), tr("扫掠"), this);
	QAction* btn_makefillet = new QAction(QIcon(":/QtOccApplication/icon/makefillet.svg"), tr("圆角"), this);
	QAction* btn_makechamfer = new QAction(QIcon(":/QtOccApplication/icon/makechamfer.svg"), tr("倒角"), this);
	QAction* btn_mirror = new QAction(QIcon(":/QtOccApplication/icon/mirror.svg"), tr("镜像"), this);
	QAction* btn_transfer = new QAction(QIcon(":/QtOccApplication/icon/transfer.svg"), tr("平移"), this);
	QAction* btn_rect_array = new QAction(QIcon(":/QtOccApplication/icon/rectangular array.svg"), tr("线性阵列"), this);
	QAction* btn_circle_array = new QAction(QIcon(":/QtOccApplication/icon/circle array.svg"), tr("圆周阵列"), this);
signals:
	void csg_create_cube_signal(const TopoDS_Shape cube);
	void deleteAll();
	void read_file(QString filename);
	void save_step();
	void CsgCubeDesign_signal(double px, double py, double pz, double l, double w, double h);
	void CsgCylinderDesign_signal(double px, double py, double pz, double r, double h);
	void CsgConeDesign_signal(double px, double py, double pz, double r1, double r2, double h);
	void CsgSphereDesign_signal(double px, double py, double pz, double r);

private slots:
	//Read file 
	void on_btnfile_clicked();
	//Save step
	void on_btnsave_clicked();
	//Delete all
	void on_btndeleteAll_clicked();
	//AdaptView
	void on_btnadaptview_clicked();
	//toEntity
	void on_btntoEntity_clicked();
	//CsgCubeDesign
	void on_btncube_clicked();
	void receive_CsgCubeDesign_signal(double px, double py, double pz, double l, double w, double h);

	//CsgCylinderDesign
	void on_btncylinder_clicked();
	void receive_CsgCylinderDesign_signal(double px, double py, double pz, double r, double h);

	//CsgConeDesign
	void on_btncone_clicked();
	void receive_CsgConeDesign_signal(double px, double py, double pz, double r1, double r2, double h);

	//CsgSphereDesign
	void on_btnsphere_clicked();
	void receive_CsgSphereDesign_signal(double px, double py, double pz, double r);

	//CsgBooleanOpt
	void on_btnboolean_clicked();
	
	//StreRectDesign
	void on_btnrect_clicked();

	//Stre3DRectDesign
	void on_btn3drect_clicked();

	//StreCircleDesign
	void on_btncircle_clicked();

	//FeaStretching
	void on_btnstretching_clicked();

	//FeaExcision
	void on_btnexcision_clicked();

	//FeaRotateOpt
	void on_btnrotate_clicked();

	//FeaFilletOpt
	void on_btnfillet_clicked();

	//FeaChamferOpt
	void on_btnchamfer_clicked();

	//FeaCircleArrayOpt
	void on_btncirclearray_clicked();

private:
    Ui::QtOccApplicationClass ui;
	SubC3dWidget *m_SubC3dWidget;
	CsgCubeDesign *CCuD_widget = new CsgCubeDesign();
	CsgCylinderDesign *CCyD_widget = new CsgCylinderDesign();
	CsgCylinderBodyDesign *CCoD_widget = new CsgCylinderBodyDesign();
	CsgSphereDesign *CSD_widget = new CsgSphereDesign();
	CsgBooleanOpt *CBO_widget = new CsgBooleanOpt();

	StreRectDesign *SRD_widget = new StreRectDesign();
	Stre3DRectDesign *S3DRD_widget = new Stre3DRectDesign();
	StreCircleDesign *SCD_widget = new StreCircleDesign();
	
	FeaStretchingOpt *FSO_widget = new FeaStretchingOpt();
	FeaExcisionOpt *FEO_widget = new FeaExcisionOpt();
	FeaRotateOpt *FRO_widget = new FeaRotateOpt();
	FeaFilletOpt *FFO_widget = new FeaFilletOpt();
	FeaChamferOpt *FCO_widget = new FeaChamferOpt();
	FeaCircleArrayOpt *FCAO_widget = new FeaCircleArrayOpt();

	//QDockWidget *ModelingStatus;
};


#endif // QTOCCAPPLICATION_H