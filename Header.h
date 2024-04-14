class pacman
{
private:
	int xpos;
	int ypos;
	char face;
	int score;
	char prevChar;
	int pelletsEaten;
	int direction;
public:
	void locate(char arr[31][28]);
	void move(int m, char arr[31][28]);
	void increaseScore(int s);
	bool checkMove(int m, char arr[31][28]);
	bool gameOver(char arr[31][28]);
	void displayscore();
	char getFace();
	int getDirection();
	pacman();
	char getPrevChar();
	void setPrevChar(char x);
	int getPelletsEaten();
	int getScore();
	int getYpos();
	int getXpos();
	void setYpos(int y);
	void setXpos(int x);
	void setFace(char x);
	~pacman();
};

class Ghost
{
public:
	virtual int getXpos() = 0;
	virtual int getYpos() = 0;
	virtual void setXpos(int) = 0;
	virtual void setYpos(int) = 0;
	virtual void setPrevMove(int move) = 0;
	virtual void setPrev(char) = 0;
	virtual int getFace() = 0;
	virtual void setFace(char arr[31][28], char) = 0;
	virtual int getPrevMove() = 0;
	virtual char getPrev() = 0;
	virtual void chaseMode(char[31][28], pacman p, Ghost* g[4]) = 0;
	virtual void scatterMode(char[31][28], Ghost* g[4]) = 0;
	virtual void locate(char arr[31][28]) = 0;
	virtual void move(char arr[31][28], int shortest, Ghost* g[4]) = 0;
	virtual bool annihilated(char arr[31][28]) = 0;
	int target(char arr[31][28], int tx, int ty, int gx, int gy, int pMove); //movements
	void frightenMode(int count, char arr[31][28], pacman p, int face, int& xPos, int& yPos, char& prev, int& prevMove, bool check, Ghost* g[4]);//xPos and yPos are ghosts positions
};

class Blinky : public Ghost
{
private:
	char prev;
	char blinky;
	int xPos;
	int yPos;
	int prevMove;
public:
	Blinky();
	~Blinky();
	virtual void chaseMode(char arr[31][28], pacman p, Ghost* g[4]);
	void locate(char[31][28]);
	virtual void scatterMode(char[31][28], Ghost* g[4]);
	virtual void move(char arr[31][28], int shortest, Ghost* g[4]);
	virtual bool annihilated(char[31][28]); //eaten

	virtual void setFace(char arr[31][28], char x);
	virtual int getXpos();
	virtual int getPrevMove();
	virtual char getPrev();
	virtual int getYpos();
	virtual void setPrevMove(int move);
	virtual void setPrev(char x);
	virtual int getFace();
	virtual void setXpos(int x);
	virtual void setYpos(int y);
};

class Clyde : public Ghost
{
private:
	char prev;
	char clyde;
	int xPos;
	int yPos;
	int prevMove;
public:
	virtual void setXpos(int x);
	virtual void setYpos(int y);
	virtual int getPrevMove();
	virtual char getPrev();
	virtual void setPrevMove(int move);
	virtual void setPrev(char x);
	virtual int getFace();
	virtual void setFace(char arr[31][28], char x);
	virtual int getXpos();
	virtual int getYpos();
	Clyde();
	~Clyde();
	void locate(char arr[31][28]);
	virtual void chaseMode(char arr[31][28], pacman p, Ghost* g[4]);
	virtual void move(char arr[31][28], int shortest, Ghost* g[4]);
	virtual void scatterMode(char[31][28], Ghost* g[4]);
	virtual bool annihilated(char[31][28]); //eaten
};

class Pinky : public Ghost
{
private:
	char prev;
	char pinky;
	int xPos;
	int yPos;
	int prevMove;
public:
	virtual void setXpos(int x);
	virtual void setYpos(int y);
	virtual int getPrevMove();
	virtual char getPrev();
	virtual void setPrevMove(int move);
	virtual void setPrev(char x);
	virtual int getFace();
	virtual void setFace(char arr[31][28], char x);
	virtual int getXpos();
	virtual int getYpos();
	Pinky();
	~Pinky();
	virtual void chaseMode(char[31][28], pacman p, Ghost* g[4]);
	void locate(char[31][28]);
	virtual void scatterMode(char[31][28], Ghost* g[4]);
	virtual void move(char arr[31][28], int shortest, Ghost* g[4]);
	virtual bool annihilated(char[31][28]); //eaten
};

class Inky : public Ghost
{
private:
	char prev;
	char inky;
	int xPos;
	int yPos;
	int prevMove;
	Blinky b;
public:
	virtual void setXpos(int x);
	virtual void setYpos(int y);
	virtual int getPrevMove();
	virtual char getPrev();
	virtual void setPrevMove(int move);
	virtual void setPrev(char x);
	virtual int getFace();
	virtual void setFace(char arr[31][28], char x);
	virtual int getXpos();
	virtual int getYpos();
	Inky();
	~Inky();
	virtual void chaseMode(char[31][28], pacman p, Ghost* g[4]);
	void locate(char[31][28]);
	virtual void scatterMode(char[31][28], Ghost* g[4]);
	virtual void move(char arr[31][28], int shortest, Ghost* g[4]);
	virtual bool annihilated(char[31][28]); //eaten
};