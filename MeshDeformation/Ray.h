#pragma once
#include<glm.hpp>
#include"NewObject.h"
#include"Camera.h"
using namespace glm;
class Ray
{
private:

public:
	vec3 direction;
	vec3 position;

	//int hitTriangleIndex;

	Ray()
	{
		direction = position = vec3(0);
		//hitTriangleIndex = -1;
	}

	Ray(vec3 _dir, vec3 _pos)
	{
		direction = _dir;
		position = _pos;
	}

	void PickRayInit(float mouseX, float mouseY, Camera& camera);							//��ʼ��3άʰȡ������
	//���Χ�����ײ��⣬�ò�������ຯ��ͳһ����
	bool BoundingHit(shared_ptr<Bounding> bounding);

	double RayHit(Object& obj, vec3 camPos);

	int Intersect(vector<Object>& Objs, vec3 camPos);		//�������ߵ�һ������������������
};
