#include "VMEngine/Graphics/Camera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "VMEngine/Game.h"

Camera::Camera()
{
	//x is the forward
	//Transform.Location = Vector3(-2.0f, 0.0f, 0.0f);
	//UpdateDirectionVectors();
	
	UpdateDirectionVectors();

	Transform.Location += -Directions.Forward * 2.0f;
}

void Camera::Translate(Vector3 Location)
{
	Transform.Location = Location;

	UpdateDirectionVectors();
}

void Camera::AddMovementInput(Vector3 Direction)
{
	//ignore the function if no directionis given
	if (glm::length(Direction) == 0)
		return;
	//divide the vector by it's length
	//don't normalise if the direction is 0
	Direction = glm::normalize(Direction);

	//set the velocity of the camera using the speed and input direction
	Vector3 Velocity = Direction * (CameraData.Speed * Game::GetGameInstance().GetFDeltaTime());

	//create a new location from the camera based on it's pos and the current vel
	Vector3 NewPosition = Transform.Location + Velocity;

	//make sure the camera has actually been told to move
	if (Transform.Location != NewPosition)
		//move camera to the new position
		Translate(NewPosition);
}

glm::mat4 Camera::GetViewMatrix() const
{
	//eye is th eview position of the camera
	//center is what the eye is looking at, thus we can simply plus the eyes position by the forward direction
	//as the forward direction is always normalised to a max of 1
	//the up direction is the location up
	return glm::lookAt(Transform.Location, Transform.Location + Directions.Forward, Directions.Up);
}

void Camera::RotatePitch(float Amount)
{
	Transform.Rotation.x += Amount * CameraData.LookSensitivity;

	if (Transform.Rotation.x > 89.0f)
		Transform.Rotation.x = 89.0f;

	if (Transform.Rotation.x < -89.0f)
		Transform.Rotation.x = -89.0f;

	UpdateDirectionVectors();
}

void Camera::RotateYaw(float Amount)
{
	Transform.Rotation.y += Amount * CameraData.LookSensitivity;
	//when the yaw gets to 360, it changes to 0
	Transform.Rotation.y = glm::mod(Transform.Rotation.y, 360.0f);

	UpdateDirectionVectors();
}

void Camera::UpdateDirectionVectors()
{
	//create a vector 3 top initialise a 0 direction
	Vector3 ForwardDirection;

	//cosine of the Yaw * cosine of the Pitch
	ForwardDirection.x = cos(glm::radians(Transform.Rotation.y)) *
		cos(glm::radians(Transform.Rotation.x));
	//sin of the pitch
	ForwardDirection.y = sin(glm::radians(Transform.Rotation.x));
	//sin of the Yaw and the cosine of the Pitch
	ForwardDirection.z = sin(glm::radians(Transform.Rotation.y)) *
		cos(glm::radians(Transform.Rotation.x));

	//normalise the direction to update the values to be between 0 and 1
	ForwardDirection = glm::normalize(ForwardDirection);

	//set the forward direction
	Directions.Forward = ForwardDirection;

	//cross product - will allow us to get our right and up vectors from the forward vector
	//cross product is the axis that is perpendicular to two other axis
	//set the right direction to always be perpendicular to the world up
	Directions.Right = glm::normalize(glm::cross(Directions.Forward, Vector3(0.0f, 1.0f, 0.0f)));
	//up direction is based on the local rotation of the forward and right directions
	Directions.Up = glm::normalize(glm::cross(Directions.Right, Directions.Forward));
}
