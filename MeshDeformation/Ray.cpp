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
	obj.GetMeshData().mesh.request_face_normals();
	for (Mesh::FaceIter f_it = obj.GetMeshData().mesh.faces_begin(); f_it != obj.GetMeshData().mesh.faces_end(); f_it++)
	{
		vec3 nor;					//������ķ�����
		double planeC;					//ƽ�泣��
		vec3 e1, e2, e3;			//����������
		vec3 nore1, nore2, nore3;	//�����ߵķ�����
		double eC1, eC2, eC3;			//�����ߵı߳���
		vector<vec3> points;	//��ǰ�����ε���������
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
		//�жϹ����Ƿ��������ε�����
		const float* nor = obj.GetMeshData().mesh.normal(*f_it).data();
		k = dot(localDir, vec3(nor[0], nor[1], nor[2]));
		if (k >= 0)
			continue;
		//�ж��Ƿ������������ڵ�ƽ���ཻ
		s = (planeC - dot(nor, localPos)) / k;
		if (s <= 0 || s > ss)			//����뵱ǰ����������ƽ���ཻ��������ǰ������ٽ�������ļ���
			continue;


		hiPoint = localPos + localDir * s;
		//�ж��ཻ���Ƿ����������ڲ�
		k = dot(nore1, hiPoint) - eC1;
		if (k < 0)
			continue;
		k = dot(nore2, hiPoint) - eC2;
		if (k < 0)
			continue;
		k = dot(nore3, hiPoint) - eC3;
		if (k < 0)
			continue;

		ss = s;			//����ss

		//obj.hitTriangleIndex = i;	//��־��ǰ�ཻ�������ε�����
		//��¼��ǰ�����ε�handle


	}
	if (ss != FAR_AWAY)
		return ss;
	return 0.0;

}


