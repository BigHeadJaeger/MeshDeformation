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

//基类
class Bounding
{
protected:
	Object* attachObj;			//一个指向依附object的指针
public:
	virtual void Init(Object* obj) = 0;		//初始化
	virtual void UpdatePos() = 0;			//随着当前object进行缩放平移旋转
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