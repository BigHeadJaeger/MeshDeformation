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
	for (Mesh::FaceIter f_it = obj.GetMeshData().mesh.faces_begin(); f_it != obj.GetMeshData().mesh.faces_end(); f_it++)
	{
		float s, k;
		vec3 hiPoint;
		//判断光照是否在三角形的正面
		const float* nor = obj.GetMeshData().mesh.normal(*f_it).data();
		k = dot(localDir, vec3(nor[0], nor[1], nor[2]));
		if (k >= 0)
			continue;
		//判断是否与三角形所在的平面相交
		s = (obj.Triangles[i].planeC - dot(obj.Triangles[i].nor, localPos)) / k;
		if (s <= 0 || s > ss)			//如果与当前三角形所在平面相交并不是最前面的则不再进行下面的计算
			continue;


		hiPoint = localPos + localDir * s;
		//判断相交点是否在三角形内部
		k = dot(obj.Triangles[i].nore1, hiPoint) - obj.Triangles[i].eC1;
		if (k < 0)
			continue;
		k = dot(obj.Triangles[i].nore2, hiPoint) - obj.Triangles[i].eC2;
		if (k < 0)
			continue;
		k = dot(obj.Triangles[i].nore3, hiPoint) - obj.Triangles[i].eC3;
		if (k < 0)
			continue;

		ss = s;			//更新ss

		obj.hitTriangleIndex = i;	//标志当前相交的三角形的索引

	}
	if (ss != FAR_AWAY)
		return ss;
	return 0.0;

}


