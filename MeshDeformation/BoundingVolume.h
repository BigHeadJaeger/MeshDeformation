#pragma once
#include<glm.hpp>
using namespace glm;

#include"Const.h"
#include"Transform.h"
#include"PublicStruct.h"


//基类
class Bounding
{
protected:
	
public:
	virtual void Init(MeshData& meshData) = 0;		//初始化
	virtual void UpdatePos(Transform& trans) = 0;			//随着当前object进行缩放平移旋转
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

	void UpdatePos(Transform& trans) override;
	void Init(MeshData& meshData) override;

};

//class BoundingSphere:public Bounding
//{
//
//};