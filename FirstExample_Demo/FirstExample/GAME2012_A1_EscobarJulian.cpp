
//***************************************************************************
// GAME2012 - GAME2012_A1_EscobarJulian.cpp by Julian Escobar - 101286557
//
// Assignment 1 submission.
//
// Description:
// In this assignment we are going to play around with some rectangulars shapes and with opengl overall.
//
//***************************************************************************


using namespace std;

#include "stdlib.h"
#include "time.h"
#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include <iostream>
#include <time.h>

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

#define X_AXIS glm::vec3(1,0,0)
#define Y_AXIS glm::vec3(0,1,0)
#define Z_AXIS glm::vec3(0,0,1)

//Input variables
int numberSquares;
float rotationAngle;

GLuint vao, points_vbo, colors_vbo, modelID, colorID;

GLfloat points[] = {
	-0.5f,  0.5f,  0.0f,
	0.5f,  0.5f,  0.0f,
	0.5f, -0.5f,  0.0f,
	-0.5f, -0.5f,  0.0f
};

GLfloat colors[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f
};


GLuint Buffers[NumBuffers];

const GLuint NumVertices = 10;
const GLfloat scale = 0.5f;
GLfloat vertices[NumVertices][2];

void init(void)
{
	//Specifying the name of vertex and fragment shaders.
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "square.vert" },
		{ GL_FRAGMENT_SHADER, "square.frag" },
		{ GL_NONE, NULL }
	};

	//Loading and compiling shaders
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);	//My Pipeline is set up

	glClearColor(1.0, 1.0, 1.0, 0.0);

	modelID = glGetUniformLocation(program, "model");
	colorID = glGetUniformLocation(program, "u_Color");

	
	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	points_vbo = 0;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), points, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0); // Can optionally unbind the buffer to avoid modification.

	glBindVertexArray(0); // Can optionally unbind the vertex array to avoid modification.
	
	
}

// transformModel
//

void transformObject(float scale, glm::vec3 rotationAxis,
	float rotationAngle, glm::vec3 translation)
{
	glm::mat4 Model;
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, translation);
	Model = glm::rotate(Model, glm::radians(rotationAngle), rotationAxis);
	Model = glm::scale(Model, glm::vec3(scale));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &Model[0][0]);
}

//---------------------------------------------------------------------
//
// display
//

void
display(void)
{
	glClearColor(0.0, 0.2, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vao);
	float scale = 1.75f;


	for (int i = 0; i < numberSquares; i++)
	{
		float r = rand() % 100 / 100.0f;
		float b = rand() % 100 / 100.0f;
		float g = rand() % 100 / 100.0f;
		transformObject(scale, Z_AXIS, rotationAngle * i, glm::vec3(0.0f, 0.0f, 0.0f));

		//Ordering the GPU to start the pipeline
		glDrawArrays(GL_LINE_LOOP, 0, 4);
		scale = sqrt(scale * 0.5 * scale * 0.5 + scale * 0.5 * scale * 0.5);
		glUniform4f(colorID, r, b, g, 1.0);

	}
	glBindVertexArray(0); // Can optionally unbind the vertex array to avoid modification.
	glFlush(); // Instead of double buffering.
}

void idle()
{
	glutPostRedisplay();
}

//---------------------------------------------------------------------
//
// main
//

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Escobar, Julian, 101286557");

	glewInit();	//Initializes the glew and prepares the drawing pipeline.

	init();

	std::cout << "Hello" << std::endl;
	std::cout << "Please Type the amount of square that you want: " << std::endl;
	std::cin >> numberSquares;
	std::cout << "Angle of Rotation: " << std::endl;
	std::cin >> rotationAngle;

	glutDisplayFunc(display);

	glutIdleFunc(idle);

	glutMainLoop();
	
	

}
