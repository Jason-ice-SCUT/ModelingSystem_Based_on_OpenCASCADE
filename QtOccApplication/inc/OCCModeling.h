#pragma once
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Compound.hxx>

#include <Geom_TrimmedCurve.hxx>
#include <Geom_Plane.hxx>

#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeSegment.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepLib.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_FindPlane.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepFilletAPI_MakeChamfer.hxx>

#include <Geom_CylindricalSurface.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom_Axis1Placement.hxx>
#include <Geom_Line.hxx>
#include <Geom_Circle.hxx>
#include <GeomConvert.hxx>
#include <GCE2d_MakeSegment.hxx>

#include <StdSelect_BRepOwner.hxx>
#include <STEPControl_Writer.hxx>
#include <STEPControl_Reader.hxx>
#include <IGESControl_Writer.hxx>
#include <IGESControl_Reader.hxx>
#include <StdSelect_FaceFilter.hxx>


#include <QDebug>

#define M_PI       3.14159265358979323846   // pi

//TopoDS_Shape makebottle();
TopoDS_Shape csg_create_cube_test();
TopoDS_Shape csg_create_cube(double p0_x, double p0_y, double p0_z,
	double L, double W, double H);
TopoDS_Shape csg_create_cylinder(double p0x, double p0y, double p0z,
	double R, double H);
TopoDS_Shape csg_create_cone(double p0x, double p0y, double p0z,
	double R1, double R2, double H);
TopoDS_Shape csg_create_sphere(double p0x, double p0y, double p0z,
	double R1);
TopoDS_Shape csg_boolean_opt_intersert(TopoDS_Shape shape1, TopoDS_Shape shape2);
TopoDS_Shape csg_boolean_opt_and(TopoDS_Shape shape1, TopoDS_Shape shape2);
TopoDS_Shape csg_boolean_opt_differ(TopoDS_Shape shape1, TopoDS_Shape shape2);
TopoDS_Wire stre_create_rect_onPln(TopoDS_Face plane, Standard_Real tran_distance_u, Standard_Real tran_distance_v, double length, double width);
TopoDS_Wire stre_create_rect_3D(gp_Pnt p0, double L, double W);
TopoDS_Wire stre_create_circle_onPln(TopoDS_Face plane, Standard_Real tran_distance_u, Standard_Real tran_distance_v, double R);
TopoDS_Shape Feature_stretching_opt(TopoDS_Wire wire, Standard_Real h, Standard_Integer flag);
TopoDS_Shape Feature_rotate_opt(TopoDS_Wire wire, gp_Ax1 ax1, Standard_Real angle);
TopoDS_Shape Feature_pillage_opt(TopoDS_Wire wire, TopoDS_Wire path);
TopoDS_Shape Feature_MakeFillet_opt(TopoDS_Shape Shape_NeedFillet, TopoDS_Edge edge_NeedFillet, Standard_Real radius);
TopoDS_Shape Feature_MakeChamfer_opt(TopoDS_Shape Shape_NeedFillet, TopoDS_Edge edge_NeedFillet, TopoDS_Face dis1_face, Standard_Real dis1, Standard_Real dis2);
TopoDS_Shape Feature_mirror_opt(TopoDS_Shape Shape_NeedMirror, gp_Ax2 plane);
TopoDS_Shape Feature_transfer_opt(TopoDS_Shape Shape_NeedTransfer, gp_Vec translationVec);
TopoDS_Shape Feature_CircleArray_opt(TopoDS_Shape Shape, gp_Ax1 ax1, Standard_Real num);
TopoDS_Shape Feature_LinearArray_opt(TopoDS_Shape Shape, Standard_Real num, Standard_Real dis, Standard_Integer direction_flag);
TopoDS_Wire stre_CurveCurveConnect_opt(TopoDS_Edge curve1, TopoDS_Edge curve2);
