#include "GameEngine.h"
#include "Constants.h"
#include "glut.h"


GameEngine * gameEngine;

void loop()
{
	gameEngine->MainLoop();
}

void keyboard()
{
	//package this to gameEngine
}

void mouseMove(int posX, int posY)
{
	userInput input;
	input.mouseX = posX;
	input.mouseY = posY;
	input.clicked = false;
	//package this to gameEngine
	gameEngine->GivenUserInput(input);
}

int main(int argc, char **argv)
{
	gameEngine = new GameEngine();
	gameEngine->Start();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize(GLOBAL_WIDTH, GLOBAL_HEIGHT);
	glutCreateWindow("COMP371 PROJECT");
	glutDisplayFunc(loop);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMove);

	glutMainLoop();
}



