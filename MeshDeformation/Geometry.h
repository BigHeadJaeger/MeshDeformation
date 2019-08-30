#pragma once
#include"NewObject.h"

class GeometryObject :public Object
{
public:
	virtual void InitData() = 0;
};

class Box :public GeometryObject
{
public:
	void InitData(float width, float height, float depth);
};

class Sphere :public GeometryObject
{
public:
	void InitData(float radius, int slice, int stack);
};

class Grid :public GeometryObject
{
public:
	void InitData(float width, float height, int m, int n);
};