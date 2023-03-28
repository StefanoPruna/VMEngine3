#include "VMEngine/Graphics/VertexArrayObject.h"
#include "GLEW/glew.h"

//Constructors - to define and initialise objects from the header
VertexArrayObject::VertexArrayObject(GeometricShapes ChosenShape)
{
	ID = EAB = VAB = 0;

	//Localised version of the chosen matrices
	PositionMatrix ChosenPositions = PositionMatrix();
	IndicesMatrix ChosenIndices = IndicesMatrix();

	switch (ChosenShape)
	{
	case GeometricShapes::Triangle :
		ChosenPositions = TrianglePositions;
		ChosenIndices = TriangleIndices;
		break;
	case GeometricShapes::Polygon :
		ChosenPositions = PolyPositions;
		ChosenIndices = PolyIndices;
		break;
	case GeometricShapes::Circle :
		ChosenPositions = CirclePositions;
		ChosenIndices = CircleIndices;
		break;
	case GeometricShapes::Arrow :
		ChosenPositions = ArrowPositions;
		ChosenIndices = ArrowIndices;
		break;
	case GeometricShapes::Cube :
		ChosenPositions = CubePositions;
		ChosenIndices = CubeIndicies;
		break;
	default :
		break;
	}

	/*Shape.PositionMatrix = TrianglePositions;
	Shape.IndecesMatrix = TriangleIndices;*/
	/*Shape.PositionMatrix = PolyPositions;

	Shape.IndecesMatrix = PolyIndices;*/

	/*Shape.IndecesMatrix = PolyIndices;

	Shape.PositionMatrix = CirclePositions;
	Shape.IndecesMatrix = CircleIndices;*/
	
	Shape.PositionMatrix = ChosenPositions;
	Shape.IndecesMatrix = ChosenIndices;

	// Handle the positions Matrix
	//Create the ID for the VAO
	glGenVertexArrays(1, &ID);

	//bind the data to this vertex array
	glBindVertexArray(ID);

	//Create an ID for the array buffer
	glGenBuffers(1, &VAB);
	//Bind the above IDs to the OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VAB);
	//Run through the data and attach the vertices to the VAB
	glBufferData(GL_ARRAY_BUFFER, 
		Shape.PositionMatrix.size() * sizeof(float), 
		&Shape.PositionMatrix[0],
		GL_STATIC_DRAW);

	//Handle the Indices
	//Create an ID for the element array buffer
	glGenBuffers(1, &EAB);
	//Bind the above ID to the OpenGl as the element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAB);
	//Run through the data and attach the inidices to the EAB
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		Shape.IndecesMatrix.size() * sizeof(vmuint),
		&Shape.IndecesMatrix[0],
		GL_STATIC_DRAW);

	//Assign the vertices and indices to the VAO
	glVertexAttribPointer(
		0,					//data set - 0 = the first data set in the array
		3,					//How many vertices/numbers in our matrix we need to make a triangle
		GL_FLOAT, GL_FALSE, //data type, whether we normalise the values
		sizeof(float) * 8,  //stride - the length it takes to get to each number
		(void*)0			//override to 0, the offset of how many number to skip in the matrix
	);

	// enable the vertex array
	glEnableVertexAttribArray(0);

	//Assign the colour to the shader
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT, GL_FALSE,
		sizeof(float) * 8,
		(void*)(3 * sizeof(float)) //skips the first 3 numbers from the matrix
		);

	//enable the colour array
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,					//data set - 0 = the first data set in the array
		2,					//How many vertices/numbers in our matrix we need to make a triangle
		GL_FLOAT, GL_FALSE, //data type, whether we normalise the values
		sizeof(float) * 8,  //stride - the length it takes to get to each number
		(void*)(6 * sizeof(float))			//override to 0, the offset of how many number to skip in the matrix
	);

	// enable the vertex array
	glEnableVertexAttribArray(2);

	//Clear the buffer
	glBindVertexArray(0);
}

VertexArrayObject::VertexArrayObject(vector<Vertex> Vertices, vector<vmuint> Indices)
{
	ID = EAB = VAB = 0;

	this->Vertices = Vertices;
	this->Indices = Indices;

	glBindVertexArray(ID);

	//Create an ID for the array buffer
	glGenBuffers(1, &VAB);
	//Bind the above IDs to the OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VAB);
	//Run through the data and attach the vertices to the VAB
	glBufferData(GL_ARRAY_BUFFER,
		Vertices.size() * sizeof(Vertex),
		&Vertices[0],
		GL_STATIC_DRAW);

	//Handle the Indices
	//Create an ID for the element array buffer
	glGenBuffers(1, &EAB);
	//Bind the above ID to the OpenGl as the element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAB);
	//Run through the data and attach the inidices to the EAB
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		Indices.size() * sizeof(vmuint),
		&Indices[0],
		GL_STATIC_DRAW);

	//Assign the vertices and indices to the VAO
	glVertexAttribPointer(
		0,					//data set - 0 = the first data set in the array
		3,					//How many vertices/numbers in our matrix we need to make a triangle
		GL_FLOAT, GL_FALSE, //data type, whether we normalise the values
		sizeof(float) * 8,  //stride - the length it takes to get to each number
		(void*)0			//override to 0, the offset of how many number to skip in the matrix
	);

	// enable the vertex array
	glEnableVertexAttribArray(0);

	//Assign the normals of the mesh vertices to the shader
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT, GL_FALSE,
		sizeof(float) * 8,
		(void*)(3 * sizeof(float)) //skips the first 3 numbers from the matrix
	);

	//enable the colour array
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(
		2,					//data set - 0 = the first data set in the array
		2,					//How many vertices/numbers in our matrix we need to make a triangle
		GL_FLOAT, GL_FALSE, //data type, whether we normalise the values
		sizeof(float) * 8,  //stride - the length it takes to get to each number
		(void*)(6 * sizeof(float))			//override to 0, the offset of how many number to skip in the matrix
	);

	// enable the vertex array
	glEnableVertexAttribArray(2);

	//Clear the buffer
	glBindVertexArray(0);
}

VertexArrayObject::~VertexArrayObject()
{
	//Clean the VAO in OpenGL
	glDeleteVertexArrays(1, &ID);

	//Clean the vectors
	Shape.PositionMatrix.clear();
	Shape.IndecesMatrix.clear();
	Vertices.clear();
	Indices.clear();

	cout << "Deleted VAO..." << "\n";
}

void VertexArrayObject::Draw()
{
	vector<vmuint> IndicesToUse;

	//decide which indices to use based on what's assigned
	if (Vertices.size() > 0)
		IndicesToUse = Indices;
	else
		IndicesToUse = Shape.IndecesMatrix;


	//bind our VAO to the current buffer
	glBindVertexArray(ID);
	//Draw the 3D object/VAO
	glDrawElements(GL_TRIANGLES,		//What type of object we are drawing 
		IndicesToUse.size(),		//How many vertices do we draw
		GL_UNSIGNED_INT,				//What type of data that is being input
		(void*)0);						//How many we should skip

	//Clear the VAO from the current array to allow for the next object
	glBindVertexArray(0);
}
