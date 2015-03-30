#ifndef GD_H_
#define GD_H_

#include <vector>
#include <cstdlib>

#include "snake.h"
#include "block.h"

enum key {key_up, key_right, key_down, key_left, key_esc};

class GameplayDirector
{
	public:
		
		static void gdStart(int argc, char ** argv);
		static void gdProcess();
		static void gdKeyPressed(key pressedKey);
		static void gdMoveSnakeThroughWall(int & X, int & Y);

	
		static bool  gdIsActive();
		static Snake gdGetSnake();
		static Block  gdGetSnack(int n);
		static int   gdGetSnacksQuantity();		

	private:
		
		static inline void gdPause();
		static inline void gdTurnSnake(direction newDirection);
		static void gdAddSnack(block_type type = normal);

		
		static Snake Python;
		static vector<Block> gdSnacks;
		static bool isActive; 

		static const int SNACKS_LIMIT = 1;
		static const int FIELD_WIDTH = 30;
		static const int FIELD_HEIGHT = 20;
};

#endif
