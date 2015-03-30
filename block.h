#ifndef FOOD_H_
#define FOOD_H_

#include "parts.h"

enum block_type {normal};

class Block
{
	public:
		Block(int x, int y, block_type inType) : type(inType) {
			coordinate = parts(x, y);
		}

		Block(parts inCoordinate, block_type inType) : type(inType) {
			coordinate = inCoordinate;
		}
		int const X() {return coordinate.X();}
		int const Y() {return coordinate.Y();}
		int const Type() {return type;}

	private:
		block_type type;
		parts coordinate;
};

#endif
