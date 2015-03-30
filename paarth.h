#ifndef RD_H_
#define RD_H_

#include "snake.h"

enum color {white, black, red, dark_red, green, dark_green, blue, orange};

class RenderingDirector
{
	public:
		static void rdInitialize(int argc, char **argv);

	private:
		static void rdRender();
		static void rdFrameControl(int arg);
		static void rdWindowResize(int W, int H);
		static void rdKeyPressed(unsigned char pressedKey, int x, int y);
		static void rdSpecialKeyPressed(int pressedKey, int x, int y);

		static void rdSetColor(int red, int green, int blue, float alpha = 0.0f);
		static void rdPickColor(color newColor, float opacity = 0.0f);
		static float rdOpacity(float modifier = 1.0f);

		static void rdRenderSnake(Snake inSnake);
		static void rdRenderSnacks();
		static void rdDrawSquare(float x, float y, float size = SQUARE_SIZE);

		static int rdFrame;
		static float rdAngle;

	
		static const int WIDTH  = 640;
		static const int HEIGHT = 420;
		static const int FRAME_RATE = 60;
		static const int SNAKE_SPEED = 15; 
		static const float PI;
		static const char* TITLE;
		static const int SQUARE_SIZE = 20;
};

#endif
