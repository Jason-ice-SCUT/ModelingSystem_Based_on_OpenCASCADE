#include "../inc/QtOccApplication.h"



QtOccApplication::QtOccApplication(QWidget *parent, bool useRibbon)
	: SARibbonMainWindow(parent), m_SubC3dWidget(new SubC3dWidget(this))
{
	ui.setupUi(this);
	setCentralWidget(m_SubC3dWidget);

	// 设置应用程序窗口的图标
	setWindowIcon(QIcon(":/QtOccApplication/icon/logo.svg"));

	// 获取SARibbonBar对象，它是SARibbonMainWindow的一部分，用于管理带状工具栏
	SARibbonBar* bar = ribbonBar();

	// 设置应用程序按钮的文本（通常位于带状工具栏的左上角）
	bar->applicationButton()->setText(tr("文件"));

	// 在带状工具栏中添加一个名为"Main"的类别页面
	SARibbonCategory* mainCate = bar->addCategoryPage(tr("建模工具"));

	// 在"Main"类别页面中添加一个面板，并命名为"CSG"
	SARibbonPannel* pannel_GF = mainCate->addPannel(tr("通用功能"));
	// 在"Main"类别页面中添加一个面板，并命名为"CSG"
	SARibbonPannel* pannel_CSG = mainCate->addPannel(tr("CSG建模"));
	// 在"Main"类别页面中添加一个面板，并命名为"Feature_2d"
	SARibbonPannel* pannel_FEATURE_2D = mainCate->addPannel(tr("草图绘制"));
	// 在"Main"类别页面中添加一个面板，并命名为"Feature_3d"
	SARibbonPannel* pannel_FEATURE_3D = mainCate->addPannel(tr("特征建模"));


	// 向pannel_CSG面板中添加带有图标和工具提示的操作按钮
	pannel_GF->addLargeAction(btn_file);
	pannel_GF->addLargeAction(btn_option);
	pannel_GF->addLargeAction(btn_setting);
	pannel_GF->addLargeAction(btn_save);
	pannel_GF->addLargeAction(btn_deleteAll);
	pannel_GF->addLargeAction(btn_adaptview);
	


	// 向pannel_FEATURE_2D面板中添加带有图标和工具提示的操作按钮
	pannel_FEATURE_2D->addLargeAction(btn_rect);
	pannel_FEATURE_2D->addLargeAction(btn_circle);
	pannel_FEATURE_2D->addLargeAction(btn_line);
	pannel_FEATURE_2D->addLargeAction(btn_arced);
	pannel_FEATURE_2D->addLargeAction(btn_connect);
	pannel_FEATURE_2D->addLargeAction(btn_cutting);
	pannel_FEATURE_2D->addLargeAction(btn_3drect);

	// 向pannel_FEATURE_3D面板中添加带有图标和工具提示的操作按钮
	pannel_FEATURE_3D->addLargeAction(btn_stretching);
	pannel_FEATURE_3D->addLargeAction(btn_rotate);
	pannel_FEATURE_3D->addLargeAction(btn_excision);
	pannel_FEATURE_3D->addLargeAction(btn_pillage);
	pannel_FEATURE_3D->addLargeAction(btn_makefillet);
	pannel_FEATURE_3D->addLargeAction(btn_makechamfer);
	pannel_FEATURE_3D->addLargeAction(btn_mirror);
	pannel_FEATURE_3D->addLargeAction(btn_transfer);
	pannel_FEATURE_3D->addLargeAction(btn_rect_array);
	pannel_FEATURE_3D->addLargeAction(btn_circle_array);


	// csg操作使用的中图标尺寸
	pannel_CSG->addMediumAction(btn_cube);
	pannel_CSG->addMediumAction(btn_cylinder);
	pannel_CSG->addMediumAction(btn_sphere);
	pannel_CSG->addMediumAction(btn_cone);
	pannel_CSG->addMediumAction(btn_boolean_opt);
	pannel_CSG->addMediumAction(btn_toEntity);
	

	// feature_2d操作中的图标尺寸
	pannel_FEATURE_2D->addMediumAction(btn_rect);
	pannel_FEATURE_2D->addMediumAction(btn_circle);
	pannel_FEATURE_2D->addMediumAction(btn_line);
	pannel_FEATURE_2D->addMediumAction(btn_arced);
	pannel_FEATURE_2D->addMediumAction(btn_connect);
	pannel_FEATURE_2D->addMediumAction(btn_cutting);
	pannel_FEATURE_2D->addMediumAction(btn_3drect);
	
	// feature_3d操作中的图标尺寸
	pannel_FEATURE_3D->addMediumAction(btn_stretching);
	pannel_FEATURE_3D->addMediumAction(btn_rotate);
	pannel_FEATURE_3D->addMediumAction(btn_excision);
	pannel_FEATURE_3D->addMediumAction(btn_pillage);
	pannel_FEATURE_3D->addMediumAction(btn_makefillet);
	pannel_FEATURE_3D->addMediumAction(btn_makechamfer);
	pannel_FEATURE_3D->addMediumAction(btn_mirror);
	pannel_FEATURE_3D->addMediumAction(btn_transfer);
	pannel_FEATURE_3D->addMediumAction(btn_rect_array);
	pannel_FEATURE_3D->addMediumAction(btn_circle_array);


	// 在带状工具栏中添加另一个名为"Other"的类别页面
	SARibbonCategory* otherCate = bar->addCategoryPage(tr("其他"));

	// 在"Other"类别页面中添加一个面板，并命名为"other"
	SARibbonPannel* pannel2 = otherCate->addPannel(tr("其他"));

	// 向第二个面板中添加一个操作按钮（与上面类似）
	pannel2->addAction(tr("action1"), QIcon(":/QtOccApplication/icon/action.svg"), QToolButton::InstantPopup);

	// 创建一个QComboBox并添加到第二个面板中，用于选择带状工具栏的主题
	QComboBox* combo = new QComboBox(this);
	pannel2->addMediumWidget(combo);

	// 向组合框中添加带状工具栏主题选项
	combo->addItem("RibbonThemeWindows7", static_cast<int>(SARibbonTheme::RibbonThemeWindows7));
	combo->addItem("RibbonThemeOffice2013", static_cast<int>(SARibbonTheme::RibbonThemeOffice2013));
	combo->addItem("RibbonThemeOffice2016Blue", static_cast<int>(SARibbonTheme::RibbonThemeOffice2016Blue));
	combo->addItem("RibbonThemeOffice2021Blue", static_cast<int>(SARibbonTheme::RibbonThemeOffice2021Blue));
	combo->addItem("RibbonThemeDark", static_cast<int>(SARibbonTheme::RibbonThemeDark));
	combo->addItem("RibbonThemeDark2", static_cast<int>(SARibbonTheme::RibbonThemeDark2));

	// 设置默认选中的主题（这里选择的是第五个选项）
	combo->setCurrentIndex(2);

	// 连接组合框的currentIndexChanged信号到一个lambda函数，用于更改带状工具栏的主题
	connect(combo, QOverload< int >::of(&QComboBox::currentIndexChanged), [this, combo](int index) {
		SARibbonTheme th = static_cast<SARibbonTheme>(combo->itemData(index).toInt());
		this->setRibbonTheme(th); });


	// 设置主窗口的初始大小
	resize(800, 600);

	// 在构造函数设置主题会不完全生效
	// QTimer::singleShot(0, this, [ this ]() { this->setRibbonTheme(SARibbonMainWindow::RibbonThemeOffice2016Blue); });

	// more example see MainWindowExample



	/*connect*/

	/*读取模型文件*/
	connect(btn_file, &QAction::triggered, this, &QtOccApplication::on_btnfile_clicked);
	connect(this, SIGNAL(read_file(QString)), m_SubC3dWidget, SLOT(read_entity_file(QString)));
	/*保存成step文件*/
	connect(btn_save, &QAction::triggered, this, &QtOccApplication::on_btnsave_clicked);
	connect(this, SIGNAL(save_step()), m_SubC3dWidget, SLOT(save_entity_step()));

	/*清除*/
	connect(btn_deleteAll, &QAction::triggered, this, &QtOccApplication::on_btndeleteAll_clicked);
	connect(this, SIGNAL(deleteAll()), m_SubC3dWidget, SLOT(deleteAll_modeling()));

	/*自适应显示*/
	connect(btn_adaptview, &QAction::triggered, this, &QtOccApplication::on_btnadaptview_clicked);

	/*转换回实体选择模式*/
	connect(btn_toEntity, &QAction::triggered, this, &QtOccApplication::on_btntoEntity_clicked);

	/*CSG创建立方体*/
	connect(btn_cube, &QAction::triggered, this, &QtOccApplication::on_btncube_clicked);
	//connect(this, SIGNAL(csg_create_cube_signal(TopoDS_Shape)), m_SubC3dWidget, SLOT(show_csg_create_cube(TopoDS_Shape)));//TEST
	connect(CCuD_widget, SIGNAL(csg_create_cube_signal_new(double, double, double, double, double, double)),
		this, SLOT(receive_CsgCubeDesign_signal(double, double, double, double, double, double)));
	connect(this, SIGNAL(CsgCubeDesign_signal(double, double, double, double, double, double)),
		m_SubC3dWidget, SLOT(csg_show_create_cube(double, double, double, double, double, double)));

	/*CSG创建圆柱体*/
	connect(btn_cylinder, &QAction::triggered, this, &QtOccApplication::on_btncylinder_clicked);
	connect(CCyD_widget, SIGNAL(csg_create_cylinder_signal(double, double, double, double, double)),
		this, SLOT(receive_CsgCylinderDesign_signal(double, double, double, double, double)));
	connect(this, SIGNAL(CsgCylinderDesign_signal(double, double, double, double, double)),
		m_SubC3dWidget, SLOT(csg_show_create_cylinder(double, double, double, double, double)));

	/*CSG创建圆台体*/
	connect(btn_cone, &QAction::triggered, this, &QtOccApplication::on_btncone_clicked);
	connect(CCoD_widget, SIGNAL(csg_create_cone_signal(double, double, double, double, double, double)),
		this, SLOT(receive_CsgConeDesign_signal(double, double, double, double, double, double)));
	connect(this, SIGNAL(CsgConeDesign_signal(double, double, double, double, double, double)),
		m_SubC3dWidget, SLOT(csg_show_create_cone(double, double, double, double, double, double)));

	/*CSG创建球体*/
	connect(btn_sphere, &QAction::triggered, this, &QtOccApplication::on_btnsphere_clicked);
	connect(CSD_widget, SIGNAL(csg_create_sphere_signal(double, double, double, double)),
		this, SLOT(receive_CsgSphereDesign_signal(double, double, double, double)));
	connect(this, SIGNAL(CsgSphereDesign_signal(double, double, double, double)),
		m_SubC3dWidget, SLOT(csg_show_create_sphere(double, double, double, double)));

	/*CSG布尔运算*/
	connect(btn_boolean_opt, &QAction::triggered, this, &QtOccApplication::on_btnboolean_clicked);
	connect(m_SubC3dWidget, SIGNAL(csg_boolopt_sendmodel(TopoDS_Shape)), CBO_widget, SLOT(csg_receive_boolopt_model(TopoDS_Shape)));

	connect(CBO_widget, SIGNAL(boolopt_signal_and(TopoDS_Shape, TopoDS_Shape)), m_SubC3dWidget, SLOT(csg_boolopt_and(TopoDS_Shape, TopoDS_Shape)));//并集
	connect(CBO_widget, SIGNAL(boolopt_signal_differ(TopoDS_Shape, TopoDS_Shape)), m_SubC3dWidget, SLOT(csg_boolopt_differ(TopoDS_Shape, TopoDS_Shape)));//差集
	connect(CBO_widget, SIGNAL(boolopt_signal_intersert(TopoDS_Shape, TopoDS_Shape)), m_SubC3dWidget, SLOT(csg_boolopt_intersert(TopoDS_Shape, TopoDS_Shape)));//交集
	connect(m_SubC3dWidget, SIGNAL(csg_boolopt_text()), CBO_widget, SLOT(on_show_boolopt_text()));


	/*特征建模创建矩形草图*/
	connect(btn_rect, &QAction::triggered, this, &QtOccApplication::on_btnrect_clicked);
	connect(SRD_widget, SIGNAL(stre_create_rect_signal(double, double, double, double)), m_SubC3dWidget, SLOT(stre_show_create_rect(double, double, double, double)));
	connect(SRD_widget, SIGNAL(toEntity()), m_SubC3dWidget, SLOT(set_SelectionMode_toEntity()));

	/*特征建模创建3d矩形草图*/
	connect(btn_3drect, &QAction::triggered, this, &QtOccApplication::on_btn3drect_clicked);
	connect(S3DRD_widget, SIGNAL(stre_create_3drect_signal(gp_Pnt, double, double)), m_SubC3dWidget, SLOT(stre_show_create_3drect(gp_Pnt, double, double)));

	/*特征建模创建圆形草图*/
	connect(btn_circle, &QAction::triggered, this, &QtOccApplication::on_btncircle_clicked);
	connect(SCD_widget, SIGNAL(stre_create_circle_signal(double, double, double)), m_SubC3dWidget, SLOT(stre_show_create_circle(double, double, double)));

	/*特征建模拉伸操作*/
	connect(btn_stretching, &QAction::triggered, this, &QtOccApplication::on_btnstretching_clicked);
	connect(FSO_widget, SIGNAL(stretching_H_signal(double,int)) , m_SubC3dWidget, SLOT(feature_stretching(double,int)));

	/*特征建模切除操作*/
	connect(btn_excision, &QAction::triggered, this, &QtOccApplication::on_btnexcision_clicked);
	connect(FEO_widget, SIGNAL(excision_H_signal(double, int)), m_SubC3dWidget, SLOT(feature_excision(double, int)));

	/*特征建模切除操作*/
	connect(btn_excision, &QAction::triggered, this, &QtOccApplication::on_btnexcision_clicked);
	connect(FEO_widget, SIGNAL(excision_H_signal(double, int)), m_SubC3dWidget, SLOT(feature_excision(double, int)));

	/*特征建模旋转拉伸操作*/
	connect(btn_rotate, &QAction::triggered, this, &QtOccApplication::on_btnrotate_clicked);
	connect(FRO_widget, SIGNAL(rotate_choice_mode_ax1()), m_SubC3dWidget, SLOT(receice_rotate_choice()));
	connect(FRO_widget, SIGNAL(rotate_angle_signal(double)), m_SubC3dWidget, SLOT(feature_rotate(double)));

	/*特征建模扫掠操作*/
	connect(btn_pillage, &QAction::triggered, m_SubC3dWidget, &SubC3dWidget::feature_pillage);

	/*特征建模圆角操作*/
	connect(btn_makefillet, &QAction::triggered, this, &QtOccApplication::on_btnfillet_clicked);
	connect(FFO_widget, SIGNAL(makefillet_choose_entity()), m_SubC3dWidget, SLOT(receice_entity_choice()));
	connect(FFO_widget, SIGNAL(makefillet_choose_edge()), m_SubC3dWidget, SLOT(receice_edge_choice()));
	connect(FFO_widget, SIGNAL(makefillet_radius(double)), m_SubC3dWidget, SLOT(feature_makefillet(double)));

	/*特征建模圆角操作*/
	connect(btn_makechamfer, &QAction::triggered, this, &QtOccApplication::on_btnchamfer_clicked);
	connect(FCO_widget, SIGNAL(makechamfer_choose_entity()), m_SubC3dWidget, SLOT(receice_entity_choice()));
	connect(FCO_widget, SIGNAL(makechamfer_choose_edge()), m_SubC3dWidget, SLOT(receice_edge_choice()));
	connect(FCO_widget, SIGNAL(makechamfer_choose_face()), m_SubC3dWidget, SLOT(receice_face_choice()));
	connect(FCO_widget, SIGNAL(makechamfer_dis(double, double)), m_SubC3dWidget, SLOT(feature_makechamfer(double, double)));

	/*特征建模镜像操作*/
	connect(btn_mirror, &QAction::triggered, m_SubC3dWidget, &SubC3dWidget::feature_mirror);

	/*特征建模平移操作*/
	connect(btn_transfer, &QAction::triggered, m_SubC3dWidget, &SubC3dWidget::feature_transfer);

	/*特征建模圆周阵列操作*/
	connect(btn_circle_array, &QAction::triggered, this, &QtOccApplication::on_btncirclearray_clicked);
	connect(FCAO_widget, SIGNAL(CircleArray_choice_mode_entity()), m_SubC3dWidget, SLOT(receice_entity_choice()));
	connect(FCAO_widget, SIGNAL(CircleArray_choice_mode_ax1()), m_SubC3dWidget, SLOT(receice_rotate_choice()));
	connect(FCAO_widget, SIGNAL(CircleArray_num_signal(double)), m_SubC3dWidget, SLOT(feature_circlearray(double)));



}
QtOccApplication::~QtOccApplication()
{
	
}

/*slot*/

/*读取文件*/
void QtOccApplication::on_btnfile_clicked() {
		
	QString filename = QFileDialog::getOpenFileName(
		this, tr("open entity file"),
		"./", tr("STEP files(*.stp *.step *.STEP *.STP);;IGES files(*.igs *.iges *IGS *IGES);;All files (*.*)"));

	if (filename.isEmpty())
	{
		qDebug() << "The file is empty!";
	}
	else
	{
		emit(read_file(filename));
	}
}

/*保存step*/
void QtOccApplication::on_btnsave_clicked() {

	emit save_step();
}

/*清除全部*/
void QtOccApplication::on_btndeleteAll_clicked() {

	emit deleteAll();

}

/*toEntity*/
void QtOccApplication::on_btntoEntity_clicked() {

	m_SubC3dWidget->set_SelectionMode_toEntity();

}


void QtOccApplication::on_btnadaptview_clicked() {
	m_SubC3dWidget->adaptView();
}

/*CSG*/
void QtOccApplication::on_btncube_clicked() {

	//emit csg_create_cube_signal(csg_create_cube_test());
	CCuD_widget->show();
}

void QtOccApplication::on_btncylinder_clicked() {
	CCyD_widget->show();
}

void QtOccApplication::on_btncone_clicked() {
	CCoD_widget->show();
}

void QtOccApplication::on_btnsphere_clicked() {
	CSD_widget->show();
}

void QtOccApplication::on_btnboolean_clicked(){
	//清除CBOwiget收到的模型内容
	CBO_widget->boolopt_model_1.Nullify();
	CBO_widget->boolopt_model_2.Nullify();
	//清除CBOwiget内容
	CBO_widget->CBO_ui.selected_status->clear();
	//show
	CBO_widget->show();
}


void QtOccApplication::receive_CsgCubeDesign_signal(double px, double py, double pz, double l, double w, double h) {
	emit CsgCubeDesign_signal(px, py, pz, l, w, h);
	//qDebug() << "slot called";

}

void QtOccApplication::receive_CsgCylinderDesign_signal(double px, double py, double pz, double r, double h) {
	emit CsgCylinderDesign_signal(px, py, pz, r, h);

}

void QtOccApplication::receive_CsgConeDesign_signal(double px, double py, double pz, double r1, double r2, double h) {
	emit CsgConeDesign_signal(px, py, pz, r1, r2, h);

}

void QtOccApplication::receive_CsgSphereDesign_signal(double px, double py, double pz, double r) {
	emit CsgSphereDesign_signal(px, py, pz, r);


}

/*特征建模*/
void QtOccApplication::on_btnrect_clicked() {

	SRD_widget->show();
	m_SubC3dWidget->set_SelectionMode_toFace();

}


void QtOccApplication::on_btn3drect_clicked() {

	S3DRD_widget->show();
	m_SubC3dWidget->set_SelectionMode_toFace();

}

void QtOccApplication::on_btncircle_clicked() {

	SCD_widget->show();
	m_SubC3dWidget->set_SelectionMode_toFace();

}

void QtOccApplication::on_btnstretching_clicked() {

	FSO_widget->show();
	m_SubC3dWidget->set_SelectionMode_toWire();
}

void QtOccApplication::on_btnexcision_clicked() {

	FEO_widget->show();
	m_SubC3dWidget->set_SelectionMode_toWire();
}

void QtOccApplication::on_btnrotate_clicked() {

	FRO_widget->show();
	m_SubC3dWidget->set_SelectionMode_toWire();
}


void QtOccApplication::on_btnfillet_clicked() {

	FFO_widget->show();
	m_SubC3dWidget->set_SelectionMode_toEntity();
}

void QtOccApplication::on_btnchamfer_clicked() {

	FCO_widget->show();
	m_SubC3dWidget->set_SelectionMode_toEntity();
}

void QtOccApplication::on_btncirclearray_clicked() {

	FCAO_widget->show();
	m_SubC3dWidget->set_SelectionMode_toEntity();
}