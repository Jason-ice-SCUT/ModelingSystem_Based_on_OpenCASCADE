#include <AIS_ViewCube.hxx>
#include <iostream>
#include <QLabel>

#include "../inc/SubC3dWidget.h"
#include "../SARibbonBar_amalgamate/SARibbon.h"


using namespace std;


SubC3dWidget::SubC3dWidget(QWidget* parent):QWidget(parent)
{
	
	
	
	//配置QWidget
	QWidget::setBackgroundRole(QPalette::NoRole);  //无背景
	QWidget::setMouseTracking(true);   //开启鼠标位置追踪

	if (m_context.IsNull()) // 若未定义交互环境
	{
		m_initialize_context(); // 初始化交互环境
	}
#if 0
	//创建一个立方体作测试
	TopoDS_Shape t_topo_bottle = makebottle();
	Handle(AIS_Shape) t_ais_bottle = new AIS_Shape(t_topo_bottle);
	m_context->Display(t_ais_bottle, Standard_True);
	m_view->FitAll();
#endif

	//Qt界面属性设置
	//这个属性告诉 Qt 在屏幕上直接绘制窗口，而不是在双缓冲中绘制。这可能会提高某些类型的动画或实时更新的性能，但也可能导致闪烁或其他视觉问题。
	QWidget::setAttribute(Qt::WA_PaintOnScreen);
	//这个属性告诉 Qt 不要为窗口绘制背景。这通常用于自定义绘制或当窗口完全由子控件组成时。
	QWidget::setAttribute(Qt::WA_NoSystemBackground);
	//设置了控件的焦点策略。Qt::StrongFocus 意味着控件可以通过鼠标点击、键盘导航（如 Tab 键）和快捷键来获得焦点。
	QWidget::setFocusPolicy(Qt::StrongFocus);

	//显示基准面和基准线
	this->Create_AIS_Datum();

	// 设置窗口的初始大小
	//resize(1200, 900);
	
}


SubC3dWidget::~SubC3dWidget()
{}


void SubC3dWidget::m_initialize_context()
{
	//若交互式上下文为空，则创建对象
	if (m_context.IsNull())
	{
		//此对象提供与X server的连接，在Windows和Mac OS中不起作用
		Handle(Aspect_DisplayConnection) m_display_donnection = new Aspect_DisplayConnection();

		//创建OpenGl图形驱动
		if (m_graphic_driver.IsNull())
		{
			m_graphic_driver = new OpenGl_GraphicDriver(m_display_donnection);
		}
		//获取QWidget的窗口系统标识符
		WId window_handle = (WId)QWidget::winId();
#ifdef _WIN32
		// 创建Windows NT 窗口
		Handle(WNT_Window) wind = new WNT_Window((Aspect_Handle)window_handle);
#else
		// 创建XLib window 窗口
		Handle(Xw_Window) wind = new Xw_Window(m_display_donnection, (Window)window_handle);
#endif
		//创建3D查看器
		m_viewer = new V3d_Viewer(m_graphic_driver);

		//创建视图
		m_view = m_viewer->CreateView();
		m_view->SetWindow(wind);

		//打开窗口
		if (!wind->IsMapped())
		{
			wind->Map();
		}
		m_context = new AIS_InteractiveContext(m_viewer);  //创建交互式上下文

		//配置查看器的光照
		m_viewer->SetDefaultLights();
		m_viewer->SetLightOn();

		//设置视图的背景颜色为灰色
		m_view->SetBackgroundColor(Quantity_NOC_GRAY);
		m_view->MustBeResized();

		//显示视方体(视图)
		auto view_cube = new AIS_ViewCube();
		auto transform_pers = new Graphic3d_TransformPers(Graphic3d_TMF_TriedronPers,
			Aspect_TOTP_RIGHT_LOWER,//右下角
			Graphic3d_Vec2i(85, 85));
		view_cube->SetTransformPersistence(transform_pers);
		m_context->Display(view_cube, Standard_True);

		//设置显示模式
		m_context->SetDisplayMode(AIS_Shaded, Standard_True);

		// 设置模型高亮的风格
		Handle(Prs3d_Drawer) t_hilight_style = m_context->HighlightStyle(); // 获取高亮风格
		t_hilight_style->SetMethod(Aspect_TOHM_COLOR);  // 颜色显示方式
		t_hilight_style->SetColor(Quantity_NOC_LIGHTYELLOW);    // 设置高亮颜色
		t_hilight_style->SetDisplayMode(1); // 整体高亮
		t_hilight_style->SetTransparency(0.2f); // 设置透明度

		// 设置选择模型的风格
		Handle(Prs3d_Drawer) t_select_style = m_context->SelectionStyle();  // 获取选择风格
		t_select_style->SetMethod(Aspect_TOHM_COLOR);  // 颜色显示方式
		t_select_style->SetColor(Quantity_NOC_LIGHTSEAGREEN);   // 设置选择后颜色
		t_select_style->SetDisplayMode(1); // 整体高亮
		t_select_style->SetTransparency(0.4f); // 设置透明度

		m_view->SetZoom(100);   // 放大

		// 激活二维网格
		m_viewer->SetRectangularGridValues(0, 0, 1, 1, 0);
		m_viewer->SetRectangularGridGraphicValues(2.01, 2.01, 0);
		m_viewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);

		
	}
}


void SubC3dWidget::paintEvent(QPaintEvent *)
{
	m_view->Redraw();
}

void SubC3dWidget::resizeEvent(QResizeEvent *)
{
	if (!m_view.IsNull())
	{
		m_view->MustBeResized();
	}
}

void SubC3dWidget::mousePressEvent(QMouseEvent *event)
{
	if ((event->buttons()&Qt::LeftButton) && (event->buttons()&Qt::RightButton))
	{
		// 鼠标左右键齐按：初始化平移
		m_x_max = event->x();
		m_y_max = event->y();
	}
#if 0
	else if (event->buttons()&Qt::LeftButton)
	{
		// 1.点击前，将鼠标位置传递到交互环境
		m_context->MoveTo(event->pos().x(), event->pos().y(), m_view, Standard_True);
		//2. 鼠标左键：选择模型(执行选择)
		AIS_StatusOfPick t_pick_status = AIS_SOP_NothingSelected;
		if (qApp->keyboardModifiers() == Qt::ControlModifier)
		{
			t_pick_status = m_context->SelectDetected(AIS_SelectionScheme_Add);   // 多选
		}
		else
		{
			t_pick_status = m_context->SelectDetected();        // 单选
		}
		//3.处理选择结果(选择要进行布尔运算的模型)

		//4.刷新视图
		m_view->Update();

	}
#endif
	else if (event->buttons()&Qt::LeftButton) {
		// 0.创建selectde obj即选择对象的初始指针
		m_context->InitSelected();

		// 1.点击前，将鼠标位置传递到交互环境
		m_context->MoveTo(event->pos().x(), event->pos().y(), m_view, Standard_True);
		// 2. 鼠标左键：选择模型(执行选择)
		AIS_StatusOfPick t_pick_status = AIS_SOP_NothingSelected;
		if (qApp->keyboardModifiers() == Qt::ControlModifier)
		{
			t_pick_status = m_context->SelectDetected(AIS_SelectionScheme_Add);   // 多选
		}
		else
		{
			t_pick_status = m_context->SelectDetected();        // 单选
		}
		//3.处理选择结果(选择要进行布尔运算的模型)
		if (t_pick_status == AIS_SOP_OneSelected) {
			for (m_context->InitSelected(); m_context->MoreSelected(); m_context->NextSelected()) {
				Handle(SelectMgr_EntityOwner) anOwner = m_context->SelectedOwner();
				Handle(AIS_InteractiveObject) selectedobj = Handle(AIS_InteractiveObject)::DownCast(anOwner->Selectable());
				ais_models.push_back(selectedobj);
				//标志位4为选择边
				if (selected_flag == 4) {
					selected_edge = selectedobj;
					if (Handle(StdSelect_BRepOwner) aBRepOwner = Handle(StdSelect_BRepOwner)::DownCast(anOwner)) {
						// to be able to use the picked shape
						TopoDS_Shape shape_edge = aBRepOwner->Shape();
						// 转换为 TopoDS_Face
						TopoDS_Edge edge = TopoDS::Edge(shape_edge);

						target_Edge = edge;
						qDebug() << "You have selected an edge.";

					}
				}
				//标志位3为选择轴线
				if (selected_flag == 3) {
					selected_ax1 = selectedobj;
					if (selectedobj->IsKind(STANDARD_TYPE(AIS_Axis))) {
						Handle(AIS_Axis) anAISAxis = Handle(AIS_Axis)::DownCast(selectedobj);
						Handle(Geom_Line) geom = anAISAxis->Component();
						target_ax1 = gp_Ax1(geom->Lin().Location(), geom->Lin().Direction());
					}
				}
				//标志位2为选择线框
				if (selected_flag == 2) {
					selected_wire = selectedobj;
					if (Handle(StdSelect_BRepOwner) aBRepOwner = Handle(StdSelect_BRepOwner)::DownCast(anOwner)) {
						// to be able to use the picked shape
						TopoDS_Shape shape_wire = aBRepOwner->Shape();
						// 转换为 TopoDS_Face
						TopoDS_Wire wire = TopoDS::Wire(shape_wire);

						target_Wire = wire;
						qDebug() << "You have selected a wire.";

					}
				}
				//标志位1为选择面
				else if (selected_flag == 1) {
					selected_face = selectedobj;
					if (Handle(StdSelect_BRepOwner) aBRepOwner = Handle(StdSelect_BRepOwner)::DownCast(anOwner)) {
						// to be able to use the picked shape
						TopoDS_Shape shape_face = aBRepOwner->Shape();
						// 转换为 TopoDS_Face
						TopoDS_Face face = TopoDS::Face(shape_face);

						target_Pln = face;
						qDebug() << "You have selected a plane.";

					}
				}
				//标志位2为实体
				else if ((selected_flag == 0))
				{
					selected_entity = selectedobj;
					if (Handle(StdSelect_BRepOwner) aBRepOwner = Handle(StdSelect_BRepOwner)::DownCast(anOwner)) {
						// to be able to use the picked shape
						TopoDS_Shape bool_Shape = aBRepOwner->Shape();
						emit csg_boolopt_sendmodel(bool_Shape);
						emit csg_boolopt_text();
						//public_faceExpoler.Init(bool_Shape, TopAbs_FACE);
						target_Shape = bool_Shape;
					}
					else
					{
						qDebug() << "The selected is null!";
					}
				}


			}

			//4.刷新视图
			m_view->Update();
			//m_context->ClearSelected();

		}
	}
	else if (event->buttons()&Qt::MiddleButton)
	{
		// 鼠标滚轮键：初始化平移
		m_x_max = event->x();
		m_y_max = event->y();
		// 鼠标滚轮键：初始化旋转
		m_view->StartRotation(event->x(), event->y());
	}

	else if (event->buttons()&Qt::RightButton)
	{
		// 1.点击前，将鼠标位置传递到交互环境
		m_context->MoveTo(event->pos().x(), event->pos().y(), m_view, Standard_True);
		//2. 鼠标右键：选择模型(执行选择)
		AIS_StatusOfPick t_pick_status = AIS_SOP_NothingSelected;
		if (qApp->keyboardModifiers() == Qt::ControlModifier)
		{
			t_pick_status = m_context->SelectDetected(AIS_SelectionScheme_Add);   // 多选
		}
		else
		{
			t_pick_status = m_context->SelectDetected();        // 单选
		}
		//3.处理选择结果(右键删除)
		if (t_pick_status == AIS_SOP_OneSelected) {//选中一个
		//Handle(AIS_InteractiveObject) selected = m_context->SelectedInteractive();
		// 执行选中后的逻辑（如显示属性
			m_context->EraseSelected(Standard_True);
		}
		//4.刷新视图
		m_view->Update();

	}

	
}

void SubC3dWidget::mouseReleaseEvent(QMouseEvent *event)
{
	// 将鼠标位置传递到交互环境
	m_context->MoveTo(event->pos().x(), event->pos().y(), m_view, Standard_True);
}

void SubC3dWidget::mouseMoveEvent(QMouseEvent *event)
{
	if ((event->buttons()&Qt::LeftButton) && (event->buttons()&Qt::RightButton))
	{
		// 鼠标左右键齐按：执行平移
		m_view->Pan(event->pos().x() - m_x_max, m_y_max - event->pos().y());
		m_x_max = event->x();
		m_y_max = event->y();
	}
	else if (event->buttons()&Qt::MiddleButton)
	{
		// 鼠标滚轮键
		if (qApp->keyboardModifiers() == Qt::ShiftModifier)    // 且按下Shift键
		{
			// 鼠标滚轮键：执行平移
			m_view->Pan(event->pos().x() - m_x_max, m_y_max - event->pos().y());
			m_x_max = event->x();
			m_y_max = event->y();
		}
		else
		{
			// 鼠标滚轮键：执行旋转
			m_view->Rotation(event->x(), event->y());
		}
	}
	else
	{
		// 将鼠标位置传递到交互环境
		m_context->MoveTo(event->pos().x(), event->pos().y(), m_view, Standard_True);
	}
}

void SubC3dWidget::wheelEvent(QWheelEvent *event)
{
	m_view->StartZoomAtPoint(event->position().x(), event->position().y());
	m_view->ZoomAtPoint(0, 0, event->angleDelta().y(), 0); //执行缩放
}

//自适应显示
void SubC3dWidget::adaptView() {
	if (!m_view.IsNull()) {
		m_view->MustBeResized();
		//切换到模型的等轴测视角
		m_view->SetProj(V3d_XposYposZpos, Standard_True);
		m_view->FitAll();
		m_view->ZFitAll();
	}
}


void SubC3dWidget::Create_AIS_Datum() {
	/*---------------- 绘制基准面 ----------------*/
	// 创建XY平面（由gp::XOY()定义，即原点在(0,0,0)，法向量沿Z轴）
	Handle(Geom_Plane) planeXY = new Geom_Plane(gp_Pln(gp::XOY()));
	// 转换成TopoDS_Face，可选

	// 创建AIS平面对象用于可视化
	Handle(AIS_Plane) aisPlaneXY = new AIS_Plane(planeXY);
	// 设置平面在缩放时保持固定位置（始终以世界坐标系原点为中心）
	aisPlaneXY->SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_ZoomPers, gp_Pnt(0, 0, 0)));
	// 将平面置于最高图层（始终显示在最前面）
	aisPlaneXY->SetZLayer(Graphic3d_ZLayerId_Topmost);
	// 设置显示模式为0（默认线框模式）
	aisPlaneXY->SetDisplayMode(0);
	// 将平面对象添加到显示上下文（第二个参数Standard_False表示不立即更新视图）
	m_context->Display(aisPlaneXY, Standard_False);

	// 创建XZ平面（由gp::ZOX()定义，法向量沿Y轴）
	Handle(Geom_Plane) planeXZ = new Geom_Plane(gp_Pln(gp::ZOX()));
	Handle(AIS_Plane) aisPlaneXZ = new AIS_Plane(planeXZ);
	aisPlaneXZ->SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_ZoomPers, gp_Pnt(0, 0, 0)));
	aisPlaneXZ->SetZLayer(Graphic3d_ZLayerId_Topmost);
	aisPlaneXZ->SetDisplayMode(0);
	m_context->Display(aisPlaneXZ, Standard_False);

	// 创建YZ平面（由gp::YOZ()定义，法向量沿X轴）
	Handle(Geom_Plane) planeYZ = new Geom_Plane(gp_Pln(gp::YOZ()));
	Handle(AIS_Plane) aisPlaneYZ = new AIS_Plane(planeYZ);
	aisPlaneYZ->SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_ZoomPers, gp_Pnt(0, 0, 0)));
	aisPlaneYZ->SetZLayer(Graphic3d_ZLayerId_Topmost);
	aisPlaneYZ->SetDisplayMode(0);
	m_context->Display(aisPlaneYZ, Standard_False);

	/*---------------- 创建3D坐标系轴线 ----------------*/
	gp_Pnt origin(0, 0, 0); // 定义坐标系原点

	// 创建X轴（红色）
	gp_Dir xDir(1, 0, 0); // X轴方向向量
	Handle(AIS_Axis) xAxis = new AIS_Axis(gp_Ax1(origin, xDir)); // 创建轴线对象
	xAxis->SetInfiniteState(Standard_False); // 设置为有限长度（默认显示一定长度）
	xAxis->SetColor(Quantity_NOC_RED); // 设置颜色为红色
	xAxis->SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_ZoomPers, origin)); // 保持缩放时位置不变
	xAxis->Attributes()->SetZLayer(Graphic3d_ZLayerId_Topmost); // 置顶显示
	m_context->Display(xAxis, Standard_True); // 显示轴线（Standard_True立即更新视图）

	// 创建Y轴（绿色）
	gp_Dir yDir(0, 1, 0);
	Handle(AIS_Axis) yAxis = new AIS_Axis(gp_Ax1(origin, yDir));
	yAxis->SetColor(Quantity_NOC_GREEN);
	yAxis->SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_ZoomPers, origin));
	yAxis->Attributes()->SetZLayer(Graphic3d_ZLayerId_Topmost);
	m_context->Display(yAxis, Standard_True); // 注意：此处应为m_context，可能是笔误

	// 创建Z轴（蓝色）
	gp_Dir zDir(0, 0, 1);
	Handle(AIS_Axis) zAxis = new AIS_Axis(gp_Ax1(origin, zDir));
	zAxis->SetColor(Quantity_NOC_BLUE);
	zAxis->SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_ZoomPers, origin));
	zAxis->Attributes()->SetZLayer(Graphic3d_ZLayerId_Topmost);
	m_context->Display(zAxis, Standard_True);

	// 视图操作
	m_view->FitAll();    // 自动调整视图显示所有对象
	m_view->ZFitAll();   // 调整Z方向裁剪平面以显示全部内容
	m_view->MustBeResized(); // 强制视图根据窗口尺寸重新计算投影参数
}



void SubC3dWidget::HighlightPlane(const TopoDS_Face& face) {
	m_context->Remove(GetCurrentHighlight(), false); // 清除之前的高亮
	Handle(AIS_Shape) aisFace = new AIS_Shape(face);
	aisFace->SetColor(Quantity_NOC_RED);
	m_context->Display(aisFace, true);
	SetCurrentHighlight(aisFace); // 记录当前高亮对象
}

Handle(AIS_InteractiveObject) SubC3dWidget::GetCurrentHighlight() {
	return highlight[0];
}

void SubC3dWidget::SetCurrentHighlight(Handle(AIS_Shape) aisface) {
	highlight[0] = aisface;
}




void SubC3dWidget::deleteAll_modeling() {
	Handle(AIS_InteractiveContext) context = m_context; // 获取AIS_InteractiveContext对象
	context->EraseAll(Standard_True); // 从AIS_InteractiveContext对象中删除所有对象
	//models.clear();
	while (!ais_queue.empty()) {
		ais_queue.pop();
	}
	auto view_cube = new AIS_ViewCube();
	auto transform_pers = new Graphic3d_TransformPers(Graphic3d_TMF_TriedronPers,
		Aspect_TOTP_RIGHT_LOWER,//右下角
		Graphic3d_Vec2i(85, 85));
	view_cube->SetTransformPersistence(transform_pers);
	m_context->Display(view_cube, Standard_True);
	Create_AIS_Datum();
}

void SubC3dWidget::csg_show_create_cube(double px, double py, double pz, double l, double w, double h) {
	TopoDS_Shape acube = csg_create_cube(px, py, pz, l, w, h);
	//models.push_back(acube);
	Handle(AIS_Shape) ais_cube = new AIS_Shape(acube);
	m_context->SetColor(ais_cube, Quantity_NOC_LIGHTGOLDENROD, Standard_True);
	m_context->Display(ais_cube, Standard_True);
	m_view->FitAll();
	ais_queue.push(ais_cube);
}


void SubC3dWidget::csg_show_create_cylinder(double px, double py, double pz, double r, double h) {
	TopoDS_Shape acylinder = csg_create_cylinder(px, py, pz, r, h);
	//models.push_back(acylinder);
	Handle(AIS_Shape) ais_cylinder = new AIS_Shape(acylinder);
	m_context->SetColor(ais_cylinder, Quantity_NOC_LIGHTBLUE, Standard_True);
	m_context->Display(ais_cylinder, Standard_True);
	m_view->FitAll();
	ais_queue.push(ais_cylinder);
}

void SubC3dWidget::csg_show_create_cone(double px, double py, double pz, double r1, double r2, double h){
	TopoDS_Shape acone = csg_create_cone(px, py, pz, r1, r2, h);
	//models.push_back(acone);
	Handle(AIS_Shape) ais_cone = new AIS_Shape(acone);
	m_context->Display(ais_cone, Standard_True);
	m_view->FitAll();
	ais_queue.push(ais_cone);
}

void SubC3dWidget::csg_show_create_sphere(double px, double py, double pz, double r) {
	TopoDS_Shape asphere = csg_create_sphere(px, py, pz, r);
	//models.push_back(asphere);
	Handle(AIS_Shape) ais_sphere = new AIS_Shape(asphere);
	m_context->SetColor(ais_sphere, Quantity_NOC_LIGHTBLUE, Standard_True);
	m_context->Display(ais_sphere, Standard_True);
	m_view->FitAll();
	ais_queue.push(ais_sphere);
}




//并集运算
void SubC3dWidget::csg_boolopt_and(TopoDS_Shape model_1, TopoDS_Shape model_2) {

	TopoDS_Shape aboolopt_model = csg_boolean_opt_and(model_1, model_2);
	Handle(AIS_Shape) ais_aboolopt_model = new AIS_Shape(aboolopt_model);
	m_context->SetColor(ais_aboolopt_model, Quantity_NOC_LIGHTPINK, Standard_True);
	m_context->Display(ais_aboolopt_model, Standard_True);
	for (int i = 0; i < ais_models.size(); ++i) {
		m_context->Remove(ais_models[i], 0);
	}
	m_context->UpdateCurrentViewer();
	m_view->FitAll();
	ais_queue.push(ais_aboolopt_model);
}

//差集运算
void SubC3dWidget::csg_boolopt_differ(TopoDS_Shape model_1, TopoDS_Shape model_2) {

	TopoDS_Shape aboolopt_model = csg_boolean_opt_differ(model_1, model_2);
	Handle(AIS_Shape) ais_aboolopt_model = new AIS_Shape(aboolopt_model);
	m_context->SetColor(ais_aboolopt_model, Quantity_NOC_CORNSILK1, Standard_True);
	m_context->Display(ais_aboolopt_model, Standard_True);
	for (int i = 0; i < ais_models.size(); ++i) {
		m_context->Remove(ais_models[i], 0);
	}
	m_context->UpdateCurrentViewer();
	m_view->FitAll();
	ais_queue.push(ais_aboolopt_model);
}

//交集运算
void SubC3dWidget::csg_boolopt_intersert(TopoDS_Shape model_1, TopoDS_Shape model_2) {

	TopoDS_Shape aboolopt_model = csg_boolean_opt_intersert(model_1, model_2);
	Handle(AIS_Shape) ais_aboolopt_model = new AIS_Shape(aboolopt_model);
	m_context->SetColor(ais_aboolopt_model, Quantity_NOC_GOLD4, Standard_True);
	m_context->Display(ais_aboolopt_model, Standard_True);
	for (int i = 0; i < ais_models.size(); ++i) {
		m_context->Remove(ais_models[i], 0);
	}
	m_context->UpdateCurrentViewer();
	m_view->FitAll();
	ais_queue.push(ais_aboolopt_model);
}

//创建矩形线框草图
void SubC3dWidget::stre_show_create_rect(double p0_u, double p0_v, double l, double w) {
	//构建矩形线框
	TopoDS_Wire rect_wire = stre_create_rect_onPln(target_Pln, p0_u, p0_v, l, w);
	Handle(AIS_Shape) ais_rect = new AIS_Shape(rect_wire);
	m_context->Display(ais_rect, Standard_True);
	m_view->FitAll();
}

//创建圆形线框草图
void SubC3dWidget::stre_show_create_circle(double p0_u, double p0_v, double R) {
	//构建圆形线框
	TopoDS_Wire circle_wire = stre_create_circle_onPln(target_Pln, p0_u, p0_v, R);
	Handle(AIS_Shape) ais_circle = new AIS_Shape(circle_wire);
	m_context->Display(ais_circle, Standard_True);
	m_view->FitAll();
}

//创建3d矩形线框草图
void SubC3dWidget::stre_show_create_3drect(gp_Pnt p0, double l, double w) {

	TopoDS_Wire rect_wire = stre_create_rect_3D(p0, l, w);
	Handle(AIS_Shape) ais_rect = new AIS_Shape(rect_wire);
	m_context->Display(ais_rect, Standard_True);
	m_view->FitAll();
}

//拉伸操作
void SubC3dWidget::feature_stretching(double h, int flag) {
	
	TopoDS_Shape prism = Feature_stretching_opt(target_Wire, h, flag);
	Handle(AIS_Shape) ais_prism = new AIS_Shape(prism);
	m_context->Display(ais_prism, Standard_True);
	m_view->FitAll();
	ais_queue.push(ais_prism);
}

//切除操作
void SubC3dWidget::feature_excision(double h, int flag) {
	//拉伸一个实体
	TopoDS_Shape prism = Feature_stretching_opt(target_Wire, h, flag);
	//和其他实体做差运算
	NCollection_List<Handle(AIS_InteractiveObject)> AIS_ObjectList = GetGetAllInteractiveObjects(m_context);
	for (const auto& obj : AIS_ObjectList) {
		if (obj->Type() == AIS_KOI_Shape) {
			Handle(AIS_Shape) anAisShape = Handle(AIS_Shape)::DownCast(obj);
			TopoDS_Shape theShape = anAisShape->Shape();
			csg_boolopt_differ(theShape, prism);
			m_context->Remove(anAisShape,0);
		}
	}
	m_view->FitAll();
}

//旋转拉伸操作
void SubC3dWidget::feature_rotate(double angle) {
	//旋转拉伸一个实体
	TopoDS_Shape rotate = Feature_rotate_opt(target_Wire, target_ax1, angle);
	Handle(AIS_Shape) ais_rotate = new AIS_Shape(rotate);
	m_context->Display(ais_rotate, Standard_True);
	m_view->FitAll();
	ais_queue.push(ais_rotate);
}

//管道扫掠操作(demo)
void SubC3dWidget::feature_pillage() {

	// 创建路径
// 定义 U 型曲线的三个部分的端点
	gp_Pnt startPoint(0, 0, 0);     // 底部起点
	gp_Pnt middlePoint1(0, 0, 50); // 底部中间点
	gp_Pnt middlePoint2(50, 00, 50); // 竖直部分的顶点
	gp_Pnt endPoint(0, 50, 0);      // 另一竖直部分的顶点

	// 创建 U 型曲线的边
	TopoDS_Edge bottomEdge = BRepBuilderAPI_MakeEdge(startPoint, middlePoint1);  // 底边
	TopoDS_Edge verticalEdge1 = BRepBuilderAPI_MakeEdge(middlePoint1, middlePoint2); // 第一竖边
	TopoDS_Edge verticalEdge2 = BRepBuilderAPI_MakeEdge(middlePoint2, endPoint);    // 第二竖边

	// 将边连接成一个 U 型曲线
	TopoDS_Wire uShapeWire = BRepBuilderAPI_MakeWire(bottomEdge, verticalEdge1, verticalEdge2);
	m_context->Display(new AIS_Shape(uShapeWire), Standard_True);

	//return;
	// 创建截面（圆形截面）
	gp_Ax2 circleAxis(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1));
	Standard_Real radius = 5;
	Handle(Geom_Circle) circle = new Geom_Circle(circleAxis, radius);
	TopoDS_Edge circleEdge = BRepBuilderAPI_MakeEdge(circle);
	TopoDS_Wire circleWire = BRepBuilderAPI_MakeWire(circleEdge);

	TopoDS_Shape pipe = Feature_pillage_opt(circleWire, uShapeWire);//调用函数
	Handle(AIS_Shape) ais_pipe = new AIS_Shape(pipe);
	m_context->Display(ais_pipe, Standard_True);
	m_view->FitAll();
	ais_queue.push(ais_pipe);
}



void SubC3dWidget::receice_rotate_choice() {

	selected_flag = 3;

}

//圆角
void SubC3dWidget::feature_makefillet(double r){

	TopoDS_Shape after_makefillet = Feature_MakeFillet_opt(target_Shape, target_Edge, r);
	Handle(AIS_Shape) ais_after_makefillet = new AIS_Shape(after_makefillet);
	m_context->Display(ais_after_makefillet, Standard_True);
	NCollection_List<Handle(AIS_InteractiveObject)> AIS_ObjectList = GetGetAllInteractiveObjects(m_context);
	for (const auto& obj : AIS_ObjectList) {
		if (obj->Type() == AIS_KOI_Shape) {
			Handle(AIS_Shape) anAisShape = Handle(AIS_Shape)::DownCast(obj);
			TopoDS_Shape theShape = anAisShape->Shape();
			if (target_Shape == theShape) {
				m_context->Remove(anAisShape, 0);
			}
		}
	}
	m_view->FitAll();
	ais_queue.push(ais_after_makefillet);
}


//倒角
void SubC3dWidget::feature_makechamfer(double dis1, double dis2) {

	TopoDS_Shape after_makechamfer = Feature_MakeChamfer_opt(target_Shape, target_Edge, target_Pln, dis1, dis2);
	Handle(AIS_Shape) ais_after_makechamfer = new AIS_Shape(after_makechamfer);
	m_context->Display(ais_after_makechamfer, Standard_True);
	NCollection_List<Handle(AIS_InteractiveObject)> AIS_ObjectList = GetGetAllInteractiveObjects(m_context);
	for (const auto& obj : AIS_ObjectList) {
		if (obj->Type() == AIS_KOI_Shape) {
			Handle(AIS_Shape) anAisShape = Handle(AIS_Shape)::DownCast(obj);
			TopoDS_Shape theShape = anAisShape->Shape();
			if (target_Shape == theShape) {
				m_context->Remove(anAisShape, 0);
			}
		}
	}
	m_view->FitAll();
	ais_queue.push(ais_after_makechamfer);
}

void SubC3dWidget::receice_entity_choice() {
	set_SelectionMode_toEntity();
}

void SubC3dWidget::receice_edge_choice() {
	set_SelectionMode_toEdge();
}

void SubC3dWidget::receice_face_choice() {
	set_SelectionMode_toFace();
}



//镜像
void SubC3dWidget::feature_mirror() {

	// 创建一个坐标系平面
	// gp_Ax2 定义了一个默认右手坐标系，包含原点、Z轴方向(法向)和X轴方向，即XOY平面
	gp_Ax2 plane = gp_Ax2();

	TopoDS_Shape mshape = csg_create_cone(0, 0, 3, 2, 4, 6);
	TopoDS_Shape mirror_shape = Feature_mirror_opt(mshape, plane);
	Handle(AIS_Shape) ais_mshape = new AIS_Shape(mshape);
	Handle(AIS_Shape) ais_mirror_shape = new AIS_Shape(mirror_shape);
	m_context->Display(ais_mshape, Standard_True);
	m_context->Display(ais_mirror_shape, Standard_True);
	m_view->FitAll();
	ais_queue.push(ais_mshape);
	ais_queue.push(ais_mirror_shape);
}

//平移
void SubC3dWidget::feature_transfer() {
	TopoDS_Shape mshape = csg_create_cone(0, 0, 3, 2, 4, 6);
	gp_Vec translationVec(0, 20, 0);
	TopoDS_Shape transfer_shape = Feature_transfer_opt(mshape, translationVec);
	Handle(AIS_Shape) ais_mshape = new AIS_Shape(mshape);
	Handle(AIS_Shape) ais_transfer_shape = new AIS_Shape(transfer_shape);
	m_context->Display(ais_mshape, Standard_True);
	m_context->Display(ais_transfer_shape, Standard_True);
	m_view->FitAll();
	ais_queue.push(ais_mshape);
	ais_queue.push(ais_transfer_shape);
}

//圆周阵列
void SubC3dWidget::feature_circlearray(double num) {

	TopoDS_Shape circlearray = Feature_CircleArray_opt(target_Shape, target_ax1,num);
	Handle(AIS_Shape) ais_circlearray = new AIS_Shape(circlearray);
	m_context->Display(ais_circlearray, Standard_True);
	m_view->FitAll();
	ais_queue.push(ais_circlearray);
}



/*通用功能*/

//遍历并存储所有交互对象
NCollection_List<Handle(AIS_InteractiveObject)> 
SubC3dWidget::GetGetAllInteractiveObjects(const Handle(AIS_InteractiveContext)& context) {
	NCollection_List<Handle(AIS_InteractiveObject)> objectList;
	AIS_ListOfInteractive allObjects;
	m_context->ObjectsInside(allObjects); // -1 表示不按类型过滤

	// 遍历所有交互对象
	for (AIS_ListIteratorOfListOfInteractive it(allObjects); it.More(); it.Next()) {
		Handle(AIS_InteractiveObject)& obj = it.Value();
		// 处理对象 obj
		if (!obj.IsNull()) {
			objectList.Append(obj);
		}
	}
	return objectList;
}


void SubC3dWidget::set_SelectionMode_toEntity() {
	NCollection_List<Handle(AIS_InteractiveObject)> AIS_ObjectList = GetGetAllInteractiveObjects(m_context);
	for (const auto& obj : AIS_ObjectList) {


		m_context->Deactivate(obj, AIS_Shape::SelectionMode(TopAbs_FACE));
		m_context->Activate(obj, AIS_Shape::SelectionMode(TopAbs_SHAPE));
		//m_context->Redisplay(ais_queue.front(), Standard_True);
		m_context->SetPixelTolerance(2);
		// 刷新视图
		m_viewer->RedrawImmediate();
	}
	selected_flag = 0;

}

void SubC3dWidget::set_SelectionMode_toFace() {
	NCollection_List<Handle(AIS_InteractiveObject)> AIS_ObjectList = GetGetAllInteractiveObjects(m_context);
	for (const auto& obj : AIS_ObjectList) {


		m_context->Deactivate(obj, AIS_Shape::SelectionMode(TopAbs_SHAPE));
		m_context->Activate(obj, AIS_Shape::SelectionMode(TopAbs_FACE));
		//m_context->Redisplay(ais_queue.front(), Standard_True);
		m_context->SetPixelTolerance(2);
		// 刷新视图
		m_viewer->RedrawImmediate();
	}
	selected_flag = 1;

}

void SubC3dWidget::set_SelectionMode_toWire() {

	NCollection_List<Handle(AIS_InteractiveObject)> AIS_ObjectList = GetGetAllInteractiveObjects(m_context);
	for (const auto& obj : AIS_ObjectList) {


		m_context->Deactivate(obj, AIS_Shape::SelectionMode(TopAbs_SHAPE));
		m_context->Activate(obj, AIS_Shape::SelectionMode(TopAbs_WIRE));
		//m_context->Redisplay(ais_queue.front(), Standard_True);
		m_context->SetPixelTolerance(2);
		// 刷新视图
		m_viewer->RedrawImmediate();
	}
	selected_flag = 2;

}

void SubC3dWidget::set_SelectionMode_toEdge() {

	NCollection_List<Handle(AIS_InteractiveObject)> AIS_ObjectList = GetGetAllInteractiveObjects(m_context);
	for (const auto& obj : AIS_ObjectList) {

		m_context->Deactivate(obj, AIS_Shape::SelectionMode(TopAbs_SHAPE));
		m_context->Activate(obj, AIS_Shape::SelectionMode(TopAbs_EDGE));
		//m_context->Redisplay(ais_queue.front(), Standard_True);
		m_context->SetPixelTolerance(2);
		// 刷新视图
		m_viewer->RedrawImmediate();
	}
	selected_flag = 4;
}

void SubC3dWidget::save_entity_step() {
	// 创建一个复合体（Compound）保存所有模型
	TopoDS_Compound allShapes;
	BRep_Builder builder;
	builder.MakeCompound(allShapes);
	// 遍历所有显示的对象
	for (Handle(AIS_Shape) ais_front = ais_queue.front(); ais_front != ais_queue.back(); ) {
		Handle(AIS_Shape) obj = ais_queue.front();

		// 检查是否为 AIS_Shape 对象
		if (obj->IsKind(STANDARD_TYPE(AIS_Shape))) {
			Handle(AIS_Shape) aisShape = Handle(AIS_Shape)::DownCast(obj);
			TopoDS_Shape shape = aisShape->Shape();
			// 将形状添加到复合体
			builder.Add(allShapes, shape);
		}
		//队列首位对象调至末尾
		ais_queue.pop();
		ais_queue.push(obj);
		//计数
		int i = 1;
		qDebug() << i;
		i++;
	}
	//导出为 STEP 文件
	STEPControl_Writer writer;
	IFSelect_ReturnStatus status = writer.Transfer(allShapes, STEPControl_ManifoldSolidBrep);
	if (status == IFSelect_RetDone) {
		writer.Write("Models.stp");
		qDebug() << "Be successful to save the file. ";
	}
	else {
		// 处理导出错误
		qDebug() << "Be failed to save the file. ";
	}



};

void SubC3dWidget::read_entity_file(QString filename) {
	// 查找最后一个点号, QString->String
	string filename_str = filename.toStdString(); // 默认使用 UTF-8 编码
	size_t dotPos = filename_str.find_last_of(".");

	// 提取扩展名并转小写
	string ext = filename_str.substr(dotPos);
	transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

	if (ext == ".stp" || ext == ".step") {
		
		cout << filename_str << endl;
		cout << ext << endl;
		//QString 转 char* 或者Standard_CString	
		QByteArray ba = filename.toLocal8Bit();
		char *Cfilename = ba.data();
	
		// 创建STEP文件读取器对象
		STEPControl_Reader reader;
		reader.ReadFile(Cfilename);
		// Loads file MyFile.stp 
		// 读取指定路径的STEP文件（注意：实际使用中应检查返回值）
		
		Standard_Integer NbRoots = reader.NbRootsForTransfer();
		// gets the number of transferable roots 
		// 获取文件中可转换的根实体数量
		//cout << "Number of roots in STEP file:" << NbRoots << endl;
		
		Standard_Integer NbTrans = reader.TransferRoots();
		// 获取并输出根实体数量
		// translates all transferable roots, and returns the number of    //successful translations 
		//cout << "STEP roots transferred:"<< NbTrans << endl;
		//cout << "Number of resulting shapes is:" << reader.NbShapes() << endl;

		// 获取合并后的单一形状（所有转换结果的集合）
		// obtain the results of translation in one OCCT shape 
		TopoDS_Shape result = reader.OneShape();
	
		Handle(AIS_Shape) ais_read = new AIS_Shape(result);
		m_context->Display(ais_read, Standard_True);
		m_view->FitAll();
		ais_queue.push(ais_read);

	}
	else if (ext == ".iges" || ext == ".igs") {
		cout << filename_str << endl;
		cout << ext << endl;
		//QString 转 char* 或者Standard_CString	
		QByteArray ba = filename.toLocal8Bit();
		char *Cfilename = ba.data();

		// 创建STEP文件读取器对象
		IGESControl_Reader reader;
		reader.ReadFile(Cfilename);
		// Loads file MyFile.stp 
		// 读取指定路径的STEP文件（注意：实际使用中应检查返回值）

		Standard_Integer NbRoots = reader.NbRootsForTransfer();
		// gets the number of transferable roots 
		// 获取文件中可转换的根实体数量
		//cout << "Number of roots in STEP file:" << NbRoots << endl;

		Standard_Integer NbTrans = reader.TransferRoots();
		// 获取并输出根实体数量
		// translates all transferable roots, and returns the number of    //successful translations 
		//cout << "STEP roots transferred:"<< NbTrans << endl;
		//cout << "Number of resulting shapes is:" << reader.NbShapes() << endl;

		// 获取合并后的单一形状（所有转换结果的集合）
		// obtain the results of translation in one OCCT shape 
		TopoDS_Shape result = reader.OneShape();

		Handle(AIS_Shape) ais_read = new AIS_Shape(result);
		m_context->Display(ais_read, Standard_True);
		m_view->FitAll();
		ais_queue.push(ais_read);
	}
}

//bool SubC3dWidget::btnconnect() {

#if 1
	/*connect*/
	//connect(mw->btn_cube, &QAction::triggered, this, &SubC3dWidget::show_csg_create_cube);
	/*std::cout << 1 << std::endl;
	bool ret = QWidget::connect(btn_cube, &QAction::triggered, this, &SubC3dWidget::show_csg_create_cube);
	if (ret) {
		std::cout << "successful" << std::endl;
	}
	else
	{
		std::cout << "failed" << std::endl;
	}
	return ret;*/

#endif 




