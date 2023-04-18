#pragma once
#include "VMEngine/CoreMinimal.h"
#include "VMEngine/Math/Transformations.h"

//ai = animation importer
struct aiNode;
struct aiScene;
struct aiMesh;

class Model
{
public:
	Model();
	~Model();

	//create a simple shape based on the engine shapes
	bool CreateSimpleMesh(GeometricShapes Shape, ShaderPtr ModelShader);

	//import a 3D model from a common file type using ASSIMP
	bool ImportMeshFromFile(const char* ImportFilePath, ShaderPtr ModelShader);

	//draw models to the screen
	void Draw();

	//change the material relevant to the slot index
	//this will error log if the slot doesn't exist
	void SetMaterialBySlot(vmuint SlotIndex, MaterialPtr NewMaterial);

	//get a material in the material stack if it exists
	MaterialPtr GetMaterialBySlot(vmuint SlotIndex) const;

	//get the directory the model as imported from
	const char* GetFilePath() const { return ModelFilePath; }

	//position, rotation and scale of all the meshes in the model
	//it's a struct
	CTransform Transform;

	//return the collision for this model
	CollisionPtr GetCollision() const { return ModelCollision; }

	//add a collision to the model
	CollisionPtr AddCollisionToModel(Vector3 Dimensions, Vector3 Offset = Vector3(0.0f));
private:
	//find all of the meshes in an import file/scene
	void FindAndImportSceneMeshes(aiNode* Node, const aiScene* Scene);

	//convert a mesh from the importer to our engine mesh class
	MeshPtr ConvertImportMeshToEngineMesh(aiMesh* ImportMesh, const aiScene* Scene);

	//all the meshes related to this model
	MeshPtrStack MeshStack;

	//all the materials relevent to the meshes in this model
	MaterialPtrStack MaterialStack;

	//model shader
	ShaderPtr ModelShader;

	//imported file path
	const char* ModelFilePath;

	CollisionPtr ModelCollision;
};