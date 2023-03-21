#pragma once
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int vmuint;

//class dependency to GraphicsEngine class
class GraphicsEngine;

//Shared pointers will delete by themselves after use
//typedef to assigned a name to anything
typedef shared_ptr<GraphicsEngine> GraphicsEnginePtr;

class VertexArrayObject;
typedef VertexArrayObject VAO;
typedef shared_ptr<VAO> VAOPtr;

class Texture;
typedef shared_ptr<Texture> TexturePtr;
typedef vector<TexturePtr> TexturePtrStack;

class ShaderProgram;
typedef shared_ptr<ShaderProgram> ShaderPtr;

class Mesh;
typedef shared_ptr<Mesh> MeshPtr;
typedef vector<MeshPtr> MeshPtrStack;

class Camera;
typedef shared_ptr<Camera> CameraPtr;

//For shape data and VAOs Matrices
typedef vector<float> PositionMatrix;
typedef vector<vmuint> IndicesMatrix;

struct ShapeData
{
	vector<float> PositionMatrix;
	vector<vmuint> IndecesMatrix;
};

//List of the geometric shapes available in the VAO
enum class GeometricShapes
{
	Triangle = 0,
	Polygon,
	Circle,
	Arrow,
	Cube
};

//store the paramater required to create a shader as a
struct VFShaderParams
{
	const wchar_t* VertexShaderPath;
	const wchar_t* FragmentShaderPath;
};

//types of shader that can be accepted in our shader program
enum class ShaderTypes
{
	Vertex = 0,
	Fragment
};