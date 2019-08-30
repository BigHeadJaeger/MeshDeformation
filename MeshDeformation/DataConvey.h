//用来shader数据传递的单例工具类
#pragma once
#include<GL/glew.h>
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include<string>
using namespace std;
using namespace glm;

#include"Program.h"
class ConveyTool
{
private:
	ConveyTool(){}
	static ConveyTool* conveyTool;
public:
	static ConveyTool* GetConveyTool()
	{
		if (conveyTool == NULL)
			conveyTool = new ConveyTool();
		return conveyTool;
	}

	//传texture到shader中
	void SetTexture(GLuint& texId, int num, GLenum texNum, string samplerName, ShaderProgram& p);
	//根据不同类型的值用重载的方式传入shader中
	void SetUniform(string valueName, mat4x4& value, ShaderProgram& p);
	void SetUniform(string valueName, vec4& value, ShaderProgram& p);
	void SetUniform(string valueName, vec3& value, ShaderProgram& p);
	void SetUniform(string valueName, float value, ShaderProgram& p);
};
