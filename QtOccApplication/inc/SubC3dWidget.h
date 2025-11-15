#pragma once


#include <Qtwidgets/Qwidget>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QApplication>
#include <QVBoxLayout>

#include <Standard.hxx> //����Open Inventor�ı�׼���һ���֣��ṩ��һЩ���������Ͷ��塢�����ʹ����쳣�Ļ����ࡣ
#include <Standard_Handle.hxx> //����Open Inventor�ı�׼���һ���֣��ṩ��һЩ���������Ͷ��塢�����ʹ����쳣�Ļ����ࡣ
#include <V3d_Viewer.hxx> //��������V3D Viewer�࣬����һ�����ڴ����͹��� <��ά��ͼ> �ĺ��������
#include <OpenGl_GraphicDriver.hxx>//����OpenGLͼ�������йأ��������ʹ��Ӳ�����ٻ���3Dͼ�Ρ�
#include <WNT_Window.hxx>//Windows NT�ض��Ĵ�������࣬�������Windows���������У����ͷ�ļ��ͺ���Ҫ��
#include <V3d_View.hxx>//��ά��ͼ�ľ���ʵ�֣�������ʾģ�ͺͽ�����
#include <AIS_InteractiveContext.hxx>//Advanced Interactive Scene���߼������������ӿڣ��ṩ�����û������Ļ��������� ������¼� �ȡ�
#include <BRepPrimAPI_MakeBox.hxx>//������һ�����ڴ��������弸����Ĺ����࣬MakeBox������������һ���򵥵ĳ����塣
#include <TopoDS_Shape.hxx>//����Topological Data Structure���������ݽṹ���⣬��ʾ������״�����ݽṹ��
#include <AIS_Shape.hxx>//������Ϊ�˽������ļ�����ת��Ϊ�����ڻ�����������ʹ�õ���״ʵ����
#include <AIS_Plane.hxx>//����ƽ��
#include <AIS_Axis.hxx>//������
#include <AIS_Manipulator.hxx>
#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <IntCurvesFace_ShapeIntersector.hxx>
#include <iostream>
#include <vector>
#include <queue>
#include "OCCModeling.h"
#include "CSG/CsgBooleanOpt.h"


using namespace std;

class SubC3dWidget : public QWidget{
	Q_OBJECT
public:
	explicit SubC3dWidget(QWidget* parent = Q_NULLPTR);
	virtual ~SubC3dWidget();

	//��ȡ��ά������������
	Handle(AIS_InteractiveContext) m_get_context() { return m_context; }

	//��ȡ��ά��ʾ����
	Handle(V3d_View)  m_get_view() { return m_view; }

	//��ʼ����������
	void m_initialize_context();

	//����ʽ�����Ĺ���һ�������鿴��(viewer)�е�ͼ����Ϊ�ͽ���ʽ�����ѡ��
	Handle(AIS_InteractiveContext) m_context;

	//����һ��ʵʱ�洢���������е�ģ�͵�����
	vector<Handle(AIS_InteractiveObject)> ais_models;


	/*csg��������������ض���*/
	TopoDS_Shape boolopt_model;//�������ڲ��������ģ��


	queue<Handle(AIS_Shape)> ais_queue;//�����������Ķ���

	//��ȡ�����������е����н�������
	NCollection_List<Handle(AIS_InteractiveObject)> GetGetAllInteractiveObjects(const Handle(AIS_InteractiveContext)& context);
	
	Standard_Integer selected_flag = 0; //ѡ��ģʽ�ı�־λ��0ѡ������ʵ�壨shape����1ѡ��ƽ�棨plane��

private:


	//����鿴�����Ͷ����ϵķ���
	Handle(V3d_Viewer) m_viewer;

	//����һ����ͼ
	Handle(V3d_View) m_view;

	//����3d�ӿڶ���ͼ����������
	Handle(Graphic3d_GraphicDriver) m_graphic_driver;

protected:
	//!��д��ͼ�¼�
	void paintEvent(QPaintEvent *);

	//!��д���ڳߴ�仯�¼�
	void resizeEvent(QResizeEvent *);

	//!��д��갴�������¼�
	void mousePressEvent(QMouseEvent *event);

	//!��д��갴���ͷ��¼�
	void mouseReleaseEvent(QMouseEvent *event);

	//!��д����ƶ��¼�
	void mouseMoveEvent(QMouseEvent *event);

	//!��д�������¼�
	void wheelEvent(QWheelEvent *event);

	//��������ʱ��������¼�
	void mouseMoveEvent_boolopt(QMouseEvent *event);

	//ʵ�������ͣʱ�Զ���Ⲣ����ƽ����
	void HighlightPlane(const TopoDS_Face& face);
	Handle(AIS_InteractiveObject) GetCurrentHighlight();
	void SetCurrentHighlight(Handle(AIS_Shape) aisface);

	//���ش��ڵĻ�������
	QPaintEngine *paintEngine() const override
	{
		return 0;
	}

	//��ά����ת��ģʽ
	enum CurrentAction3d
	{
		CurAction3d_Nothing,
		CurAction3d_DynamicPanning, //ƽ��
		CurAction3d_DynamicZooming, //����
		CurAction3d_DynamicRotation //��ת
	};

	//���ý���Ļ�׼��ͻ�׼ƽ��
	void Create_AIS_Datum();

private:
	Standard_Integer m_x_max;    //!��¼���ƽ������X
	Standard_Integer m_y_max;    //!��¼���ƽ������Y
	CurrentAction3d m_current_mode; //!��ά����ת��ģʽ

	TopExp_Explorer public_faceExpoler; //һ��������ʵ���������
	Handle(AIS_InteractiveObject) highlight[1]; //����ƽ�������
	TopoDS_Shape target_Shape; //Ŀ��ѡ�е�ʵ��
	TopoDS_Face target_Pln; //Ŀ��ѡ�е�ƽ��
	TopoDS_Wire target_Wire; //Ŀ��ѡ�е��߿�
	gp_Ax1 target_ax1; //Ŀ����ת��
	TopoDS_Edge target_Edge;//Ŀ��ѡ�еı�
	Handle(AIS_InteractiveObject) selected_entity; //��ʱ�洢ѡ��ʵ�����
	Handle(AIS_InteractiveObject) selected_face; //��ʱ�洢ѡ�������
	Handle(AIS_InteractiveObject) selected_wire; //��ʱ�洢ѡ���߿����
	Handle(AIS_InteractiveObject) selected_ax1; //��ʱ�洢ѡ�����߶���
	Handle(AIS_InteractiveObject) selected_edge; //��ʱ�洢ѡ��߶���
	
signals:
	void csg_boolopt_sendmodel(TopoDS_Shape boolopt_model);
	void csg_boolopt_text();

public Q_SLOTS:
	//ͨ�ù���
	void save_entity_step();
	void read_entity_file(QString filename);
	void deleteAll_modeling();
	void adaptView();


	//CSG
	void csg_show_create_cube(double px, double py, double pz, double l, double w, double h);
	void csg_show_create_cylinder(double px, double py, double pz, double r, double h);
	void csg_show_create_cone(double px, double py, double pz, double r1, double r2, double h);
	void csg_show_create_sphere(double px, double py, double pz, double r);
	void csg_boolopt_and(TopoDS_Shape model_1, TopoDS_Shape model_2);
	void csg_boolopt_differ(TopoDS_Shape model_1, TopoDS_Shape model_2);
	void csg_boolopt_intersert(TopoDS_Shape model_1, TopoDS_Shape model_2);

	//Feature
	void feature_stretching(double h, int flag);
	void feature_excision(double h, int flag);
	void feature_rotate(double angle);
	void feature_pillage();
	void receice_rotate_choice();
	void feature_makefillet(double r);
	void feature_mirror();
	void feature_transfer();
	void feature_makechamfer(double dis1, double dis2);
	void feature_circlearray(double num);

	void receice_entity_choice();
	void receice_edge_choice();
	void receice_face_choice();

	void stre_show_create_rect(double p0_u, double p0_v, double l, double w);
	void stre_show_create_3drect(gp_Pnt p0, double l, double w);
	void stre_show_create_circle(double p0_u, double p0_v, double R);
	
	void set_SelectionMode_toEntity();
	void set_SelectionMode_toFace();
	void set_SelectionMode_toWire();
	void set_SelectionMode_toEdge();

	
};

