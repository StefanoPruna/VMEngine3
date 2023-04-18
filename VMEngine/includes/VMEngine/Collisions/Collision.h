#pragma once
#include "VMEngine/CoreMinimal.h"
#include "VMEngine/Math/Transformations.h"

class Collision
{
public:
	Collision(Vector3 Location, Vector3 Offset);
	~Collision();

	//Detect if two collisions are overlapping
	virtual bool IsOverlapping(Collision& OtherCol) { return false; }

	//Get the center of the collision
	virtual Vector3 FindCenter() { return Vector3(0.0f); }

	//draw the collision for debugging
	//Vector 3 to use R G B colours
	virtual void DebugDraw(Vector3 Colour) {}

	//Transform functions
	//Set the location of the collision
	virtual void SetLocation(Vector3 NewLocation) { Transform.Location = NewLocation; }

	//Update the Offset
	virtual void SetOffset(Vector3 NewOffset) { Offset = NewOffset; }

	//Set the rotation of the collision
	virtual void SetRotation(Vector3 NewRotation) { Transform.Rotation = NewRotation; }

	//Set the rotations x, y and z of the collisions
	virtual void SetRotationX(float Value) { Transform.Rotation.x = Value; }
	virtual void SetRotationY(float Value) { Transform.Rotation.y = Value; }
	virtual void SetRotationZ(float Value) { Transform.Rotation.z = Value; }
protected:
	//Transforms for the collision in world space
	CTransform Transform;

	//Offset for the center location
	Vector3 Offset;

	//Visual mesh for debugging
	MeshPtr DebugMesh;
	ShaderPtr DebugShader;
	MaterialPtr DebugMaterial;
};

class BoxCollision :
	public Collision
{
public:
	BoxCollision(Vector3 Location, Vector3 Offset, Vector3 Dimensions);

	//override needed to override the function
	bool IsOverlapping(Collision& OtherCol) override;
	Vector3 FindCenter() override;
	//draw a mesh to the dimension of the box
	//turn the mesh into a wireframe view to not obscure the actual object
	//create the mesh and a shader only if we need to debug the collision
	void DebugDraw(Vector3 Colour) override;
	void SetLocation(Vector3 NewLocation) override;

	//return the size of the box
	Vector3 GetDimensions() const { return Dimensions; }

	//Set the dimensions of the box
	void SetDimensions(Vector3 NewDimensions);
protected:
	//Bounding box values
	Vector3 Dimensions;
	//Bounding vectors between the minimum and maximum size of the collision
	Vector3 Min;
	Vector3 Max;
};