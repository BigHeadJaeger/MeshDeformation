#pragma once
#include<string>
#include<memory>
using namespace std;
#include"ShaderData.h"
#include"DataConvey.h"
#include"BoundingVolume.h"

//基类Object
class Object
{
protected:
	string name;							//object名称
	Transform transformation;				//和空间位置有关的transform组件
	ShaderData shaderData;					//和OpenGL相关的渲染组件
	MeshData meshData;
	shared_ptr<Bounding> bounding;
	//Bounding* bounding;

public:

	Object()
	{

	}

	Object(string _name)
	{
		name = _name;
	}

	//Object(const Object& obj)
	//{
	//	name = obj.name;
	//	transformation = obj.transformation;
	//	shaderData = obj.shaderData;
	//	meshData = obj.meshData;
	//	bounding=new Bounding()
	//}

	~Object()
	{
		//delete bounding;
		cout << bounding.use_count() << endl;
		bounding.reset();
		cout << bounding.use_count() << endl;
	}
	//Get
	string GetName() { return name; }
	Transform& GetTransform() { return transformation; }
	ShaderData& GetShaderData() { return shaderData; }
	MeshData& GetMeshData() { return meshData; }
	//Set
	void SetName(string _name) { name = _name; }
	//Init
	void InitVertexBuffer() { shaderData.InitVertexBuffer(meshData); }
	void InitBounding(BOUNDINGTYPE type);
	void InitAlbedo(string texPath) { shaderData.bAlbedo = true; shaderData.InitTexture(shaderData.tAlbedo, texPath); }
	void InitMetallic(string texPath) { shaderData.bMetallic = true; shaderData.InitTexture(shaderData.tMetallic, texPath); }
	void InitRoughness(string texPath) { shaderData.bRoughness = true; shaderData.InitTexture(shaderData.tRoughness, texPath); }
	void InitAo(string texPath) { shaderData.bAo = true; shaderData.InitTexture(shaderData.tAo, texPath); }
	void InitNormal(string texPath) { shaderData.bNormal = true; shaderData.InitTexture(shaderData.tNormal, texPath); }
	void InitShadowTex(string texPath) { shaderData.bShadowTex = true; shaderData.InitTexture(shaderData.tShadowTex, texPath); }
	//Update
	void UpdateMatrix(Camera& camera) { shaderData.UpdateMatrix(transformation, camera); }
	void UpdateBounding() { bounding->UpdatePos(this->transformation); }
	//Destroy
	void DestroyBounding() { bounding.reset(); }


	void Draw(ShaderProgram& p);
};