#include "../headers/LineRenderer.h"

// Stores endPoints on the line
GLfloat verticesLine[] = {
-1.0f, -1.0f, -1.0f, // X , Y, Z of start point
 1.0f, -1.0f, -1.0f, // X, Y, Z of end point
};

/**
 * Initialize the line renderer, creates the line shader on the GPU and binds all correct buffers.
 *
 */
void LineRenderer::init()
{

	lineShader.initialize("Shaders/lineShader.vert", "Shaders/lineShader.frag");
	lineShader.SetMatrix(glm::ortho(0.0f, globals::width, globals::height, 0.0f, 0.1f, 100.0f), "projection");

	// Generate vertex aray and buffer object
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);

	// Bind buffer and set data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLine), verticesLine, GL_STATIC_DRAW);

	// Set layour of the vertex buffer
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	// Bind buffer and array to 0 for safety
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
/**
 * Get the Shader object linked to this line renderer.
 *
 * @return lineShader a pointer to a Shader object.
 */
Shader * LineRenderer::getShader()
{
	return &lineShader;
}
LineRenderer::LineRenderer()
{

}

/**
 * Render a line to screen using the desired start and end points of the line.
 *
 *@param startPoint 3 value vector for the start point of the line.
 *@param endPoint 3 value vector for the end point of the line.
 */
void LineRenderer::Render(glm::vec3 startPoint, glm::vec3 endPoint)
{
	//Set the start points for the line.
	verticesLine[0] = startPoint.x;
	verticesLine[1] = startPoint.y;
	verticesLine[3] = endPoint.x;
	verticesLine[4] = endPoint.y;

	//Set screen resolution on the shader.
	lineShader.Set2Float(globals::width, globals::height, "resolution");
	
	//Bind correct vertex arrays and buffers and attatch new line data.
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesLine), verticesLine, GL_STATIC_DRAW);
	glUseProgram(lineShader.shaderID);
	//Draw the line.
	glDrawArrays(GL_LINE_LOOP, 0, 2);
	//Unbind buffers and shader after use.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glUseProgram(0);
}

/**
 * Set a float inside the shader attatched to this line renderer.
 *
 *@param value1 the first value of the 2 float variable to be set.
 *@param value2 the second value of the 2 float variable to be set.
 *@param name the name of the variable on the shader to be set.
 */
void LineRenderer::SetFloat(float value1, float value2,const char* name)
{
	lineShader.Set2Float(value1, value2, name);
}

//Destructor
LineRenderer::~LineRenderer()
{
}
