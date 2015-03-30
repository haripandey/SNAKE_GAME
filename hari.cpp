#include <iostream>

#include "hari.h"
#include "paarth.h"

using std::cout;
using std::endl;

Snake GameplayDirector::Python;
vector<Block> GameplayDirector::gdSnacks;
bool GameplayDirector::isActive = false;
void GameplayDirector::gdStart(int argc, char ** argv) {
	isActive = true;
	RenderingDirector::rdInitialize(argc, argv);
}
void GameplayDirector::gdProcess()
{
	if (isActive) {
		bool isHungry = true;
		for (int i = 0; i < gdSnacks.size(); i++) {
			int X = gdSnacks[i].X();
			int Y = gdSnacks[i].Y();
			if (Python.HasCaughtSnack(X, Y)) {
				gdSnacks.erase(gdSnacks.begin() + i);
				isHungry = false;
			}
		}
		if (gdSnacks.size() < SNACKS_LIMIT) {
			gdAddSnack();
		}
		if (isHungry) {
			Python.Move();
		}
	}
}
void GameplayDirector::gdKeyPressed(key pressedKey) 
{
	switch(pressedKey)
	{
		case key_up:
			gdTurnSnake(UP);
			break;
		case key_right:
			gdTurnSnake(RIGHT);
			break;
		case key_down:
			gdTurnSnake(DOWN);
			break;
		case key_left: 
			gdTurnSnake(LEFT);
			break;
		case key_esc:
			gdPause();
			break;
	}
}
void GameplayDirector::gdMoveSnakeThroughWall(int & X, int & Y) {
	if (X >= FIELD_WIDTH) X = 0;
	if (Y >= FIELD_HEIGHT) Y = 0;
	if (X < 0) X = FIELD_WIDTH - 1;
	if (Y < 0) Y = FIELD_HEIGHT - 1;
}

bool GameplayDirector::gdIsActive() {
	return isActive;
}

Snake GameplayDirector::gdGetSnake() {
	return Python;
}

Block GameplayDirector::gdGetSnack(int n) {
	return gdSnacks[n];
}

int GameplayDirector::gdGetSnacksQuantity() {
	return gdSnacks.size();
}
void GameplayDirector::gdPause() {
	isActive = !isActive;
	if (isActive) cout << "Unpaused" << endl;
			 else cout << "Paused"   << endl;
}

void GameplayDirector::gdTurnSnake(direction newDirection) {
	if (isActive) {
		Python.Turn(newDirection);
	}
}
void GameplayDirector::gdAddSnack(block_type type) {
	int blockX, blockY;
	do {
		blockX = rand() % FIELD_WIDTH;
		blockY = rand() % FIELD_HEIGHT;
	} while (Python.IsHere(blockX, blockY));
	gdSnacks.push_back(Block(blockX, blockY, type));
}
