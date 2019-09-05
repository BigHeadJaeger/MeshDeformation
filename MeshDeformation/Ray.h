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

	void PickRayInit(float mouseX, float mouseY, Camera& camera);				//将当前射线初始化成3维拾取的射线
	//与包围体的碰撞检测，用参数虚基类函数统一调用
	bool BoundingHit(shared_ptr<Bounding> bounding);

	double RayHit(Object& obj);

	string Intersect(map<string, Object>& objs);		//返回射线第一个触碰到的物体名字
};
