#pragma once
#include "VMEngine/Math/Transformations.h"
#include "VMEngine/CoreMinimal.h"

struct STCameraData
{
	//how fast the camera can move
	float Speed = 5.0f;

	//it looks like a camera zoom, but it's just getting closer/cliper to the objects
	//in degrees
	float FOV = 80.0f;

	//how close models can get to the camera before disappearing
	float NearClip = 0.01f;
	//how far models can get to the camera before disappearing
	float FarClip = 1000.0f;
};

class Camera
{
public:
	Camera();

	//Move camera in 3D space to a location
	void Translate(Vector3 Location);

	//return the transform data
	CTransform GetTransforms() const { return Transform; }

	//return the current facing directions
	CDirection GetDirections() const { return Directions; }

	//return the extra camera info
	//speed, fov, near and far clips
	STCameraData GetCameraData() const { return CameraData; }

	//return a view matrix that considers pos and rot
	glm::mat4 GetViewMatrix() const;

	void RotatePitch(float Amount);

	void RotateYaw(float Amount);
private:
	//Transforms of the camera
	//Location, Rotation and Scale (but we don't need Scale)
	CTransform Transform;

	//Forward, Right and Up directions
	CDirection Directions;

	//hold all the extra camera info
	STCameraData CameraData;

	//find the current direction vectors based on the rotation of the YAW and PITCH of the camera
	void UpdateDirectionVectors();
};