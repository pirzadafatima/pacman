#include <conio.h>
#include<ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Header.h"


using namespace sf;
using namespace std;

void initialize(char arr[31][28]);
void display(char arr[31][28], Sprite& s, Vector2u& textureSize, RenderWindow& window, Sprite sprite);
int main()
{
	int count1 = 0;
	int count2 = 0;
	int count3 = 0;
	int count4 = 0;
	// create the window
	RenderWindow window(sf::VideoMode(280, 310), "Pacman", Style::Default);


	/*******************/
	Texture texture;
	texture.loadFromFile("map.jpg");
	Sprite sprite;
	Vector2u size = texture.getSize();
	sprite.setTexture(texture);
	sprite.setScale(1.24f, 1.24f);
	/*******************/

	window.draw(sprite);
	window.setFramerateLimit(5);

	//create a sprite
	Sprite s;

	Texture t;
	t.loadFromFile("sprite.png");
	Vector2u textureSize = t.getSize();
	textureSize.x /= 8;
	textureSize.y /= 6;
	s.setTexture(t);
	t.setSmooth(true);//not imp

	char arr[31][28];
	initialize(arr);
	pacman p;
	p.locate(arr);
	//display(arr);
	unsigned char ch2 = 75; //initially moves to left
	int previousMove = ch2;

	/*********/
	//creating the ghost objects
	//g[0] is clyde, //g[1] is Blinky
	Ghost* g[4];
	g[0] = new Clyde;
	g[0]->locate(arr);

	g[1] = new Blinky;
	g[1]->locate(arr);

	g[2] = new Pinky;
	g[2]->locate(arr);

	g[3] = new Inky;
	g[3]->locate(arr);

	time_t beginT = time(NULL), endT = time(NULL);//clock for frightened mode
	time_t beginS = time(NULL), endS = time(NULL);//clock for scattermode

	bool checkAnnihilated = false;
	bool checkAlive = true;
	// run the program as long as the window is open
	while (window.isOpen())
	{
		//dt = clock.getElapsedTime().asSeconds();
		//cout << dt;
		bool frightened = false;



		while (p.gameOver(arr) == false && checkAlive == true)
		{

			while (!_kbhit() && p.gameOver(arr) == false)
			{
				if (frightened == false)
				{
					beginT = time(NULL);//clock.restart();
					endT = time(NULL);

				}




				if (p.getPrevChar() != '@' && frightened == false)
				{
					beginS = time(NULL);//clock has started



					if (p.getPelletsEaten() >= 60 && g[0]->getXpos() <= 16 && g[0]->getXpos() >= 11 && g[0]->getYpos() >= 12 && g[0]->getYpos() <= 15) //clyde leaves ghost house after pacman has eaten atleast 60 pellets
					{
						int outOfTheHouse = true;
						int shortest = g[0]->target(arr, 14, 11, g[0]->getXpos(), g[0]->getYpos(), g[0]->getPrevMove());
						g[0]->move(arr, shortest, g);
						outOfTheHouse = false;
					}
					else
						if (difftime(beginS, endS) < 15)
						{
							g[0]->scatterMode(arr, g);
						}
						else
						{
							g[0]->chaseMode(arr, p, g);
							if (difftime(beginS, endS) == 40)
							{
								beginS = time(NULL);
								endS = time(NULL);
							}
						}

					if (p.getPelletsEaten() >= 3 && g[2]->getXpos() <= 16 && g[2]->getXpos() >= 11 && g[2]->getYpos() >= 12 && g[2]->getYpos() <= 15) //pinky leaving ghost house immediately
					{
						int shortest = g[2]->target(arr, 14, 11, g[2]->getXpos(), g[2]->getYpos(), g[2]->getPrevMove());
						g[2]->move(arr, shortest, g);
					}
					else
						if (difftime(beginS, endS) < 15)
						{
							g[2]->scatterMode(arr, g);
						}
						else
						{
							g[2]->chaseMode(arr, p, g);
							if (difftime(beginS, endS) == 40)
							{
								beginS = time(NULL);
								endS = time(NULL);
							}
						}

					if (p.getPelletsEaten() >= 30 && g[3]->getXpos() <= 16 && g[3]->getXpos() >= 11 && g[3]->getYpos() >= 12 && g[3]->getYpos() <= 15) //inky leaves after pacman has eaten atleast 30 pellets
					{
						int shortest = g[3]->target(arr, 14, 11, g[3]->getXpos(), g[3]->getYpos(), g[3]->getPrevMove());
						g[3]->move(arr, shortest, g);
					}
					else
						if (difftime(beginS, endS) < 15)
						{
							g[3]->scatterMode(arr, g);
						}
						else
						{
							g[3]->chaseMode(arr, p, g);
							if (difftime(beginS, endS) == 40)
							{
								beginS = time(NULL);
								endS = time(NULL);
							}
						}

					// check all the window's events that were triggered since the last iteration of the loop
					sf::Event event;
					while (window.pollEvent(event))
					{
						// "close requested" event: we close the window
						if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Key::Escape))

							window.close();

					}
					//clock.restart();
					beginT = time(NULL);
					endT = time(NULL);

					//c.restart().asSeconds();

					if (difftime(beginS, endS) < 15)
					{

						g[1]->scatterMode(arr, g);//blinky
					}
					else
					{
						g[1]->chaseMode(arr, p, g);
						if (difftime(beginS, endS) == 40)
						{
							beginS = time(NULL);
							endS = time(NULL);
						}
					}
				}
				int move = ch2;
				bool check = p.checkMove(move, arr); //it will be false if no new move is entered.
				bool checkAnnihilated = false;

				if (check == false)
				{
					bool check2 = p.checkMove(previousMove, arr);
					if (check2 == true)
					{
						p.move(previousMove, arr);
					}


					if (p.getPrevChar() == '@')
					{
						if (frightened == false)
						{
							beginT = time(NULL);
							endT = time(NULL);


							frightened = true;
							g[0]->setFace(arr, 'c');
							g[1]->setFace(arr, 'b');
							g[2]->setFace(arr, 'p');
							g[3]->setFace(arr, 'i');

						}

					}

					if (frightened == true)
					{
						//Frightened: CLYDE*********************************
						char prev = g[0]->getPrev();
						int prevMove = g[0]->getPrevMove();
						int x = g[0]->getXpos();
						int y = g[0]->getYpos();

						if (p.getXpos() == g[0]->getXpos() && p.getYpos() == g[0]->getYpos())
						{

							count1 = 0;

							checkAnnihilated = true;

							p.setXpos(g[0]->getXpos());
							p.setYpos(g[0]->getYpos());
							arr[g[0]->getYpos()][g[0]->getXpos()] = 'P';
							g[0]->setPrev('P');

							window.setFramerateLimit(15);

							while (g[0]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[0]->setXpos(14);
							g[0]->setYpos(11);
							g[0]->setFace(arr, '%');
							checkAnnihilated = false;

							g[0]->locate(arr);

						}
						else
						{
							g[0]->frightenMode(count1, arr, p, g[0]->getFace(), x, y, prev, prevMove, checkAnnihilated, g);// will target a tile if annihiated

							checkAnnihilated = false;
							count1++;

							window.clear();
							display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
							system("cls");
							p.displayscore();

							g[0]->setXpos(x);
							g[0]->setYpos(y);
						}

						if (p.getXpos() == g[0]->getXpos() && p.getYpos() == g[0]->getYpos())//if somehow ghost moves into pacman it will get eaten.
						{

							count1 = 0;

							checkAnnihilated = true;

							p.setXpos(g[0]->getXpos());
							p.setYpos(g[0]->getYpos());
							arr[g[0]->getYpos()][g[0]->getXpos()] = 'P';
							g[0]->setPrev('P');//new

							window.setFramerateLimit(15);

							while (g[0]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[0]->setXpos(14);
							g[0]->setYpos(11);
							g[0]->setFace(arr, '%');
							checkAnnihilated = false;

							g[0]->locate(arr);

						}
						//Frightened: Blinky*******************************
						char prev1 = g[1]->getPrev();
						int prevMove1 = g[1]->getPrevMove();
						int x1 = g[1]->getXpos();
						int y1 = g[1]->getYpos();


						if (p.getXpos() == g[1]->getXpos() && p.getYpos() == g[1]->getYpos())
						{

							count2 = 0;

							checkAnnihilated = true;

							p.setXpos(g[1]->getXpos());
							p.setYpos(g[1]->getYpos());
							arr[g[1]->getYpos()][g[1]->getXpos()] = 'P';
							g[1]->setPrev('P');
							window.setFramerateLimit(15);

							while (g[1]->annihilated(arr) == false)
							{

								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[1]->setXpos(14);
							g[1]->setYpos(11);
							g[1]->setFace(arr, '%');
							checkAnnihilated = false;

							g[1]->locate(arr);

						}
						else
						{
							g[1]->frightenMode(count2, arr, p, g[1]->getFace(), x1, y1, prev1, prevMove1, checkAnnihilated, g);

							checkAnnihilated = false;
							count2++;

							window.clear();
							display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
							system("cls");
							p.displayscore();


							g[1]->setXpos(x1);
							g[1]->setYpos(y1);
						}
						if (p.getXpos() == g[1]->getXpos() && p.getYpos() == g[1]->getYpos())
						{

							count2 = 0;

							checkAnnihilated = true;

							p.setXpos(g[1]->getXpos());
							p.setYpos(g[1]->getYpos());
							arr[g[1]->getYpos()][g[1]->getXpos()] = 'P';
							g[1]->setPrev('P');
							window.setFramerateLimit(15);

							while (g[1]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[1]->setXpos(14);
							g[1]->setYpos(11);
							g[1]->setFace(arr, '%');
							checkAnnihilated = false;

							g[1]->locate(arr);

						}
						//Frightened: Pinky***************************************************************
						char prev2 = g[2]->getPrev();
						int prevMove2 = g[2]->getPrevMove();
						int x2 = g[2]->getXpos();
						int y2 = g[2]->getYpos();

						if (p.getXpos() == g[2]->getXpos() && p.getYpos() == g[2]->getYpos())
						{

							count3 = 0;

							checkAnnihilated = true;

							p.setXpos(g[2]->getXpos());
							p.setYpos(g[2]->getYpos());
							arr[g[2]->getYpos()][g[2]->getXpos()] = 'P';
							g[2]->setPrev('P');

							window.setFramerateLimit(15);

							while (g[2]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[2]->setXpos(14);
							g[2]->setYpos(11);
							g[2]->setFace(arr, '%');
							checkAnnihilated = false;

							g[2]->locate(arr);

						}
						else
						{
							g[2]->frightenMode(count3, arr, p, g[2]->getFace(), x2, y2, prev2, prevMove2, checkAnnihilated, g);// will target a tile if annihiated

							checkAnnihilated = false;
							count3++;

							window.clear();
							display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
							system("cls");
							p.displayscore();

							g[2]->setXpos(x2);
							g[2]->setYpos(y2);
						}
						if (p.getXpos() == g[2]->getXpos() && p.getYpos() == g[2]->getYpos())
						{

							count3 = 0;

							checkAnnihilated = true;

							p.setXpos(g[2]->getXpos());
							p.setYpos(g[2]->getYpos());
							arr[g[2]->getYpos()][g[2]->getXpos()] = 'P';
							g[2]->setPrev('P');

							window.setFramerateLimit(15);

							while (g[2]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[2]->setXpos(14);
							g[2]->setYpos(11);
							g[2]->setFace(arr, '%');
							checkAnnihilated = false;

							g[2]->locate(arr);

						}
						//*******************************//Inky

						char prev3 = g[3]->getPrev();
						int prevMove3 = g[3]->getPrevMove();
						int x3 = g[3]->getXpos();
						int y3 = g[3]->getYpos();

						if (p.getXpos() == g[3]->getXpos() && p.getYpos() == g[3]->getYpos())
						{

							count4 = 0;

							checkAnnihilated = true;

							p.setXpos(g[3]->getXpos());
							p.setYpos(g[3]->getYpos());
							arr[g[3]->getYpos()][g[3]->getXpos()] = 'P';
							g[3]->setPrev('P');//new

							window.setFramerateLimit(15);

							while (g[3]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[3]->setXpos(14);
							g[3]->setYpos(11);
							g[3]->setFace(arr, '%');
							checkAnnihilated = false;

							g[3]->locate(arr);

						}
						else
						{
							g[3]->frightenMode(count4, arr, p, g[3]->getFace(), x3, y3, prev3, prevMove3, checkAnnihilated, g);// will target a tile if annihiated

							checkAnnihilated = false;
							count4++;

							window.clear();
							display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
							system("cls");
							p.displayscore();


							g[3]->setXpos(x3);
							g[3]->setYpos(y3);
						}
						if (p.getXpos() == g[3]->getXpos() && p.getYpos() == g[3]->getYpos())
						{

							count4 = 0;

							checkAnnihilated = true;

							p.setXpos(g[3]->getXpos());
							p.setYpos(g[3]->getYpos());
							arr[g[3]->getYpos()][g[3]->getXpos()] = 'P';
							g[3]->setPrev('P');//new

							window.setFramerateLimit(15);

							while (g[3]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[3]->setXpos(14);
							g[3]->setYpos(11);
							g[3]->setFace(arr, '%');
							checkAnnihilated = false;

							g[3]->locate(arr);

						}
						//**************************************

						if (count1 == 0 && g[0]->getFace() == '%')
							g[0]->setFace(arr, 'c');//it is still in frightened mode

						if (count2 == 0 && g[1]->getFace() == '%')
							g[1]->setFace(arr, 'b');//it is still in frightened mode

						if (count3 == 0 && g[2]->getFace() == '%')
							g[2]->setFace(arr, 'p');//it is still in frightened mode

						if (count4 == 0 && g[2]->getFace() == '%')
							g[3]->setFace(arr, 'i');//it is still in frightened mode


						window.clear();
						display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
						system("cls");
						p.displayscore();

						system("cls");

						beginT = time(NULL);

						if (difftime(beginT, endT) >= 15)//
						{
							endT = time(NULL);//clock.restart();//end and beginning will be the same
							beginT = time(NULL);
							frightened = false;

							g[0]->setFace(arr, '1');//this sets clydes face back to normal.
							g[1]->setFace(arr, '2');//this sets blinkys face back to normal.
							g[2]->setFace(arr, '3');//this sets pinkys face back to normal.
							g[3]->setFace(arr, '4');//this sets inkys face back to normal.
						}
					}



				}
				if (check == true)
				{


					p.move(move, arr);
					previousMove = ch2;


					if (p.getPrevChar() == '@')
					{
						if (frightened == false)
						{
							beginT = time(NULL);
							endT = time(NULL);


							frightened = true;
							g[0]->setFace(arr, 'c');
							g[1]->setFace(arr, 'b');
							g[2]->setFace(arr, 'p');
							g[3]->setFace(arr, 'i');

						}

					}
					if (frightened == true)
					{
						//Frightened: CLYDE*********************************
						char prev = g[0]->getPrev();
						int prevMove = g[0]->getPrevMove();
						int x = g[0]->getXpos();
						int y = g[0]->getYpos();

						if (p.getXpos() == g[0]->getXpos() && p.getYpos() == g[0]->getYpos())
						{

							count1 = 0;

							checkAnnihilated = true;

							p.setXpos(g[0]->getXpos());
							p.setYpos(g[0]->getYpos());
							arr[g[0]->getYpos()][g[0]->getXpos()] = 'P';
							g[0]->setPrev('P');//new

							window.setFramerateLimit(15);

							while (g[0]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[0]->setXpos(14);
							g[0]->setYpos(11);
							g[0]->setFace(arr, '%');
							checkAnnihilated = false;

							g[0]->locate(arr);

						}
						else
						{
							g[0]->frightenMode(count1, arr, p, g[0]->getFace(), x, y, prev, prevMove, checkAnnihilated, g);// will target a tile if annihiated

							checkAnnihilated = false;
							count1++;

							window.clear();
							display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
							system("cls");
							p.displayscore();

							g[0]->setXpos(x);
							g[0]->setYpos(y);
						}

						if (p.getXpos() == g[0]->getXpos() && p.getYpos() == g[0]->getYpos())//if somehow ghost moves into pacman it will get eaten.
						{

							count1 = 0;

							checkAnnihilated = true;

							p.setXpos(g[0]->getXpos());
							p.setYpos(g[0]->getYpos());
							arr[g[0]->getYpos()][g[0]->getXpos()] = 'P';
							g[0]->setPrev('P');//new

							window.setFramerateLimit(15);

							while (g[0]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[0]->setXpos(14);
							g[0]->setYpos(11);
							g[0]->setFace(arr, '%');
							checkAnnihilated = false;

							g[0]->locate(arr);

						}
						//Frightened: Blinky*******************************
						char prev1 = g[1]->getPrev();
						int prevMove1 = g[1]->getPrevMove();
						int x1 = g[1]->getXpos();
						int y1 = g[1]->getYpos();


						if (p.getXpos() == g[1]->getXpos() && p.getYpos() == g[1]->getYpos())
						{

							count2 = 0;

							checkAnnihilated = true;

							p.setXpos(g[1]->getXpos());
							p.setYpos(g[1]->getYpos());
							arr[g[1]->getYpos()][g[1]->getXpos()] = 'P';
							g[1]->setPrev('P');
							window.setFramerateLimit(15);

							while (g[1]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[1]->setXpos(14);
							g[1]->setYpos(11);
							g[1]->setFace(arr, '%');
							checkAnnihilated = false;

							g[1]->locate(arr);

						}
						else
						{
							g[1]->frightenMode(count2, arr, p, g[1]->getFace(), x1, y1, prev1, prevMove1, checkAnnihilated, g);

							checkAnnihilated = false;
							count2++;

							window.clear();
							display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
							system("cls");
							p.displayscore();

							g[1]->setXpos(x1);
							g[1]->setYpos(y1);
						}
						if (p.getXpos() == g[1]->getXpos() && p.getYpos() == g[1]->getYpos())
						{

							count2 = 0;

							checkAnnihilated = true;

							p.setXpos(g[1]->getXpos());
							p.setYpos(g[1]->getYpos());
							arr[g[1]->getYpos()][g[1]->getXpos()] = 'P';
							g[1]->setPrev('P');
							window.setFramerateLimit(15);

							while (g[1]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[1]->setXpos(14);
							g[1]->setYpos(11);
							g[1]->setFace(arr, '%');
							checkAnnihilated = false;

							g[1]->locate(arr);

						}
						//Frightened: Pinky***************************************************************
						char prev2 = g[2]->getPrev();
						int prevMove2 = g[2]->getPrevMove();
						int x2 = g[2]->getXpos();
						int y2 = g[2]->getYpos();

						if (p.getXpos() == g[2]->getXpos() && p.getYpos() == g[2]->getYpos())
						{

							count3 = 0;

							checkAnnihilated = true;

							p.setXpos(g[2]->getXpos());
							p.setYpos(g[2]->getYpos());
							arr[g[2]->getYpos()][g[2]->getXpos()] = 'P';
							g[2]->setPrev('P');

							window.setFramerateLimit(15);

							while (g[2]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[2]->setXpos(14);
							g[2]->setYpos(11);
							g[2]->setFace(arr, '%');
							checkAnnihilated = false;

							g[2]->locate(arr);

						}
						else
						{
							g[2]->frightenMode(count3, arr, p, g[2]->getFace(), x2, y2, prev2, prevMove2, checkAnnihilated, g);// will target a tile if annihiated

							checkAnnihilated = false;
							count3++;

							window.clear();
							display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
							system("cls");
							p.displayscore();

							g[2]->setXpos(x2);
							g[2]->setYpos(y2);
						}
						if (p.getXpos() == g[2]->getXpos() && p.getYpos() == g[2]->getYpos())
						{

							count3 = 0;

							checkAnnihilated = true;

							p.setXpos(g[2]->getXpos());
							p.setYpos(g[2]->getYpos());
							arr[g[2]->getYpos()][g[2]->getXpos()] = 'P';
							g[2]->setPrev('P');

							window.setFramerateLimit(15);

							while (g[2]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[2]->setXpos(14);
							g[2]->setYpos(11);
							g[2]->setFace(arr, '%');
							checkAnnihilated = false;

							g[2]->locate(arr);

						}
						//*******************************//

						char prev3 = g[3]->getPrev();
						int prevMove3 = g[3]->getPrevMove();
						int x3 = g[3]->getXpos();
						int y3 = g[3]->getYpos();

						if (p.getXpos() == g[3]->getXpos() && p.getYpos() == g[3]->getYpos())
						{

							count4 = 0;

							checkAnnihilated = true;

							p.setXpos(g[3]->getXpos());
							p.setYpos(g[3]->getYpos());
							arr[g[3]->getYpos()][g[3]->getXpos()] = 'P';
							g[3]->setPrev('P');//new

							window.setFramerateLimit(15);

							while (g[3]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[3]->setXpos(14);
							g[3]->setYpos(11);
							g[3]->setFace(arr, '%');
							checkAnnihilated = false;

							g[3]->locate(arr);

						}
						else
						{
							g[3]->frightenMode(count4, arr, p, g[3]->getFace(), x3, y3, prev3, prevMove3, checkAnnihilated, g);// will target a tile if annihiated

							checkAnnihilated = false;
							count4++;

							window.clear();
							display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
							system("cls");
							p.displayscore();

							g[3]->setXpos(x3);
							g[3]->setYpos(y3);
						}
						if (p.getXpos() == g[3]->getXpos() && p.getYpos() == g[3]->getYpos())
						{

							count4 = 0;

							checkAnnihilated = true;

							p.setXpos(g[3]->getXpos());
							p.setYpos(g[3]->getYpos());
							arr[g[3]->getYpos()][g[3]->getXpos()] = 'P';
							g[3]->setPrev('P');//new

							window.setFramerateLimit(15);

							while (g[3]->annihilated(arr) == false)
							{
								window.clear();
								display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
								system("cls");
								p.displayscore();

							}
							window.setFramerateLimit(7);

							g[3]->setXpos(14);
							g[3]->setYpos(11);
							g[3]->setFace(arr, '%');
							checkAnnihilated = false;

							g[3]->locate(arr);

						}
						//**************************************

						if (count1 == 0 && g[0]->getFace() == '%')
							g[0]->setFace(arr, 'c');//it is still in frightened mode

						if (count2 == 0 && g[1]->getFace() == '%')
							g[1]->setFace(arr, 'b');//it is still in frightened mode

						if (count3 == 0 && g[2]->getFace() == '%')
							g[2]->setFace(arr, 'p');//it is still in frightened mode

						if (count4 == 0 && g[2]->getFace() == '%')
							g[3]->setFace(arr, 'i');//it is still in frightened mode

						window.clear();
						display(arr, s, textureSize, window, sprite);
						system("cls");
						p.displayscore();

						system("cls");

						beginT = time(NULL);

						if (difftime(beginT, endT) >= 15)//
						{
							endT = time(NULL);//clock.restart();//end and beginning will be the same
							beginT = time(NULL);
							frightened = false;

							g[0]->setFace(arr, '1');//this sets clydes face back to normal.
							g[1]->setFace(arr, '2');//this sets blinkys face back to normal.
							g[2]->setFace(arr, '3');//this sets pinkys face back to normal.
							g[3]->setFace(arr, '4');//this sets inkys face back to normal.
						}
					}



				}

				window.clear();
				display(arr, s, textureSize, window, sprite); //use display window hereeee, at the end of this function.	
				system("cls");
				p.displayscore();

				if (p.gameOver(arr) == true)
				{
					cout << "You have successfully eaten all the pellets. " << endl << "Press any key to continue. ";
					break;
				}
				if ((p.getXpos() == g[0]->getXpos() && p.getYpos() == g[0]->getYpos() && g[0]->getFace() == '1') || (p.getXpos() == g[1]->getXpos() && p.getYpos() == g[1]->getYpos() && g[1]->getFace() == '2') || (p.getXpos() == g[2]->getXpos() && p.getYpos() == g[2]->getYpos() && g[2]->getFace() == '3') || (p.getXpos() == g[3]->getXpos() && p.getYpos() == g[3]->getYpos() && g[3]->getFace() == '4'))
				{
					cout << "Ghost eats pacman. Game Over! " << endl;
					checkAlive = false;
					break;
				}
			}

			previousMove = ch2;
			const int KEY_ARROW_CHAR1 = 224;
			const int KEY_ARROW_UP = 72;
			const int KEY_ARROW_DOWN = 80;
			const int KEY_ARROW_LEFT = 75;
			const int KEY_ARROW_RIGHT = 77;

			unsigned char ch1 = _getch();

			if (ch1 == KEY_ARROW_CHAR1)
			{
				// Some Arrow key was pressed, determine which?
				ch2 = _getch();
			}
		}

		if (p.gameOver(arr) == true || checkAlive == false)
		{

			window.close();
		}
	}

	return 0;

}



void initialize(char arr[31][28])
{
	for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < 28; j++)
			arr[i][j] = ' ';
	}

	for (int i = 0; i < 28; i++)
		arr[0][i] = '*';
	for (int i = 0; i < 28; i++)
		arr[30][i] = '*';

	for (int i = 0; i < 30; i++)
	{
		if (i != 12 && i != 10 && i != 11 && i != 14 && i != 16 && i != 17 && i != 18)
			arr[i][0] = '*';
	}
	for (int i = 0; i < 30; i++)
	{
		if (i != 12 && i != 10 && i != 11 && i != 14 && i != 16 && i != 17 && i != 18)
			arr[i][27] = '*';

	}
	for (int i = 2; i <= 4; i++)
	{
		for (int j = 2; j <= 5; j++)
			arr[i][j] = '*';
		for (int j = 16; j <= 20; j++)
			arr[i][j] = '*';
		for (int j = 7; j <= 11; j++)
			arr[i][j] = '*';
		for (int j = 22; j <= 25; j++)
			arr[i][j] = '*';
	}
	for (int i = 0; i <= 4; i++)
	{
		arr[i][13] = '*';
		arr[i][14] = '*';
	}

	for (int i = 9; i <= 13; i++)
	{
		arr[i][5] = '*';
		arr[i][22] = '*';
		arr[i][7] = '*';
		arr[i][8] = '*';
		arr[i][19] = '*';
		arr[i][20] = '*';
	}

	for (int i = 6; i <= 7; i++)
	{
		for (int j = 2; j <= 5; j++)
			arr[i][j] = '*';
		for (int j = 22; j <= 25; j++)
			arr[i][j] = '*';
		for (int j = 7; j <= 8; j++)
			arr[i][j] = '*';
		for (int j = 10; j <= 17; j++)
			arr[i][j] = '*';
		for (int j = 19; j <= 20; j++)
			arr[i][j] = '*';
	}
	for (int i = 0; i <= 5; i++)
	{
		arr[9][i] = '*';
		arr[13][i] = '*';
		arr[15][i] = '*';
		arr[19][i] = '*';
	}
	for (int i = 18; i <= 19; i++)
		for (int j = 10; j <= 17; j++)
			arr[i][j] = '*';

	for (int i = 22; i <= 27; i++)
	{
		arr[9][i] = '*';
		arr[13][i] = '*';
		arr[15][i] = '*';
		arr[19][i] = '*';
	}
	for (int j = 9; j <= 10; j++)
	{

		for (int i = 7; i <= 11; i++)
			arr[j][i] = '*';
		for (int i = 13; i <= 14; i++)
			arr[j][i] = '*';
		for (int i = 16; i <= 20; i++)
			arr[j][i] = '*';

	}
	for (int i = 15; i <= 19; i++)
	{
		for (int j = 7; j <= 8; j++)
			arr[i][j] = '*';
		arr[i][19] = '*';
		arr[i][20] = '*';
		arr[i][5] = '*';
		arr[i][22] = '*';
	}

	for (int i = 19; i <= 20; i++)
	{
		arr[8][i] = '*';
		arr[26][i] = '*';
		arr[25][i] = '*';
		arr[24][i] = '*';
	}

	for (int i = 7; i <= 8; i++)
	{
		arr[8][i] = '*';
		arr[26][i] = '*';
	}

	for (int i = 13; i <= 14; i++)
	{
		arr[8][i] = '*';
		arr[26][i] = '*';
	}

	for (int i = 12; i <= 16; i++)
	{

		for (int j = 10; j <= 17; j++)
		{
			if (j == 10 || j == 17)
				arr[i][j] = '*';
			if (i == 12 || i == 16)
				arr[i][j] = '*';
		}
	}

	for (int i = 20; i <= 22; i++)
		for (int j = 13; j <= 14; j++)
			arr[i][j] = '*';

	for (int i = 21; i <= 22; i++)
	{
		for (int j = 2; j <= 5; j++)
			arr[i][j] = '*';

		for (int j = 7; j <= 11; j++)
			arr[i][j] = '*';

		for (int j = 16; j <= 20; j++)
			arr[i][j] = '*';

		for (int j = 22; j <= 25; j++)
			arr[i][j] = '*';
	}


	arr[23][4] = '*';
	arr[23][5] = '*';
	arr[23][22] = '*';
	arr[23][23] = '*';

	for (int i = 24; i <= 25; i++)
	{
		for (int j = 0; j <= 2; j++)
			arr[i][j] = '*';
		for (int j = 4; j <= 5; j++)
			arr[i][j] = '*';
		for (int j = 7; j <= 8; j++)
			arr[i][j] = '*';
		for (int j = 10; j <= 17; j++)
			arr[i][j] = '*';
		for (int j = 22; j <= 23; j++)
			arr[i][j] = '*';
		for (int j = 25; j <= 27; j++)
			arr[i][j] = '*';
	}
	for (int i = 27; i <= 28; i++)
	{
		for (int j = 2; j <= 11; j++)
			arr[i][j] = '*';
		for (int j = 13; j <= 14; j++)
			arr[i][j] = '*';
		for (int j = 16; j <= 25; j++)
			arr[i][j] = '*';
	}



	for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			if (((i >= 0 && i <= 8) || (i >= 20 && i <= 29)) && arr[i][j] != '*')
				arr[i][j] = '`';
		}
	}
	for (int i = 9; i <= 19; i++)
	{
		arr[i][6] = '`';
		arr[i][21] = '`';
	}
	arr[2][1] = '@';
	arr[2][26] = '@';
	arr[23][1] = '@';
	arr[23][26] = '@';

}
void display(char arr[31][28], Sprite& s, Vector2u& textureSize, RenderWindow& window, Sprite sprite)
{
	window.draw(sprite);
	for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			if (arr[i][j] == '%')
			{
				//draw eyes
				s.setTextureRect(IntRect(textureSize.x * 7, textureSize.y * 0.2, textureSize.x, textureSize.y));
				s.setScale(0.15f, 0.15f); //added this so that larger sprites can be fitted into the screen

				//IMPORTANT//
				s.setPosition(sf::Vector2f(j * 10, i * 10));//extra

				window.draw(s);

			}
			if (arr[i][j] == 'P')
			{

				s.setTextureRect(IntRect(textureSize.x * 0, textureSize.y * 0, textureSize.x, textureSize.y));
				s.setScale(0.15f, 0.15f);

				//IMPORTANT//
				s.setPosition(sf::Vector2f(j * 10, i * 10));//extra

				window.draw(s);

			}
			if (arr[i][j] == '`')
			{
				s.setTextureRect(IntRect(textureSize.x * 2.5, textureSize.y * 4.5, textureSize.x * 0.25, textureSize.y * 0.25)); //the size of these pallets was optimized with the sprite that was available//depends on the sprites 
				s.setScale(0.3f, 0.3f);
				//IMPORTANT//
				s.setPosition(sf::Vector2f(j * 10, i * 10));//extra


				window.draw(s);

			}
			if (arr[i][j] == '@')
			{
				s.setTextureRect(IntRect(textureSize.x * 4.4, textureSize.y * 4.35, textureSize.x * 0.5, textureSize.y * 0.5));
				s.setScale(0.3f, 0.3f); //added this so that larger sprites can be fitted into the screen

				//IMPORTANT//
				s.setPosition(sf::Vector2f(j * 10, i * 10));//extra

				window.draw(s);

			}
			if (arr[i][j] == 'c' || arr[i][j] == 'b' || arr[i][j] == 'p' || arr[i][j] == 'i')//letters crrespond to frightenedmode
			{
				s.setTextureRect(IntRect(textureSize.x * 6.0, textureSize.y * 0.2, textureSize.x, textureSize.y));
				s.setScale(0.15f, 0.15f); //added this so that larger sprites can be fitted into the screen

				//IMPORTANT//
				s.setPosition(sf::Vector2f(j * 10, i * 10));//extra

				window.draw(s);
			}
			if (arr[i][j] == '1') //Clyde
			{
				s.setTextureRect(IntRect(textureSize.x * 2.2, textureSize.y * 0.2, textureSize.x, textureSize.y));
				s.setScale(0.15f, 0.15f); //added this so that larger sprites can be fitted into the screen

				//IMPORTANT//
				s.setPosition(sf::Vector2f(j * 10, i * 10));//extra

				window.draw(s);
			}

			if (arr[i][j] == '2')//Blinky
			{
				s.setTextureRect(IntRect(textureSize.x * 5.2, textureSize.y * 0.2, textureSize.x, textureSize.y));
				s.setScale(0.15f, 0.15f); //added this so that larger sprites can be fitted into the screen

				//IMPORTANT//
				s.setPosition(sf::Vector2f(j * 10, i * 10));//extra

				window.draw(s);
			}

			if (arr[i][j] == '3')//Pinky
			{
				s.setTextureRect(IntRect(textureSize.x * 4.2, textureSize.y * 0.2, textureSize.x * 0.8, textureSize.y));
				s.setScale(0.15f, 0.15f); //added this so that larger sprites can be fitted into the screen

				//IMPORTANT//
				s.setPosition(sf::Vector2f(j * 10, i * 10));//extra

				window.draw(s);

			}

			if (arr[i][j] == '4')//Inky
			{
				s.setTextureRect(IntRect(textureSize.x * 3.2, textureSize.y * 0.2, textureSize.x * 0.8, textureSize.y));
				s.setScale(0.15f, 0.15f); //added this so that larger sprites can be fitted into the screen

				//IMPORTANT//
				s.setPosition(sf::Vector2f(j * 10, i * 10));//extra

				window.draw(s);

			}
		}
	}


	window.display();
}
