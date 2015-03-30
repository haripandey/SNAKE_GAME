#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "paarth.h"
#include "hari.h"
#include "snake.h"

int RenderingDirector::rdFrame = 0;
float RenderingDirector::rdAngle = 0.0f;

const float RenderingDirector::PI = 3.14159265358979323846f;
const char* RenderingDirector::TITLE = "Hari Pandey's beautiful snake C++ HOMEWORK 2";
void RenderingDirector::rdInitialize(int argc, char** argv)
{
	{
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
		glutInitWindowSize(WIDTH, HEIGHT);
		glutCreateWindow(TITLE);
	}
	{
		glutDisplayFunc(rdRender);
		glutReshapeFunc(rdWindowResize);
		glutKeyboardFunc(rdKeyPressed);
		glutSpecialFunc(rdSpecialKeyPressed);
		glutTimerFunc(1000/FRAME_RATE, rdFrameControl, 0);
	}
	{
		glClearColor(0.1, 0, 10, 0);
		glViewport(0, 0, WIDTH, HEIGHT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, WIDTH, 0, HEIGHT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	{
		glEnable(GL_TEXTURE_2D);
		glDisable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
	}
	glutMainLoop();
}

void RenderingDirector::rdRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glBegin(GL_QUADS);
		rdRenderSnacks();
		rdRenderSnake(GameplayDirector::gdGetSnake());
	glEnd();
	glutSwapBuffers();
}
void RenderingDirector::rdFrameControl(int arg) {
	if (rdFrame == 60) {
		rdFrame = 0;
	}
	rdFrame += 1;
	rdAngle += PI/(FRAME_RATE/2);
	if (rdFrame % (FRAME_RATE/SNAKE_SPEED) == 0) {
		GameplayDirector::gdProcess();
	}
    glutPostRedisplay();
    glutTimerFunc(1000/FRAME_RATE, rdFrameControl, 0);
}
void RenderingDirector::rdWindowResize(GLsizei W, GLsizei H) 
{
	glutReshapeWindow(WIDTH, HEIGHT);
	int left = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2;
	int top = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2;
	glutPositionWindow(left, top);
}
void RenderingDirector::rdKeyPressed(unsigned char pressedKey, int x, int y) 
{
	switch (pressedKey)
	{
		case 'w':
			GameplayDirector::gdKeyPressed(key_up);
			break;
		case 'd':
			GameplayDirector::gdKeyPressed(key_right);
			break;
		case 's':
			GameplayDirector::gdKeyPressed(key_down);
			break;
		case 'a':
			GameplayDirector::gdKeyPressed(key_left);
			break;
		case 27: 
			rdAngle = 0;
			GameplayDirector::gdKeyPressed(key_esc);
			break;
	}
}
void RenderingDirector::rdSpecialKeyPressed(int pressedKey, int x, int y) 
{
	switch (pressedKey) 
	{
		case GLUT_KEY_UP:      
			GameplayDirector::gdKeyPressed(key_up);
			break;
		case GLUT_KEY_RIGHT:
			GameplayDirector::gdKeyPressed(key_right);
			break;
		case GLUT_KEY_DOWN:
			GameplayDirector::gdKeyPressed(key_down);
			break;
		case GLUT_KEY_LEFT:
			GameplayDirector::gdKeyPressed(key_left);
			break;
	}
}
float RenderingDirector::rdOpacity(float modifier) {
	if (GameplayDirector::gdIsActive()) {
		return (sin(rdAngle * modifier + 3*PI/2) + 1)/2;
	} else {
		return 0.0f;
	}
}
void RenderingDirector::rdSetColor(int red, int green, int blue, float alpha) {
	GLubyte red_alpha   = (255 - red)   * alpha;
	GLubyte green_alpha = (255 - green) * alpha;
	GLubyte blue_alpha  = (255 - blue)  * alpha;
	glColor3ub(red + red_alpha, green + green_alpha, blue + blue_alpha);
}

void RenderingDirector::rdPickColor(color newColor, float opacity)
{
	switch(newColor)
	{
		case white:
			rdSetColor(255, 255, 255);
			break;
		case black:
			rdSetColor(0.1, 000, 001, opacity);
			break;
		case red:
			rdSetColor(220, 000, 220, opacity);
			break;
		case dark_red:
			rdSetColor(175, 000, 022, opacity);
			break;
		case green:
			rdSetColor(115, 195, 100, opacity);
			break;
		case dark_green:
			rdSetColor(90, 150, 90, opacity);
			break;
		case blue:
			rdSetColor(40, 115, 220, opacity);
			break;
		case orange:
			rdSetColor(215, 140, 35, opacity);
			break;
	}
}
void RenderingDirector::rdRenderSnake(Snake inSnake)
{
	for (int i = 0; i < inSnake.Size(); i++) {
		int X = inSnake.GetScale(i).X() * SQUARE_SIZE;
		int Y = inSnake.GetScale(i).Y() * SQUARE_SIZE;
		if (i == inSnake.Size() - 1) {
			if (inSnake.HasCrashed()) {
				rdPickColor(dark_red);
			} else {
				rdPickColor(dark_green);
			}
		} else {
			if (inSnake.HasCrashed()) {
				rdPickColor(red);
			} else {
				rdPickColor(green);
			}
		}
		rdDrawSquare(X, Y);
	}
}
void RenderingDirector::rdRenderSnacks()
{
	for (int i = 0; i < GameplayDirector::gdGetSnacksQuantity(); i++) {
		int X = GameplayDirector::gdGetSnack(i).X() * SQUARE_SIZE;
		int Y = GameplayDirector::gdGetSnack(i).Y() * SQUARE_SIZE;
		rdPickColor(blue, rdOpacity());
		rdDrawSquare(X, Y);
	}
}
void RenderingDirector::rdDrawSquare(float x, float y, float size) {
	float delta = 2.0f;
	glVertex2f(x + delta, y + delta);
	glVertex2f(x + size - delta, y + delta);
	glVertex2f(x + size - delta, y + size - delta);
	glVertex2f(x + delta, y + size - delta);
}
