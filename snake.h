#ifndef SNAKE_H_
#define SNAKE_H_

#include <vector>
#include "parts.h"

using std::vector;

enum direction {UP, DOWN, RIGHT, LEFT, NONE};

class Snake {
	public:
		/* Constructors */
		Snake(int size = dSnakeSize);

		/* Methods */
		bool Turn(direction newDirection);
		void Move();

		bool HasCrashed();
		bool HasCaughtSnack(int x, int y);
		bool IsHere(int x, int y);

		/* Getters */
		parts const GetScale(int n);
		int const Size();

	private:
		/* Methods */
		void AddScale();
		void DelScale();
		void Punish();
		void PrintSize();

		/* Fields */
		direction myDirection;
		vector<parts> myScales;
		bool canTurn;
		bool isReady;
		int indulgence;

		/* Options */
		// d prefix stands for "default"
		static const int dSnakeSize = 6;
		static const int dSnakeInitialPositionX = 0;
		static const int dSnakeInitialPositionY = 8;
		static const int CRASH_PENALTY = 3;
		static const int INDULGENCE_SIZE = 12;
		static const int MIN_SIZE = 3;
};

#endif
