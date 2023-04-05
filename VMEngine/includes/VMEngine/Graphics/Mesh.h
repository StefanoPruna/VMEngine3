#pragma once
#include "VMEngine/CoreMinimal.h"
#include "VMEngine/Math/Transformations.h"

struct Vertex;

class Mesh
{
	//Constructers and Deconstructers
public:
	Mesh();
	~Mesh();

	//create the mesh out of VAO, a shader and textures
	bool CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, vmuint MaterialSlot);

	//create a mesh VAO that has predefined model
	bool CreateMesh(vector<Vertex> Vertices, vector<vmuint> Indices, ShaderPtr MeshShader, vmuint MaterialSlot);
	
	//handle the drawing of all the required classes
	void Draw(MaterialPtr MeshMaterial);

	//return material slot assigned by the model to the mesh
	vmuint GetMaterialSlot() const { return MaterialSlot; }

	//this holds the pos, rot and scale of the mesh
	CTransform Transform;

private:
	//Store the shader this mesh requires
	ShaderPtr MeshShader;

	//assigned material slot relevant to the model class
	vmuint MaterialSlot;

	//Create a new VAO for the mesh
	VAOPtr MeshVAO;
};