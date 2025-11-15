#include "../inc/OCCModeling.h"
#include "../inc/SubC3dWidget.h"
#if 0
TopoDS_Shape makebottle() {
//;定义支持点;
	Standard_Integer myheight = 70;
	Standard_Integer mywidth = 50;
	Standard_Integer mythickness = 30;

	gp_Pnt apnt1(-mywidth / 2, 0, 0);
	gp_Pnt apnt2(-mywidth / 2, -mythickness / 4, 0);
	gp_Pnt apnt3(0, -mythickness / 2, 0);
	gp_Pnt apnt4(mywidth / 2, 0, 0);
	gp_Pnt apnt5(mywidth / 2, -mythickness / 4, 0);

//;定义几何图形;
	//计算部分几何轮廓
	Handle(Geom_TrimmedCurve) anArcOfCircle = GC_MakeArcOfCircle(apnt2, apnt3, apnt5);//圆弧
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(apnt1, apnt2);
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(apnt5, apnt4);

//;定义拓扑结构;
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(anArcOfCircle);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment2);
	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2, anEdge3);

//完成轮廓
	gp_Ax1 xAxis = gp::OX();    // 获得X轴
	gp_Trsf aTrsf;// 创建一个变换对象
	aTrsf.SetMirror(xAxis); // 设置变换为关于x轴的变换
	BRepBuilderAPI_Transform aBRepTrsf(aWire, aTrsf); //  使用BRepBuilderAPI_Transform类来应用变换到原始线框上
	TopoDS_Shape aMirroredShape = aBRepTrsf.Shape(); // 从变换结果中获取新的形状，即镜像后的线框
	TopoDS_Wire aMirroredWire = TopoDS::Wire(aMirroredShape);// 将形状转换为线框类型
	BRepBuilderAPI_MakeWire mkWire;// 创建一个新的线框构建器对象，用于合并线框
	mkWire.Add(aWire);// 将原始线框添加到新的线框构建器中
	mkWire.Add(aMirroredWire);// 将镜像后的线框也添加到新的线框构建器中
	TopoDS_Wire myWireProfile = mkWire.Wire();

//;拉伸轮廓;
	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(myWireProfile);//由线框生成平面
	gp_Vec aPrismVec(0, 0, myheight);//gp_vec是一个矢量类型，声明一个三维矢量用以创建棱柱(prism)
	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);//由平面和矢量方向生成棱柱

//倒角

	 //创建了一个BRepFilletAPI_MakeFillet对象mkFillet，用于生成圆角。它初始化时接收一个几何体myBody作为参数，这个几何体将被用来添加圆角。
	BRepFilletAPI_MakeFillet mkFillet(myBody); 
	
	TopExp_Explorer anEdgeExplorer(myBody, TopAbs_EDGE);// 创建一个遍历器，用于遍历myBody中的所有边。TopAbs_EDGE指定了我们感兴趣的是边（Edge）。
	// 获取当前遍历到的边，并转换为TopoDS_Edge类型
	while (anEdgeExplorer.More()) {
		
		TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());// 获取当前遍历到的边，并转换为TopoDS_Edge类型。
		
		mkFillet.Add(mythickness / 12., anEdge);//Add edge to fillet algorithm

		anEdgeExplorer.Next();// 移动到下一个边，以便在下一次循环中处理。
	}
	myBody = mkFillet.Shape();


// 瓶身：添加瓶颈
	gp_Pnt neckLocation(0, 0, myheight);//瓶颈位置
	gp_Dir neckAxis = gp::DZ();//点处向量
	gp_Ax2 neckAx2(neckLocation, neckAxis);//创建轴系
	Standard_Real myNeckRadius = mythickness / 4.;//半径
	Standard_Real myNeckHeight = myheight / 10.;//高度
	BRepPrimAPI_MakeCylinder MKCylinder(neckAx2, myNeckRadius, myNeckHeight);//创建圆柱线框模型
	TopoDS_Shape myNeck = MKCylinder.Shape();//获取圆柱的形状，拓扑模型
	myBody = BRepAlgoAPI_Fuse(myBody, myNeck);//// 使用布尔融合操作将瓶颈添加到瓶身主体上。

	#if 0

//构建中空的瓶体
	TopoDS_Face   faceToRemove; //用于存储需要移除的面
	Standard_Real zMax = -1; //用于记录遍历过程中找到的最高平面的Z坐标。
	for (TopExp_Explorer aFaceExplorer(myBody, TopAbs_FACE); aFaceExplorer.More(); aFaceExplorer.Next()) {   //(创建面的遍历器；条件表达式: .More()如果没有更多face返回0；移动到下个面)
		TopoDS_Face aFace = TopoDS::Face(aFaceExplorer.Current()); //创建一个TopDS_Face对象，代表当前遍历到的面
		// Check if <aFace> is the top face of the bottle's neck
		Handle(Geom_Surface) aSurface = BRep_Tool::Surface(aFace);    // 检查当前面是否是瓶子颈部的顶面（假设这是一个平面）
		if (aSurface->DynamicType() == STANDARD_TYPE(Geom_Plane)) {   // 如果当前面是一个平面
			Handle(Geom_Plane) aPlane = Handle(Geom_Plane)::DownCast(aSurface);  // 将Geom_Surface句柄向下转型为Geom_Plane句柄
			gp_Pnt aPnt = aPlane->Location();  //获取平面的位置点
			Standard_Real aZ = aPnt.Z(); //获取位置点的z坐标
			if (aZ > zMax) {
				zMax = aZ; 

				faceToRemove = aFace; //如果当前平面的Z坐标大于zMax，则更新zMax为当前平面的Z坐标，并将当前平面设置为需要移除的面。
			}
		}
	}
	TopTools_ListOfShape facesToRemove;
	facesToRemove.Append(faceToRemove);
	BRepOffsetAPI_MakeThickSolid BodyMaker; //创建一个BRepOffsetAPI_MakeThickSolid对象BodyMaker，用于生成厚实体。

	//调用MakeThickSolidByJoin方法，根据myBody和需要移除的面列表facesToRemove生成一个新的厚实体。-myThickness / 50指定了偏移的厚度（负值表示向内偏移），1.e-3是公差。
	BodyMaker.MakeThickSolidByJoin(myBody, facesToRemove, -mythickness / 50, 1.e-3); //Microsoft C++ 异常: StdFail_NotDone，位于内存位置 0x000000BE3776D5E0 处。
	myBody = BodyMaker.Shape();

	#endif

	// 螺纹：
	//创建表面I
	Handle(Geom_CylindricalSurface) aCyl1 = new Geom_CylindricalSurface(neckAx2, myNeckRadius * 0.99);
	Handle(Geom_CylindricalSurface) aCyl2 = new Geom_CylindricalSurface(neckAx2, myNeckRadius * 1.05);
	//定义二维曲线
	gp_Pnt2d aPnt(2. * M_PI, myNeckHeight / 2.);
	gp_Dir2d aDir(2. * M_PI, myNeckHeight / 4.);
	gp_Ax2d anAx2d(aPnt, aDir);
	Standard_Real aMajor = 2. * M_PI;
	Standard_Real aMinor = myNeckHeight / 10;
	Handle(Geom2d_Ellipse) anEllipse1 = new Geom2d_Ellipse(anAx2d, aMajor, aMinor);
	Handle(Geom2d_Ellipse) anEllipse2 = new Geom2d_Ellipse(anAx2d, aMajor, aMinor / 4);
	Handle(Geom2d_TrimmedCurve) anArc1 = new Geom2d_TrimmedCurve(anEllipse1, 0, M_PI);
	Handle(Geom2d_TrimmedCurve) anArc2 = new Geom2d_TrimmedCurve(anEllipse2, 0, M_PI);
	gp_Pnt2d anEllipsePnt1 = anEllipse1->Value(0);
	gp_Pnt2d anEllipsePnt2 = anEllipse1->Value(M_PI);
	Handle(Geom2d_TrimmedCurve) aSegment = GCE2d_MakeSegment(anEllipsePnt1, anEllipsePnt2);
	//创建边和曲线
	TopoDS_Edge anEdge1OnSurf1 = BRepBuilderAPI_MakeEdge(anArc1, aCyl1);
	TopoDS_Edge anEdge2OnSurf1 = BRepBuilderAPI_MakeEdge(aSegment, aCyl1);
	TopoDS_Edge anEdge1OnSurf2 = BRepBuilderAPI_MakeEdge(anArc2, aCyl2);
	TopoDS_Edge anEdge2OnSurf2 = BRepBuilderAPI_MakeEdge(aSegment, aCyl2);
	TopoDS_Wire threadingWire1 = BRepBuilderAPI_MakeWire(anEdge1OnSurf1, anEdge2OnSurf1);
	TopoDS_Wire threadingWire2 = BRepBuilderAPI_MakeWire(anEdge1OnSurf2, anEdge2OnSurf2);
	BRepLib::BuildCurves3d(threadingWire1);
	BRepLib::BuildCurves3d(threadingWire2);
	// 构建螺纹
	BRepOffsetAPI_ThruSections aTool(Standard_True);
	aTool.AddWire(threadingWire1);
	aTool.AddWire(threadingWire2);
	aTool.CheckCompatibility(Standard_False);
	TopoDS_Shape myThreading = aTool.Shape();

//整合模型
	
	TopoDS_Compound aRes;
	BRep_Builder aBuilder;
	aBuilder.MakeCompound(aRes);
	aBuilder.Add(aRes, myBody);
	aBuilder.Add(aRes, myThreading);
	return aRes;

}
#endif
#if 0
TopoDS_Shape csg_create_cube_test() {
	// 创建一个矩形平面
	gp_Pnt p1(0, 0, 0);
	gp_Pnt p2(100, 0, 0);
	gp_Pnt p3(100, 100, 0);
	gp_Pnt p4(0, 100, 0);

	BRepBuilderAPI_MakeWire wire;
	wire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
	wire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
	wire.Add(BRepBuilderAPI_MakeEdge(p3, p4));
	wire.Add(BRepBuilderAPI_MakeEdge(p4, p1));

	TopoDS_Wire wireShape = wire.Wire();
	TopoDS_Face face = BRepBuilderAPI_MakeFace(wireShape);


	// 拉伸平面
	gp_Vec vector(0, 0, 100); // 拉伸向量
	TopoDS_Shape prism = BRepPrimAPI_MakePrism(face, vector);

	return prism;

};
#endif

// CSG创建立方体
#if 1
TopoDS_Shape csg_create_cube(
	double p0_x, double p0_y, double p0_z,
	double L, double W, double H
	) {
	gp_Pnt p0(p0_x, p0_y, p0_z);
	TopoDS_Shape cube = BRepPrimAPI_MakeBox(p0, L, W, H);
	return cube;
};
#endif

//CSG创建圆柱体
TopoDS_Shape csg_create_cylinder(
	double p0x, double p0y, double p0z,
	double R, double H) {
	gp_Ax2 cylinder_Ax2(gp_Pnt(p0x, p0y, p0z), gp_Dir(0, 0, 1));
	TopoDS_Shape acylinder = BRepPrimAPI_MakeCylinder(cylinder_Ax2, R, H).Solid();
	return acylinder;
}

//CSG创建圆台体
TopoDS_Shape csg_create_cone(double p0x, double p0y, double p0z,
	double R1, double R2, double H) {

	gp_Ax2 cone_Ax2(gp_Pnt(p0x, p0y, p0z), gp_Dir(0, 0, 1));
	TopoDS_Shape acone = BRepPrimAPI_MakeCone(cone_Ax2, R2, R1, H).Solid();
	return acone;
}

//CSG创建球体
TopoDS_Shape csg_create_sphere(double p0x, double p0y, double p0z,
	double R){
	gp_Pnt pt(p0x, p0y, p0z);
	TopoDS_Shape asphere = BRepPrimAPI_MakeSphere(pt, R).Solid();
	return asphere;
}

//CSG布尔交集运算
TopoDS_Shape csg_boolean_opt_intersert(TopoDS_Shape shape1, TopoDS_Shape shape2) {

	BRepAlgoAPI_Common common_opt(shape1, shape2);
	if (!common_opt.IsDone()) {
		// 处理错误，例如打印错误信息
		qDebug() << "wrong";
	}
	return common_opt.Shape();
}

//CSG布尔并集运算
TopoDS_Shape csg_boolean_opt_and(TopoDS_Shape shape1, TopoDS_Shape shape2) {

	BRepAlgoAPI_Fuse fuse_opt(shape1, shape2);
	if (!fuse_opt.IsDone()) {
		// 处理错误，例如打印错误信息
		qDebug() << "wrong";
	}
	return fuse_opt.Shape();
}


//CSG布尔差集运算
TopoDS_Shape csg_boolean_opt_differ(TopoDS_Shape shape1, TopoDS_Shape shape2) {

	BRepAlgoAPI_Cut cut_opt(shape1, shape2);
	if (!cut_opt.IsDone()) {
		// 处理错误，例如打印错误信息
		qDebug() << "wrong";
	}
	return cut_opt.Shape();
}

//基于平面创建矩形线框草图
TopoDS_Wire stre_create_rect_onPln(TopoDS_Face plane, Standard_Real tran_distance_u, Standard_Real tran_distance_v, double length, double width) {
	// 获取面的几何曲面
	Handle(Geom_Surface) surface = BRep_Tool::Surface(plane);
	// 转换为 Geom_Plane 并提取 gp_Pln
	Handle(Geom_Plane) geomPlane = Handle(Geom_Plane)::DownCast(surface);
	gp_Pln pln = geomPlane->Pln();


	// 计算平面的边界框
	Bnd_Box bbox;
	BRepBndLib::Add(plane, bbox);

	// 获取边界框的角点
	gp_Pnt minPnt = bbox.CornerMin(), maxPnt = bbox.CornerMax();


	// 计算中心点
	gp_Pnt origin(
		(minPnt.X() + maxPnt.X()) / 2.0,
		(minPnt.Y() + maxPnt.Y()) / 2.0,
		(minPnt.Z() + maxPnt.Z()) / 2.0
	);
	//提取平面坐标系
	const gp_Ax3& planeCoordinateSystem = pln.Position();
	//获取法线方向（Z 轴方向）
	gp_Dir normal = planeCoordinateSystem.Direction();
	//基于选择平面的坐标系
	gp_Ax3 planeAx3(origin, normal);
	// 计算矩形顶点(translated即采用原点平移的方式得到矩形的四个顶点坐标)
	gp_Vec uDir = planeAx3.XDirection();
	gp_Vec vDir = planeAx3.YDirection();
	
	gp_Pnt p1 = origin.Translated((-0.5 * length + tran_distance_u)* uDir + (-0.5 * width + tran_distance_v) * vDir);
	gp_Pnt p2 = origin.Translated((-0.5 * length + tran_distance_u) * uDir + (0.5 * width + tran_distance_v) * vDir);
	gp_Pnt p3 = origin.Translated((0.5 * length + tran_distance_u) * uDir + (0.5 * width + tran_distance_v) * vDir);
	gp_Pnt p4 = origin.Translated((0.5 * length + tran_distance_u) * uDir + (-0.5 * width + tran_distance_v) * vDir);
	//创建矩形的各条边
	BRepBuilderAPI_MakeWire wire;
	wire.Add(BRepBuilderAPI_MakeEdge(p1, p2));
	wire.Add(BRepBuilderAPI_MakeEdge(p2, p3));
	wire.Add(BRepBuilderAPI_MakeEdge(p3, p4));
	wire.Add(BRepBuilderAPI_MakeEdge(p4, p1));

	TopoDS_Wire wireShape = wire.Wire();
	return wireShape;
}


//基于平面创建圆形线框草图
TopoDS_Wire stre_create_circle_onPln(TopoDS_Face plane, Standard_Real tran_distance_u, Standard_Real tran_distance_v, double R) {
	// 获取面的几何曲面
	Handle(Geom_Surface) surface = BRep_Tool::Surface(plane);
	// 转换为 Geom_Plane 并提取 gp_Pln
	Handle(Geom_Plane) geomPlane = Handle(Geom_Plane)::DownCast(surface);

	gp_Pln pln = geomPlane->Pln();


	// 计算平面的边界框
	Bnd_Box bbox;
	BRepBndLib::Add(plane, bbox);

	// 获取边界框的角点
	gp_Pnt minPnt = bbox.CornerMin(), maxPnt = bbox.CornerMax();


	// 计算中心点
	gp_Pnt origin(
		(minPnt.X() + maxPnt.X()) / 2.0,
		(minPnt.Y() + maxPnt.Y()) / 2.0,
		(minPnt.Z() + maxPnt.Z()) / 2.0
	);
	//提取平面坐标系
	const gp_Ax3& planeCoordinateSystem = pln.Position();
	//获取法线方向（Z 轴方向）
	gp_Dir normal = planeCoordinateSystem.Direction();
	//基于选择平面的坐标系
	gp_Ax3 planeAx3(origin, normal);
	// 计算矩形顶点(translated即采用原点平移的方式得到矩形的四个顶点坐标)
	gp_Vec uDir = planeAx3.XDirection();
	gp_Vec vDir = planeAx3.YDirection();

	gp_Circ circle(gp_Ax2(origin, normal), R);

	TopoDS_Edge edge = BRepBuilderAPI_MakeEdge(circle).Edge();
	TopoDS_Wire circleWire = BRepBuilderAPI_MakeWire(edge).Wire();
	return circleWire;
}


TopoDS_Wire stre_create_rect_3D(gp_Pnt p0, double L, double W) {
	// 创建一个XOY矩形平面
	gp_Pnt p1(p0.X() + L, p0.Y(), p0.Z());
	gp_Pnt p2(p0.X(), p0.Y() + W, p0.Z());
	gp_Pnt p3(p0.X()+ L, p0.Y() + W, p0.Z());

	BRepBuilderAPI_MakeWire wire;
	wire.Add(BRepBuilderAPI_MakeEdge(p0, p1));
	wire.Add(BRepBuilderAPI_MakeEdge(p0, p2));
	wire.Add(BRepBuilderAPI_MakeEdge(p1, p3));
	wire.Add(BRepBuilderAPI_MakeEdge(p3, p2));

	TopoDS_Wire wireShape = wire.Wire();
	return wireShape;

};

//拉伸操作
TopoDS_Shape Feature_stretching_opt(
	TopoDS_Wire wire, Standard_Real h, Standard_Integer flag)
 {
	//找法线(gp_Dir自动单位化)
	BRepBuilderAPI_FindPlane findPlane(wire);
	Handle(Geom_Plane) plane = findPlane.Plane();
	gp_Dir normol = plane->Axis().Direction();
	gp_Vec unitvec(normol);
	
	TopoDS_Face face = BRepBuilderAPI_MakeFace(wire);

	if (flag == 0) {
		// 拉伸平面
		gp_Vec check1 =  h * unitvec;
		TopoDS_Shape prism = BRepPrimAPI_MakePrism(face, h * unitvec);
		return prism;
	
	}
	else if (flag == 1) {
		// 拉伸平面
		gp_Vec check2 = -1 * h * unitvec;
		TopoDS_Shape prism = BRepPrimAPI_MakePrism(face, -1 * h * unitvec);
		return prism;
	}
	else if (flag == 2) {
		// 拉伸平面
		gp_Vec check3 = 0.5 * h * unitvec;
		gp_Vec check4 = -0.5 * h * unitvec;
		TopoDS_Shape prism1 = BRepPrimAPI_MakePrism(face, 0.5 * h * unitvec);
		TopoDS_Shape prism2 = BRepPrimAPI_MakePrism(face, -0.5 * h * unitvec);
		TopoDS_Shape prism_result = csg_boolean_opt_and(prism1, prism2);
		return prism_result;
	}
	

};

TopoDS_Shape Feature_rotate_opt(TopoDS_Wire wire, gp_Ax1 ax1, Standard_Real angle) {

	BRepBuilderAPI_MakeFace face(wire);
	BRepPrimAPI_MakeRevol EntityRevol(face, ax1, angle * ( M_PI / 180 ));

	return EntityRevol.Shape();
}


TopoDS_Shape Feature_pillage_opt(TopoDS_Wire wire, TopoDS_Wire path) {
	//初始化扫掠工具对象，传入扫掠路径
	BRepOffsetAPI_MakePipeShell Sweep(path);
	//添加扫掠截面（wire）
	Sweep.Add(wire, Standard_False, Standard_False);
	//设置扫掠模式
	Sweep.SetMode(Standard_True);
	//设置过渡模式（截面间的连接方式）
	Sweep.SetTransitionMode(BRepBuilderAPI_RoundCorner);
	//执行扫掠计算
	Sweep.Build();
	TopoDS_Shape pipe = Sweep.Shape();
	return pipe;
}

TopoDS_Shape Feature_MakeFillet_opt(TopoDS_Shape Shape_NeedFillet, TopoDS_Edge edge_NeedFillet, Standard_Real radius) {
	//创建一个倒圆角操作对象，传入需要进行倒圆角的形状
	BRepFilletAPI_MakeFillet aMFillet(Shape_NeedFillet);
	//添加需要圆角的边和半径
	aMFillet.Add(radius, edge_NeedFillet);
	try {
		//防止所选边所在的直角面的宽度不满足圆角的半径条件
		aMFillet.Build();
		return aMFillet.Shape();
	}
	catch (Standard_Failure) {
		return Shape_NeedFillet;
	}
}

TopoDS_Shape Feature_MakeChamfer_opt
(TopoDS_Shape Shape_NeedFillet, TopoDS_Edge edge_NeedFillet, TopoDS_Face dis1_face, Standard_Real dis1, Standard_Real dis2) {
	//创建一个倒圆角操作对象，传入需要进行倒圆角的形状
	BRepFilletAPI_MakeChamfer aMChamfer(Shape_NeedFillet);
	//添加需要圆角的边和半径
	aMChamfer.Add(dis1, dis2, edge_NeedFillet, dis1_face);
	try {
		//防止所选边所在的直角面的宽度不满足圆角的半径条件
		aMChamfer.Build();
		return aMChamfer.Shape();
	}
	catch (Standard_Failure) {
		return Shape_NeedFillet;
	}
}

//镜像实体
TopoDS_Shape Feature_mirror_opt(TopoDS_Shape Shape_NeedMirror, gp_Ax2 mirror_plane) {
	// 创建一个几何变换对象
	gp_Trsf bTrsf;
	// 设置该变换为关于 plane 平面的镜像变换
	// 这将创建一个相对于指定平面的对称变换
	bTrsf.SetMirror(mirror_plane);
	// 创建形状变换操作对象
	// 参数说明：
	// Shape_NeedMirror - 要变换的原始形状
	// bTrsf - 要应用的几何变换
	// true - 表示要复制原始形状而非直接修改
	BRepBuilderAPI_Transform bBrepTrsf(Shape_NeedMirror, bTrsf, true);
	// 执行变换操作
	bBrepTrsf.Build();
	// 检查变换是否成功完成
	if (!bBrepTrsf.IsDone())
		return Shape_NeedMirror;  // 如果变换失败，直接返回
	return bBrepTrsf.Shape();
}

//平移实体
TopoDS_Shape Feature_transfer_opt(TopoDS_Shape Shape_NeedTransfer, gp_Vec translationVec) {

	// 创建一个变换对象
	gp_Trsf transform;
	// 设置变换为按translationVec进行平移
	transform.SetTranslation(translationVec);

	return BRepBuilderAPI_Transform(Shape_NeedTransfer, transform).Shape();

}

//圆周阵列实体
TopoDS_Shape Feature_CircleArray_opt(TopoDS_Shape Shape, gp_Ax1 ax1, Standard_Real num) {

	//创建Compound
	TopoDS_Compound Com;
	BRep_Builder builder;
	builder.MakeCompound(Com);
	for (int i=1;i<num;i++) {
		// 创建一个旋转变换对象
		gp_Trsf rotate;
		// 设置变换为绕Axis旋转给定角度
		rotate.SetRotation(ax1, i*2*M_PI/num);
		BRepBuilderAPI_Transform bRepRotate(Shape, rotate, true);
		builder.Add(Com, bRepRotate.Shape());
	}
	return Com;
}

//线性阵列实体
TopoDS_Shape Feature_LinearArray_opt(TopoDS_Shape Shape, Standard_Real num, Standard_Real dis, Standard_Integer direction_flag) {

	//创建Compound
	TopoDS_Compound Com;
	BRep_Builder builder;
	builder.MakeCompound(Com);
	for (int i = 1; i < num; i++) {
		if (direction_flag == 0) {
			// 创建一个变换对象
			gp_Trsf transform;
			gp_Vec translationVec(i*dis, 0, 0);
			// 设置变换为按translationVec进行平移
			transform.SetTranslation(translationVec);
			BRepBuilderAPI_Transform bRepTransform(Shape, transform);
			builder.Add(Com, bRepTransform.Shape());
		}
		else if (direction_flag == 1) {
			// 创建一个变换对象
			gp_Trsf transform;
			gp_Vec translationVec(0, i*dis, 0);
			// 设置变换为按translationVec进行平移
			transform.SetTranslation(translationVec);
			BRepBuilderAPI_Transform bRepTransform(Shape, transform);
			builder.Add(Com, bRepTransform.Shape());
		}
		else if (direction_flag == 2) {
			// 创建一个变换对象
			gp_Trsf transform;
			gp_Vec translationVec(0, 0, i*dis);
			// 设置变换为按translationVec进行平移
			transform.SetTranslation(translationVec);
			BRepBuilderAPI_Transform bRepTransform(Shape, transform);
			builder.Add(Com, bRepTransform.Shape());
		}

	}
	return Com;
}

//线线连接
TopoDS_Wire stre_CurveCurveConnect_opt(TopoDS_Edge curve1, TopoDS_Edge curve2) {

	BRepBuilderAPI_MakeWire wireMaker;
	wireMaker.Add(curve1);
	wireMaker.Add(curve2);
	TopoDS_Wire connectedWire = wireMaker.Wire();
	return connectedWire;
}



