#include "Ray.h"

void Ray::PickRayInit(float mouseX, float mouseY, Camera& camera)
{
	//������(0,0)����(width,height)������ϵת��������(-1,1)������(1,-1)������ϵ��
	direction.x = (2 * mouseX) / WIDTH - 1.0;
	direction.y = 1.0 - (2 * mouseY) / HEIGHT;
	direction.z = 1.0;

	//������ת������������֮��
	vec4 tempRay = vec4(direction, 1.0);		//vec4Ϊ�������������λ
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
	//����һ��������ķ�����
	obj.GetMeshData().mesh.request_face_normals();

	//��ȷ���Ͱ�Χ���ཻ֮��Ҫ�ѹ���ת��������ľֲ����꣬��Ϊmesh��data�Ǿֲ���
	vec3 localDir, localPos;							//��Rayת������ǰ����ľֲ�����ϵ��
	vec4 temp4;
	temp4 = inverse(obj.GetShaderData().world) * vec4(camPos, 1.0);
	if (temp4.w != 0)
		temp4 /= temp4.w;
	localPos = vec3(temp4.x, temp4.y, temp4.z);

	temp4 = inverse(obj.GetShaderData().world) * vec4(direction, 1.0);
	if (temp4.w != 0)
		temp4 /= temp4.w;
	localDir = normalize(vec3(temp4.x, temp4.y, temp4.z) - localPos);

	double ss = FAR_AWAY;		//�����ҳ��뵱ǰ�����ཻ�ĵ�һ�����ǣ��������壬һ�����߿���������ͷ���������ཻ
//����ÿһ�������Σ��ù��߼���Ƿ���ײ
	for (Mesh::FaceIter f_it = obj.GetMeshData().mesh.faces_begin(); f_it != obj.GetMeshData().mesh.faces_end(); f_it++)
	{
		float s, k;
		vec3 hiPoint;
		//�жϹ����Ƿ��������ε�����
		const float* nor = obj.GetMeshData().mesh.normal(*f_it).data();
		k = dot(localDir, vec3(nor[0], nor[1], nor[2]));
		if (k >= 0)
			continue;
		//�ж��Ƿ������������ڵ�ƽ���ཻ
		s = (obj.Triangles[i].planeC - dot(obj.Triangles[i].nor, localPos)) / k;
		if (s <= 0 || s > ss)			//����뵱ǰ����������ƽ���ཻ��������ǰ������ٽ�������ļ���
			continue;


		hiPoint = localPos + localDir * s;
		//�ж��ཻ���Ƿ����������ڲ�
		k = dot(obj.Triangles[i].nore1, hiPoint) - obj.Triangles[i].eC1;
		if (k < 0)
			continue;
		k = dot(obj.Triangles[i].nore2, hiPoint) - obj.Triangles[i].eC2;
		if (k < 0)
			continue;
		k = dot(obj.Triangles[i].nore3, hiPoint) - obj.Triangles[i].eC3;
		if (k < 0)
			continue;

		ss = s;			//����ss

		obj.hitTriangleIndex = i;	//��־��ǰ�ཻ�������ε�����

	}
	if (ss != FAR_AWAY)
		return ss;
	return 0.0;

}


