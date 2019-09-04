#include "Ray.h"

void Ray::PickRayInit(float mouseX, float mouseY, Camera& camera)
{
	//将左上(0,0)右下(width,height)的坐标系转换到左上(-1,1)，右下(1,-1)的坐标系中
	direction.x = (2 * mouseX) / WIDTH - 1.0;
	direction.y = 1.0 - (2 * mouseY) / HEIGHT;
	direction.z = 1.0;

	//将射线转换到世界坐标之下
	vec4 tempRay = vec4(direction, 1.0);		//vec4为了增加齐次坐标位
	tempRay = inverse(camera.view) * inverse(camera.pro) * tempRay;
	if (tempRay.w != 0)
		tempRay /= tempRay.w;
	direction = vec3(tempRay.x, tempRay.y, tempRay.z);

	position = camera.eyePos;
}

bool Ray::BoundingHit(shared_ptr<Bounding> bounding)
{
	return bounding->RayDetect(direction, position);
}

double Ray::RayHit(Object& obj, vec3 camPos)
{


	if (!BoundingHit(obj.GetBounding()))
		return 0.0;
	//更新一下三角面的法向量
	obj.GetMeshData().mesh.request_face_normals();

	//当确定和包围体相交之后要把光线转换到物体的局部坐标，因为mesh的data是局部的
	vec3 localDir, localPos;							//将Ray转化到当前物体的局部坐标系中
	vec4 temp4;
	temp4 = inverse(obj.GetShaderData().world) * vec4(camPos, 1.0);
	if (temp4.w != 0)
		temp4 /= temp4.w;
	localPos = vec3(temp4.x, temp4.y, temp4.z);

	temp4 = inverse(obj.GetShaderData().world) * vec4(direction, 1.0);
	if (temp4.w != 0)
		temp4 /= temp4.w;
	localDir = normalize(vec3(temp4.x, temp4.y, temp4.z) - localPos);

	double ss = FAR_AWAY;		//用来找出与当前光线相交的第一个三角，比如球体，一条光线可能与正面和反面的三角相交
	//遍历每一个三角形，用光线检测是否碰撞
	obj.GetMeshData().mesh.request_face_normals();
	for (Mesh::FaceIter f_it = obj.GetMeshData().mesh.faces_begin(); f_it != obj.GetMeshData().mesh.faces_end(); f_it++)
	{
		vec3 nor;					//三角面的法向量
		double planeC;					//平面常数
		vec3 e1, e2, e3;			//三条边向量
		vec3 nore1, nore2, nore3;	//三条边的法向量
		double eC1, eC2, eC3;			//三条边的边常数
		vector<vec3> points;	//当前三角形的三个顶点
		for (Mesh::FaceVertexIter fv_it = obj.GetMeshData().mesh.fv_begin(*f_it); fv_it.is_valid();fv_it++)
		{
			float* temp = obj.GetMeshData().mesh.point(*fv_it).data();
			points.push_back(vec3(temp[0], temp[1], temp[2]));
		}

		e1 = points[1] - points[0];
		e2 = points[2] - points[1];
		e3 = points[1] - points[3];

		nor = normalize(vec3(obj.GetMeshData().mesh.normal(*f_it).data()[0], obj.GetMeshData().mesh.normal(*f_it).data()[1], obj.GetMeshData().mesh.normal(*f_it).data()[2]));

		planeC = dot(nor, points[0]);

		nore1 = normalize(cross(nor, e1));
		eC1 = dot(nore1, points[0]);
		nore2 = normalize(cross(nor, e2));
		eC2 = dot(nore2, points[1]);
		nore3 = normalize(cross(nor, e3));
		eC3 = dot(nore3, points[2]);

		float s, k;
		vec3 hiPoint;
		//判断光照是否在三角形的正面
		const float* nor = obj.GetMeshData().mesh.normal(*f_it).data();
		k = dot(localDir, vec3(nor[0], nor[1], nor[2]));
		if (k >= 0)
			continue;
		//判断是否与三角形所在的平面相交
		s = (planeC - dot(nor, localPos)) / k;
		if (s <= 0 || s > ss)			//如果与当前三角形所在平面相交并不是最前面的则不再进行下面的计算
			continue;


		hiPoint = localPos + localDir * s;
		//判断相交点是否在三角形内部
		k = dot(nore1, hiPoint) - eC1;
		if (k < 0)
			continue;
		k = dot(nore2, hiPoint) - eC2;
		if (k < 0)
			continue;
		k = dot(nore3, hiPoint) - eC3;
		if (k < 0)
			continue;

		ss = s;			//更新ss

		//obj.hitTriangleIndex = i;	//标志当前相交的三角形的索引
		//记录当前三角形的handle


	}
	if (ss != FAR_AWAY)
		return ss;
	return 0.0;

}


