#pragma once
#include<string>
using namespace std;
#include"ShaderData.h"
#include"Program.h"
#include"DataConvey.h"

#pragma once
//基类Object
class Object
{
protected:
	string name;							//object名称
	Transform transformation;				//和空间位置有关的transform组件
	ShaderData shaderData;					//和OpenGL相关的渲染组件
	MeshData meshData;

public:

	Object()
	{

	}

	Object(string _name)
	{
		name = _name;
	}

	string GetName() { return name; }
	Transform& GetTransform() { return transformation; }
	ShaderData& GetShaderData() { return shaderData; }
	MeshData& GetMeshData() { return meshData; }

	void SetName(string _name) { name = _name; }

	void UpdateMatrix(Camera& camera) { shaderData.UpdateMatrix(transformation, camera); }
	void InitVertexBuffer() { shaderData.InitVertexBuffer(meshData); }

	void InitAlbedo(string texPath) { shaderData.bAlbedo = true; shaderData.InitTexture(shaderData.tAlbedo, texPath); }
	void InitMetallic(string texPath) { shaderData.bMetallic = true; shaderData.InitTexture(shaderData.tMetallic, texPath); }
	void InitRoughness(string texPath) { shaderData.bRoughness = true; shaderData.InitTexture(shaderData.tRoughness, texPath); }
	void InitAo(string texPath) { shaderData.bAo = true; shaderData.InitTexture(shaderData.tAo, texPath); }
	void InitNormal(string texPath) { shaderData.bNormal = true; shaderData.InitTexture(shaderData.tNormal, texPath); }
	void InitShadowTex(string texPath) { shaderData.bShadowTex = true; shaderData.InitTexture(shaderData.tShadowTex, texPath); }

	void Draw(ShaderProgram& p);
};