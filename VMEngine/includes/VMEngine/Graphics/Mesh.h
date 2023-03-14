#pragma once
#include "VMEngine/CoreMinimal.h"
#include "VMEngine/Math/Transformations.h"

class Mesh
{
	//Constructers and Deconstructers
public:
	Mesh();
	~Mesh();

	//create the mesh out of VAO, a shader and textures
	bool CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures);

	//handle the drawing of all the required classes
	void Draw();

	//this holds the pos, rot and scale of the mesh
	CTransform Transform;

private:
	//Store the shader this mesh requires
	ShaderPtr MeshShader;
	//store the textures this mesh requires
	TexturePtrStack MeshTextures;
	//Create a new VAO for the mesh
	VAOPtr MeshVAO;
};