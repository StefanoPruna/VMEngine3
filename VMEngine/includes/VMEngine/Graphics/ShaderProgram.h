#pragma once
#include "VMEngine/CoreMinimal.h"
#include "glm/glm.hpp"

class ShaderProgram
{
public:
	ShaderProgram();
	~ShaderProgram();

	//Initialise the shader as a vertex fragment shader
	bool InitVFShader(VFShaderParams ShaderFilePaths);

	//Run the shader program as the current shader to be interacted with in openGL
	void RunShader();

	vmuint GetID() const { return ProgramID; }

	//allow changing mat 4 variables in shader code
	void SetMat4(const char* ShaderVariable, glm::mat4 Value);
	//allow changing integer values in hsader code
	void SetInt(const char* ShaderVarName, int Value);

private:
	//Attach the shader to the VAO
	bool AttachShader(const wchar_t* ShaderFilePath, ShaderTypes Type);

	//Link the shader to OpenGL
	bool Link();

	//OpenGL will assign an ID to our Shader
	vmuint ProgramID;
	//array that will hold IDs to our unique shaders
	//0 = Vertex
	//1 = Fragment
	vmuint VFShaderIDs[2] = { 0 };
};