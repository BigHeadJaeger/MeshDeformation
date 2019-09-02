#pragma once
#include<OpenMesh/Core/IO/MeshIO.hh>
#include<OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include<glm.hpp>
using namespace glm;

struct Point
{
	vec3 vertex;
	vec2 texcoord;
	vec3 normal;
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

enum BOUNDINGTYPE
{
	BOX,
	SPHERE,

};

typedef OpenMesh::TriMesh_ArrayKernelT<> Mesh;

struct MeshData
{
	Mesh mesh;			//网格数据
	bool providedTex;	//记录文件是否含有纹理坐标
};