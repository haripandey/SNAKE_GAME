#ifndef PIECE_H_
#define PIECE_H_

class parts {
	public:
		parts() { }
		parts(int inX, int inY) : myX(inX), myY(inY) { }

		int X() const {return myX;}
		int Y() const {return myY;}

		bool operator==(const parts & s) {
			return (s.myX == myX && s.myY == myY);
		}
		
		parts & operator=(const parts & s) {
			myX = s.myX;
			myY = s.myY;
			return *this;
		}

	private:
		int myX, myY;
};

#endif
