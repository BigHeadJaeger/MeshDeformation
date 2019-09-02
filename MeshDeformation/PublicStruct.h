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

//����Ĳ�������
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
	Mesh mesh;			//��������
	bool providedTex;	//��¼�ļ��Ƿ�����������
};