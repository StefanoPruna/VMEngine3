#pragma once
#include "VMEngine/CoreMinimal.h"

const PositionMatrix TrianglePositions
{
	// x	//y		//z		//colour			//Texture Coordinates
	-0.5f,	-0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,		//bottom left
	 0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,   1.0f, 0.0f,		//bottom right
	 0.0f,	 0.5f,	0.0f,   0.0f, 0.0f, 1.0f,	0.5f, 1.0f		//top
};

const IndicesMatrix TriangleIndices
{
	0, 1, 2
};

const PositionMatrix PolyPositions
{
	// x	//y		//z		//Colour			//Texture Coordinates
	-0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	  0.0f, 0.0f,		//bottom left - index 0
	 0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	  1.0f, 0.0f,		//bottom right - index 1
	 0.5f,	 0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	  1.0f, 1.0f,		//top right - index 2
	-0.5f,	 0.5f,  0.0f,   1.0f, 1.0f, 0.0f,	  0.0f, 1.0f		//top left - index 3
};

const IndicesMatrix PolyIndices
{
	0, 3, 1,	//Triangle 1
	3, 2, 1		//Triangle 2
};

const PositionMatrix CirclePositions
{
	// x	//y		//z     //colour		  //Texture Coordinates
	 0.0f,	 0.0f,	0.0f,	0.0f, 0.0f, 1.0f,  0.0f, 0.0f, //index 0
   -0.25f,	-0.5f,	0.0f,	1.0f, 0.0f, 0.0f,  0.0f, 0.0f, //index 1
	0.25f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,  0.0f, 0.0f, //index 2
	 0.5f, -0.25f,  0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f, //index 3
	 0.5f,  0.25f,  0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f, //index 4
	0.25f,   0.5f,  0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f, //index 5
   -0.25f,   0.5f,  0.0f,   0.0f, 0.0f, 1.0f,  0.0f, 0.0f, //index 6
    -0.5f,  0.25f,  0.0f,   1.0f, 0.0f, 0.0f,  0.0f, 0.0f, //index 7
	-0.5f, -0.25f,  0.0f,   0.0f, 1.0f, 0.0f,  0.0f, 0.0f //index 8
};

const IndicesMatrix CircleIndices
{
	0, 1, 2, 	//Triangle 1
	0, 2, 3,	//Triangle 2
	0, 3, 4,    //triangle 3
	0, 4, 5,    //Triangle 4
	0, 5, 6,	//Triangle 5
	0, 6, 7,	//Triangle 6
	0, 7, 8,	//Triangle 7
	0, 8, 1		//Triangle 8
};

const PositionMatrix ArrowPositions
{
	// x	//y		//z		//Colour            //Texture Coordinates
	-0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 0.0f, //bottom left - index 0
	 0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 0.0f, //bottom right - index 1
	 0.5f,	 0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 0.0f, //top right - index 2
	-0.5f,	 0.5f,  0.0f,   1.0f, 1.0f, 0.0f,	0.0f, 0.0f, //top left - index 3
	 0.0f,   1.0f,  0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, //top up - index 4
	 0.0f,	-1.0f,  0.0f,   0.0f, 1.0f, 0.0f,	0.0f, 0.0f, //bottom down - index 5
	 1.0f,	 0.0f,	0.0f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f //right - index 6
};

const IndicesMatrix ArrowIndices
{
	0, 3, 1,	//Triangle 1
	3, 2, 1,	//Triangle 2
	4, 5, 6		//Triangle 3
};

const PositionMatrix CubePositions{
	// x	// y	// z	// r	// g	// b	// tex coords
	-0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// back - bot - left	0
	 0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// back - bot - right	1
	 0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// back - top - right	2
	-0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// back - top - left	3
	-0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// front - top - left	4
	 0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// front - top - right	5
	 0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// front - bot - right	6
	-0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// front - bot - left	7
	-0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// left - top - right	8
	-0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// left - top - left	9
	-0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// left - bot - left	10
	-0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// left - bot - right	11
	 0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// right - top - right	12
	 0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// right - top - left	13
	 0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// right - bot - left	14
	 0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// right - bot - right	15
	-0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// top - bot - left		16
	 0.5f,	 0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// top - bot - right	17
	 0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// top - top - right	18
	-0.5f,	 0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// top - top - left		19
	-0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	1.0f,	// bot - top - left		20
	 0.5f,	-0.5f,	 0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	1.0f,	// bot - top - right	21
	 0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	1.0f,	0.0f,	// bot - bot - right	22
	-0.5f,	-0.5f,	-0.5f,	0.0f,	0.0f,	0.0f,	0.0f,	0.0f,	// bot - bot - left		23
};

const IndicesMatrix CubeIndicies{
	0,	1,	2,	// front tri 1
	2,	3,	0,	// front tri 2
	12, 13, 15,	// right tri 1
	15, 14, 13,	// right tri 2
	8,	9,	10,	// left tri 1
	10,	11,	8,	// left tri 2
	20,	21,	22,	// bot tri 1
	22,	23,	20,	// bot tri 2
	16,	17,	18,	// top tri 1
	18,	19,	16,	// top tri 2
	4,	5,	6,	// back tri 1
	6,	7,	4	// back tri 2
};

class VertexArrayObject
{
public:
	VertexArrayObject(GeometricShapes ChosenShape);
	~VertexArrayObject();

	void Draw();

private:
	ShapeData Shape;

	//This is unsigned int named vmuint from CoreMinimal.h
	// 
	//ID FOR THE VAO
	//VAB ID FOR THE VERTICES
	//EAB ID FOR THE INDICES
	vmuint ID, VAB, EAB;
};