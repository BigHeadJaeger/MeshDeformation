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
	vec3 localDir, localPos;							//将Ray转化到当前物体的局部坐标系中

	vec4 temp4;

	/*vec3 testPos = obj.Position;
	vec3 testScaler = obj.Scaler;
	vec3 testRoate = obj.Rotation;
	float testAngle = obj.RotateAngle;

	mat4 testWorld = translate(mat4(1.0), testPos);
	testWorld = rotate(testWorld, testAngle, testRoate);
	*/
	//temp4 = inverse(obj.World) * vec4(camPos, 1.0);
	//if (temp4.w != 0)
	//	temp4 /= temp4.w;
	////localPos = normalize(vec3(temp4.x, temp4.y, temp4.z));
	//localPos = vec3(temp4.x, temp4.y, temp4.z);

	//temp4 = inverse(obj.World) * vec4(dir, 1.0);
	//if (temp4.w != 0)
	//	temp4 /= temp4.w;
	//localDir = normalize(vec3(temp4.x, temp4.y, temp4.z) - localPos);

	if (!BoundingHit(obj.GetBounding()))
		return 0.0;

	double ss = FAR_AWAY;		//用来找出与当前光线相交的第一个三角，比如球体，一条光线可能与正面和反面的三角相交
//遍历每一个三角形，用光线检测是否碰撞
	for (int i = 0; i < obj.Triangles.size(); i++)
	{
		float s, k;
		vec3 hiPoint;
		//判断光照是否在三角形的正面
		k = dot(localDir, obj.Triangles[i].nor);
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


