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

protected:
	////传texture到shader中
	//void SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, ShaderProgram& p);
	////根据不同类型的值用重载的方式传入shader中
	//void SetUniform(string valueName, mat4x4& value, ShaderProgram& p);
	//void SetUniform(string valueName, vec4& value, ShaderProgram& p);
	//void SetUniform(string valueName, vec3& value, ShaderProgram& p);
	//void SetUniform(string valueName, float value, ShaderProgram& p);
public:

	Object()
	{

	}

	string getName() { return name; }
	Transform& getTransform() { return transformation; }
	ShaderData& getShaderData() { return shaderData; }
	MeshData& getMeshData() { return meshData; }

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