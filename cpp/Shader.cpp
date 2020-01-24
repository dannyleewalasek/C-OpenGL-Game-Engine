#include "../headers/Shader.h"

/**
 * Clear all data linked to this Shader freom the GPU.
 *
 */
void Shader::clearShader()
{
	glDeleteShader(shaderID);
}

/**
 * Set the matrix for the shader used for on screen positioning.
 *@param matrix the matrix to be passed to the shader.
 *@param uniformName the name of the matrix variable in the shader code.
 *
 */
void Shader::SetMatrix(glm::mat4 matrix,const char* uniformName)
{
	glUseProgram(shaderID);
	uniform = glGetUniformLocation(shaderID, uniformName);
	glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));
	glUseProgram(0);
}

/**
 * Set a 2 value variable inside the shader.
 *@param float1 the first variable to be set.
 *@param float2 the second variable to be set.
 *@param uniformName the name of the variable on the shader to be set.
 *
 */
void Shader::Set2Float(GLfloat float1, GLfloat float2,const char* uniformName)
{
	glUseProgram(shaderID);
	uniform = glGetUniformLocation(shaderID, uniformName);
	glUniform2f(uniform, float1, float2);
	glUseProgram(0);
}

/**
 * Add shader to the GPU
 *@param theProgram An integer used to find the program on the GPU to attatch the shader to.
 *@param shaderCode The code of the shader to be transferred to the gpu.
 *@param shaderType Defines the type of shjader to be created.
 *
 */
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const char* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
}

/**
 * Initilize the shader and attach to the GPU.
 *@param vertLocation the location of the vertex shader code.
 *@param fragLocation the location of the fragment shader code.
 *
 */
void Shader::initialize(const char*vertLocation,const char* fragLocation) {
	std::string vertShader;
	std::string fragShader;
	try
	{
		// Open files
		std::ifstream vertexShader(vertLocation);
		std::ifstream fragmentShader(fragLocation);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShader.rdbuf();
		fShaderStream << fragmentShader.rdbuf();
		// close file handlers
		vertexShader.close();
		fragmentShader.close();
		// Convert stream into string
		vertShader = vShaderStream.str();
		fragShader = fShaderStream.str();

	}
	catch (std::exception e)
	{
		std::cout << "Error reading shader files" << std::endl;
	}
	
	const char * vShader = vertShader.c_str();
	const char * fShader = fragShader.c_str();

	shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Shader creation failed");
		return;
	}

	AddShader(shaderID, vShader, GL_VERTEX_SHADER);
	AddShader(shaderID, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}
	
}

Shader::Shader()
{
}


Shader::~Shader()
{
	clearShader();
}
