#include "VMEngine/Graphics/Mesh.h"
#include "VMEngine/Graphics/ShaderProgram.h"
#include "VMEngine/Graphics/Material.h"
#include "VMEngine/Graphics/VertexArrayObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "VMEngine/Game.h"
#include "VMEngine/Graphics/GraphicsEngine.h"

Mesh::Mesh()
{
	cout << "Mesh | Initialised Mesh" << endl;

	//Transform.Location.x = 1.0f;
	//Transform.Scale = Vector3(0.5f);
	////Transform.Scale.y = Vector3(1.0f);
}

Mesh::~Mesh()
{
	MeshShader = nullptr;
	MeshVAO = nullptr;

	cout << "Mesh | Mesh Destroyed" << endl;
}

bool Mesh::CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, vmuint MaterialSlot)
{
	cout << "Mesh | Creating a Mesh" << endl;

	//create a VAO
	MeshVAO = make_shared<VAO>(Shape);

	//validate the mesh was created
	if (MeshVAO == nullptr)
	{
		cout << "Mesh | Mesh failed to be created" << endl;
		return false;
	}

	//without the pointer(this) it won't work
	this->MeshShader = MeshShader;
	this->MaterialSlot = MaterialSlot;

	cout << "Mesh | Created a Mesh successfully" << endl;

	return true;
}

bool Mesh::CreateMesh(vector<Vertex> Vertices, vector<vmuint> Indices, ShaderPtr MeshShader, vmuint MaterialSlot)
{
	cout << "Mesh | Creating a Imported Mesh" << endl;

	//create a VAO
	MeshVAO = make_shared<VAO>(Vertices, Indices);

	//validate the mesh was created
	if (MeshVAO == nullptr)
	{
		cout << "Mesh | Mesh failed to be created" << endl;
		return false;
	}

	//without the pointer(this) it won't work
	this->MeshShader = MeshShader;
	this->MaterialSlot = MaterialSlot;

	cout << "Mesh | Created a Mesh successfully" << endl;

	return true;
}

void Mesh::Draw(MaterialPtr MeshMaterial)
{
	MeshShader->RunShader();

	if (MeshMaterial != nullptr)
		MeshMaterial->Draw(MeshShader);

	//Initialise a static variable to check if any changes to transform
	static CTransform OldTransform;

	if (Transform != OldTransform)
	{
		OldTransform = Transform;

		glm::mat4 MatTransform = glm::mat4(1.0f);

		//Translate(move), then rotate, then scale
		MatTransform = glm::translate(MatTransform, Transform.Location);
		//rotate
		MatTransform = glm::rotate(MatTransform,glm::radians(Transform.Rotation.x), Vector3(1.0f, 0.0f, 0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.y), Vector3(0.0f, 1.0f, 0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.z), Vector3(0.0f, 0.0f, 1.0f));
		//scale
		MatTransform = glm::scale(MatTransform, Transform.Scale);

		//update the shader with the new transforms
		MeshShader->SetMat4("model", MatTransform);
	}		

	Game::GetGameInstance().GetGraphicsEngine()->ApplyScreenTransformations(MeshShader);

	//draw the VAO
	MeshVAO->Draw();
}
