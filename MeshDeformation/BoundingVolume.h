#pragma once
#include<glm.hpp>
using namespace glm;

#include"NewObject.h"
#include"Const.h"

enum BOUNDINGTYPE
{
	BOX,
	SPHERE,

};

//����
class Bounding
{
protected:
	Object* attachObj;			//һ��ָ������object��ָ��
public:
	virtual void Init(Object* obj) = 0;		//��ʼ��
	virtual void UpdatePos() = 0;			//���ŵ�ǰobject��������ƽ����ת
};

class BoundingBox :public Bounding
{
protected:
	vec3 minPos;
	vec3 maxPos;


public:
	BoundingBox()
	{
		maxPos = vec3(float(-M_INFINITE), float(-M_INFINITE), float(-M_INFINITE));
		minPos = vec3(float(M_INFINITE), float(M_INFINITE), float(M_INFINITE));
	}

	void UpdatePos() override;
	void Init(Object* obj) override;

};

//class BoundingSphere:public Bounding
//{
//
//};