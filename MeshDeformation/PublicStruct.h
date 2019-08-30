#pragma once

#include<glm.hpp>
using namespace glm;

struct Point
{
	vec3 vertex;
	vec2 texcoord;
	vec3 normal;
};

struct AABB
{
	vec3 minPos;
	vec3 maxPos;
};

enum ObjIndexType
{
	Triangles,
	Quad
};

//物体的材质属性
struct ObjMaterial
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shiness;
};