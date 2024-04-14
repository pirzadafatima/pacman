#include "Header.h"

#include <cmath>
#include <conio.h>
#include <Windows.h>
#include <iostream>
using namespace std;


void Ghost::frightenMode(int count, char arr[31][28], pacman p, int face, int& xPos, int& yPos, char& prev, int& prevMove, bool check, Ghost* g[4])//x and y are ghosts positions
{
	int up = 0;
	int left = 1;
	int down = 2;
	int right = 3;


	arr[yPos][xPos] = face;

	//target was said to be pseudorandom.
	int y = rand() % 31;
	int x = rand() % 28;


	if (prev == '2' || prev == 'b')
	{
		prev = g[1]->getPrev();
	}
	if (prev == '4' || prev == 'i')
	{
		prev = g[3]->getPrev();
	}
	if (prev == '3' || prev == 'p')
	{
		prev = g[2]->getPrev();
	}
	if (prev == '1' || prev == 'c')
	{
		prev = g[0]->getPrev();
	}

	while (arr[y][x] == '*')
	{
		y = rand() % 31;
		x = rand() % 28;
	}


	int shortest = target(arr, x, y, xPos, yPos, prevMove);//it will move towards the targetted tile.
	while (((shortest == up && arr[yPos - 1][xPos] == '*') || (shortest == down && arr[yPos + 1][xPos] == '*') || (shortest == left && arr[yPos][xPos - 1] == '*') || (shortest == right && arr[yPos][xPos + 1] == '*')) && (arr[yPos - 1][xPos] == '*' && (xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13) && (xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
	{
		shortest = target(arr, x, y, xPos, yPos, prev);

	}



	if (shortest == up && arr[yPos - 1][xPos] != '*' || shortest == down && arr[yPos + 1][xPos] != '*' || shortest == left && arr[yPos][xPos - 1] != '*' || shortest == right && arr[yPos][xPos + 1] != '*')
	{
		if (shortest == up)
		{
			arr[yPos][xPos] = prev;
			prev = arr[yPos - 1][xPos];
			arr[yPos - 1][xPos] = face;
			yPos--;
		}

		else
			if (shortest == left)
			{
				arr[yPos][xPos] = prev;
				prev = arr[yPos][xPos - 1];
				arr[yPos][xPos - 1] = face;
				xPos--;
			}
			else
				if (shortest == down)
				{
					arr[yPos][xPos] = prev;
					prev = arr[yPos + 1][xPos];
					arr[yPos + 1][xPos] = face;
					yPos++;
				}
				else
					if (shortest == right)
					{
						arr[yPos][xPos] = prev;
						prev = arr[yPos][xPos + 1];
						arr[yPos][xPos + 1] = face;
						xPos++;
					}

		prevMove = shortest;

	}

	setPrev(prev);
}

int Ghost::target(char arr[31][28], int tx, int ty, int xPos, int yPos, int pMove)
{
	int up = 0;
	int left = 1;
	int down = 2;
	int right = 3;

	int temp[4];

	temp[0] = sqrt(pow(((yPos - 1) - ty), 2) + pow((xPos - tx), 2));//up
	temp[1] = sqrt(pow((yPos - ty), 2) + pow((xPos - 1 - tx), 2));//left
	temp[2] = sqrt(pow((yPos + 1 - ty), 2) + pow((xPos - tx), 2));//down
	temp[3] = sqrt(pow((yPos - ty), 2) + pow((xPos + 1 - tx), 2));//right


	if (xPos == 27 && yPos == 14)
		pMove = left;
	if (xPos == 0 && yPos == 14)
		pMove = right;

	int shortest = temp[0];

	int loc[4] = { 0, -1, -1, -1 };

	for (int i = 1; i < 4; i++)
	{
		if (shortest > temp[i])
		{
			shortest = temp[i];
			loc[0] = i;
		}
	}

	int shortest2 = 100000;
	int count = 0;

	for (int i = 0; i < 4; i++)
	{
		bool x = true;
		if (shortest == temp[i])
		{
			int j = 0;
			for (j = 0; j < 4; j++)
			{
				if (shortest == temp[j])
				{
					count++;
					if (count > 1)
						loc[1] = j;
				}
			}
			if (count > 1)
			{
				shortest2 = shortest;
				x = false;
			}
		}

		if (x == false)
			break;
		if (shortest2 > temp[i] && temp[i] > shortest && x == true)
		{
			shortest2 = temp[i];
			loc[1] = i;
		}
	}


	int shortest3 = 100000;
	count = 0;
	for (int i = 0; i < 4; i++)
	{

		bool x = true;
		if (shortest2 == temp[i] && loc[0] != i)
		{
			int count = 0;
			for (int j = 0; j < 4; j++)
			{
				if (shortest2 == temp[j] && loc[0] != j)
				{
					count++;
					if (count > 1)
						loc[2] = j;
				}

			}
			if (count > 1)
			{
				shortest3 = shortest2;
				x = false;
			}
		}

		if (x == false)
			break;
		if (shortest3 > temp[i] && temp[i] > shortest2 && x == true)
		{
			shortest3 = temp[i];
			loc[2] = i;
		}
	}


	int shortest4 = 100000;

	count = 0;
	for (int i = 0; i < 4; i++)
	{

		bool x = true;
		if (shortest3 == temp[i])
		{

			int count = 0;
			for (int j = 0; j < 4; j++)
			{
				if (shortest3 == temp[j] && loc[0] != j && loc[1] != j)
				{
					count++;
					if (count > 1)
						loc[3] = j;
				}
			}
			if (count > 1)
			{
				shortest4 = shortest3;
				x = false;
			}
		}

		if (x == false)
			break;
		if (shortest4 > temp[i] && temp[i] > shortest3 && x == true)
		{
			shortest4 = temp[i];
			loc[3] = i;
		}

	}



	if (pMove == up)//up
	{
		if (loc[0] == 0) //if the shortest1 distance was up
		{
			if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
			{

				if (loc[1] == 1 || (loc[2] == 1 && loc[1] == 2))//left
				{
					if (arr[yPos][xPos - 1] == '*')
					{

						if (loc[2] == 3 || (loc[3] == 3 && loc[2] == 2))//right 
						{
							if (arr[yPos][xPos + 1] == '*')
							{

							}
							else
								return right;


						}
					}
					else
						return left;

				}
				else
					if (loc[1] == 3 || (loc[2] == 3 && loc[1] == 2))//right
					{
						if (arr[yPos][xPos + 1] == '*')
						{
							if (loc[2] == 1 || (loc[3] == 1 && loc[2] == 2))//left
							{
								if (arr[yPos][xPos - 1] == '*')
								{

								}
								else
									return left;
							}


						}
						else
							return right;

					}

			}
			else
			{
				return up;
			}
		}
		else
			if (loc[0] == 1) //if the shortest1 distance was ////LEFT
			{
				if (arr[yPos][xPos - 1] == '*')//if shortest1 is left then the precedence of left is more than up
				{
					if (loc[1] == 0 || (loc[2] == 0 && loc[1] == 2))//up ------- 2nd condition checks if 2nd shortest distance is down then it prefers shortest3 because it cant turn 180 degree
					{
						if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
						{

							if ((loc[3] == 3 && loc[2] == 2) || loc[2] == 3)//right 
							{
								if (arr[yPos][xPos + 1] == '*')
								{

								}
								else
									return right;

							}
						}
						else
							return up;

					}
					else
						if (loc[1] == 3 || (loc[2] == 3 && loc[1] == 2))//right
						{
							if (arr[yPos][xPos + 1] == '*')
							{
								if (loc[2] == 0 || (loc[3] == 0 && loc[2] == 2))//up
								{
									if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
									{

									}
									else
										return up;
								}
							}
							else
								return right;
						}
				}
				else
				{
					return left;
				}
			}
			else
				if (loc[0] == 3) //if the shortest1 distance was ////right
				{
					if (arr[yPos][xPos + 1] == '*')
					{
						if (loc[1] == 0 || (loc[2] == 0 && loc[1] == 2))//up
						{
							if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
							{
								if (loc[2] == 1 || (loc[3] == 1 && loc[2] == 2))//left 
								{
									if (arr[yPos][xPos - 1] == '*')
									{

									}
									else
										return left;

								}
							}
							else
								return up;

						}
						else
							if (loc[1] == 1 || (loc[2] == 1 && loc[1] == 2))//left
							{
								if (arr[yPos][xPos - 1] == '*')
								{
									if (loc[2] == 0 || (loc[3] == 0 && loc[2] == 2))//up
									{
										if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
										{

										}
										else
											return up;
									}


								}
								else
									return left;
							}

					}
					else
						return right;
				}
				else
					if (loc[0] == 2)//down
					{
						if (loc[1] == 0)//up
						{
							if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
							{

								if (loc[2] == 1)//left 
								{
									if (arr[yPos][xPos - 1] == '*')
									{
										if (loc[3] == 3)//right
										{
											if (arr[yPos][xPos + 1] == '*')
											{
											}
											else
												return right;

										}
									}
									else
										return left;


								}
								else
									if (loc[2] == 3)//right /
									{
										if (arr[yPos][xPos + 1] == '*')
										{

											if (loc[3] == 1)//left
											{
												if (arr[yPos][xPos - 1] == '*')
												{
												}
												else
													return left;

											}
										}
										else
											return right;
									}
							}
							else
								return up;

						}
						else
							if (loc[1] == 1)//left
							{
								if (arr[yPos][xPos - 1] == '*')
								{
									if (loc[2] == 0)//up
									{
										if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
										{
											if (loc[3] == 3)//right
											{
												if (arr[yPos][xPos + 1] == '*')
												{
												}
												else
													return right;
											}
										}
										else
											return up;
									}
									else
										if (loc[2] == 3)//right
										{
											if (arr[yPos][xPos + 1] == '*')
											{
												if (loc[3] == 0)//up
												{
													if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
													{
													}
													else
														return up;
												}
											}
											else
												return right;
										}

								}
								else
									return left;
							}
							else
								if (loc[1] == 3)
								{
									if (arr[yPos][xPos + 1] == '*')
									{
										if (loc[2] == 0)//up
										{
											if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
											{
												if (loc[3] == 1)//left
												{
													if (arr[yPos][xPos - 1] == '*')
													{
													}
													else
														return left;
												}
											}
											else
												return up;
										}
										else
											if (loc[2] == 1)//left
											{
												if (arr[yPos][xPos - 1] == '*')
												{
													if (loc[3] == 0)//up
													{
														if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
														{
														}
														else
															return up;
													}
												}
												else
													return left;
											}

									}
									else
										return right;
								}

					}
	}
	else
		if (pMove == down)//down
		{
			if (loc[0] == 2) //if the shortest1 distance was down
			{
				if (arr[yPos + 1][xPos] == '*')
				{
					if (loc[1] == 1 || (loc[2] == 1 && loc[1] == 0))//left
					{
						if (arr[yPos][xPos - 1] == '*')
						{

							if (loc[2] == 3 || (loc[3] == 3 && loc[2] == 0))//right 
							{
								if (arr[yPos][xPos + 1] == '*')
								{

								}
								else
									return right;
							}
						}
						else
							return left;

					}
					else
						if (loc[1] == 3 || (loc[2] == 3 && loc[1] == 0))//right
						{
							if (arr[yPos][xPos + 1] == '*')
							{
								if (loc[2] == 1 || (loc[2] == 0 && loc[3] == 1))//left
								{
									if (arr[yPos][xPos - 1] == '*')
									{

									}
									else
										return left;
								}
							}
							else
								return right;
						}
				}
				else
				{
					return down;
				}
			}
			else
				if (loc[0] == 1) //if the shortest1 distance was ////LEFT
				{
					if (arr[yPos][xPos - 1] == '*')//if shortest1 is left then the precedence of left is more than up
					{
						if (loc[1] == 2 || (loc[2] == 2 && loc[1] == 0))//down
						{
							if (arr[yPos + 1][xPos] == '*')
							{

								if (loc[2] == 3 || (loc[3] == 3 && loc[2] == 0))//right 
								{
									if (arr[yPos][xPos + 1] == '*')
									{

									}
									else
										return right;
								}
							}
							else
								return down;
						}
						else
							if (loc[1] == 3 || (loc[2] == 3 && loc[1] == 0))//right
							{
								if (arr[yPos][xPos + 1] == '*')
								{
									if (loc[2] == 2 || (loc[3] == 2 && loc[2] == 0))//down
									{
										if (arr[yPos + 1][xPos] == '*')
										{

										}
										else
											return down;
									}
								}
								else
									return right;
							}
					}
					else
					{
						return left;
					}
				}
				else
					if (loc[0] == 3) //if the shortest1 distance was ////right
					{
						if (arr[yPos][xPos + 1] == '*')
						{
							if (loc[1] == 2 || (loc[2] == 2 && loc[1] == 0))//down
							{
								if (arr[yPos + 1][xPos] == '*')
								{
									if (loc[2] == 1 || (loc[3] == 1 && loc[2] == 0))//left 
									{
										if (arr[yPos][xPos - 1] == '*')
										{

										}
										else
											return left;
									}
								}
								else
									return down;

							}
							else
								if (loc[1] == 1 || (loc[2] == 1 && loc[1] == 0))//left
								{
									if (arr[yPos][xPos - 1] == '*')
									{
										if (loc[2] == 2 && (loc[2] == 0 || loc[3] == 2))//down
										{
											if (arr[yPos + 1][xPos] == '*')
											{
											}
											else
												return down;
										}
									}
									else
										return left;
								}

						}
						else
							return right;
					}
					else
						if (loc[0] == 0)//up
						{

							if (loc[1] == 2)//down
							{
								if (arr[yPos + 1][xPos] == '*')
								{

									if (loc[2] == 1)//left
									{
										if (arr[yPos][xPos - 1] == '*')
										{

											if (loc[3] == 3)//right
											{
												if (arr[yPos][xPos + 1] == '*')
												{
												}
												else
													return right;

											}
										}
										else
											return left;


									}
									else
										if (loc[2] == 3)//left 
										{
											if (arr[yPos][xPos + 1] == '*')
											{

												if (loc[3] == 1)//right
												{
													if (arr[yPos][xPos - 1] == '*')
													{
													}
													else
														return left;

												}
											}
											else
												return right;
										}
								}
								else
									return down;

							}
							else
								if (loc[1] == 1)//left
								{
									if (arr[yPos][xPos - 1] == '*')
									{
										if (loc[2] == 2)//down
										{
											if (arr[yPos + 1][xPos] == '*')
											{
												if (loc[3] == 3)//right
												{
													if (arr[yPos][xPos + 1] == '*')
													{
													}
													else
														return right;
												}
											}
											else
												return down;
										}
										else
											if (loc[2] == 3)//right
											{
												if (arr[yPos][xPos + 1] == '*')
												{
													if (loc[3] == 2)//down
													{
														if (arr[yPos + 1][xPos] == '*')
														{
														}
														else
															return down;
													}
												}
												else
													return right;
											}

									}
									else
										return left;
								}
								else
									if (loc[1] == 3)
									{
										if (arr[yPos][xPos + 1] == '*')
										{
											if (loc[2] == 2)//down
											{
												if (arr[yPos + 1][xPos] == '*')
												{
													if (loc[3] == 1)//left
													{
														if (arr[yPos][xPos - 1] == '*')
														{
														}
														else
															return left;
													}
												}
												else
													return down;
											}
											else
												if (loc[2] == 1)//left
												{
													if (arr[yPos][xPos - 1] == '*')
													{
														if (loc[3] == 2)//down
														{
															if (arr[yPos + 1][xPos] == '*')
															{
															}
															else
																return down;
														}
													}
													else
														return left;
												}

										}
										else
											return right;
									}
						}
		}
		else
			if (pMove == left)//left
			{

				if (loc[0] == 1) //if the shortest1 distance was left
				{
					if (arr[yPos][xPos - 1] == '*')
					{
						if (loc[1] == 0 || (loc[2] == 0 && loc[1] == 3))//up
						{
							if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
							{

								if (loc[2] == 2 || (loc[2] == 3 && loc[3] == 2))//down 
								{
									if (arr[yPos + 1][xPos] == '*')
									{

									}
									else
										return down;
								}
							}
							else
								return up;

						}
						else
							if (loc[1] == 2 || (loc[2] == 2 && loc[1] == 3))//down
							{
								if (arr[yPos + 1][xPos] == '*')
								{
									if (loc[2] == 0 || (loc[3] == 0 && loc[2] == 3))//up
									{
										if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
										{

										}
										else
											return up;
									}
								}
								else
									return down;
							}

					}
					else
					{
						return left;
					}
				}
				else
					if (loc[0] == 2) //if the shortest1 distance was ////down
					{
						if (arr[yPos + 1][xPos] == '*')//if shortest1 is left then the precedence of left is more than up
						{
							if (loc[1] == 1 || (loc[2] == 1 && loc[1] == 3))//left
							{
								if (arr[yPos][xPos - 1] == '*')
								{

									if ((loc[3] == 0 && loc[2] == 3) || loc[2] == 0)//up 
									{
										if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
										{

										}
										else
											return up;
									}
								}
								else
									return left;

							}
							else
								if (loc[1] == 0 || (loc[2] == 0 && loc[1] == 3))//up
								{
									if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
									{
										if ((loc[3] == 1 && loc[2] == 3) || loc[2] == 1 || loc[2] == 0)//left
										{
											if (arr[yPos][xPos - 1] == '*')
											{
											}
											else
												return left;
										}
									}
									else
										return up;
								}

						}
						else
						{
							return down;
						}
					}
					else
						if (loc[0] == 0) //if the shortest1 distance was ////up
						{
							if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
							{
								if (loc[1] == 1 || (loc[2] == 1 && loc[1] == 3))//left
								{
									if (arr[yPos][xPos - 1] == '*')
									{
										if (loc[2] == 2 || (loc[2] == 3 && loc[3] == 2))//down 
										{
											if (arr[yPos + 1][xPos] == '*')
											{

											}
											else
												return down;
										}
									}
									else
										return left;

								}
								else
									if (loc[1] == 2 || (loc[2] == 2 && loc[1] == 3))//down
									{
										if (arr[yPos - 1][xPos] == '*')
										{
											if (loc[2] == 1 || (loc[3] == 1 && loc[2] == 3))//left
											{
												if (arr[yPos][xPos - 1] == '*')
												{

												}
												else
													return left;
											}
										}
										else
											return down;
									}


							}
							else
								return up;
						}
						else
							if (loc[0] == 3)//right
							{

								if (loc[1] == 2)//down
								{
									if (arr[yPos + 1][xPos] == '*')
									{

										if (loc[2] == 1)//left
										{
											if (arr[yPos][xPos - 1] == '*')
											{

												if (loc[3] == 0)//up
												{
													if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
													{
													}
													else
														return up;

												}
											}
											else
												return left;


										}
										else
											if (loc[2] == 0)//up 
											{
												if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
												{

													if (loc[3] == 1)//left
													{
														if (arr[yPos][xPos - 1] == '*')
														{
														}
														else
															return left;

													}
												}
												else
													return up;
											}
									}
									else
										return down;

								}
								else
									if (loc[1] == 1)//left
									{
										if (arr[yPos][xPos - 1] == '*')
										{
											if (loc[2] == 2)//down
											{
												if (arr[yPos + 1][xPos] == '*')
												{
													if (loc[3] == 0)//up
													{
														if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
														{
														}
														else
															return up;
													}
												}
												else
													return down;
											}
											else
												if (loc[2] == 0)//up
												{
													if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
													{
														if (loc[3] == 2)//down
														{
															if (arr[yPos + 1][xPos] == '*')
															{
															}
															else
																return down;
														}
													}
													else
														return up;
												}

										}
										else
											return left;
									}
									else
										if (loc[1] == 0)
										{
											if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12))) //up
											{
												if (loc[2] == 2)//down
												{
													if (arr[yPos + 1][xPos] == '*')
													{
														if (loc[3] == 1)//left
														{
															if (arr[yPos][xPos - 1] == '*')
															{
															}
															else
																return left;
														}
													}
													else
														return down;
												}
												else
													if (loc[2] == 1)//left
													{
														if (arr[yPos][xPos - 1] == '*')
														{
															if (loc[3] == 2)//down
															{
																if (arr[yPos + 1][xPos] == '*')
																{
																}
																else
																	return down;
															}
														}
														else
															return left;
													}

											}
											else
												return up;
										}
							}
			}

			else
				if (pMove == right)//right
				{

					if (loc[0] == 3) //if the shortest1 distance was right
					{
						if (arr[yPos][xPos + 1] == '*')
						{
							if (loc[1] == 0 || (loc[2] == 0 && loc[1] == 1))//up
							{
								if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
								{

									if (loc[2] == 2 || (loc[3] == 2 && loc[2] == 1))//down 
									{
										if (arr[yPos + 1][xPos] == '*')
										{

										}
										else
											return down;
									}
								}
								else
									return up;

							}
							else
								if (loc[1] == 2 || (loc[2] == 2 && loc[1] == 1))//down
								{
									if (arr[yPos + 1][xPos] == '*')
									{
										if (loc[2] == 0 || (loc[3] == 0 && loc[2] == 1))//up
										{
											if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
											{

											}
											else
												return up;
										}
									}
									else
										return down;
								}

						}
						else
						{
							return right;
						}
					}
					else
						if (loc[0] == 2) //if the shortest1 distance was ////down
						{
							if (arr[yPos + 1][xPos] == '*')//if shortest1 is left then the precedence of left is more than up
							{
								if (loc[1] == 3 || (loc[2] == 3 && loc[1] == 1))//right
								{
									if (arr[yPos][xPos + 1] == '*')
									{

										if (loc[2] == 0 || (loc[3] == 0 && loc[2] == 1))//up 
										{
											if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
											{

											}
											else
												return up;
										}
									}
									else
										return right;
								}
								else
									if (loc[1] == 0 || (loc[2] == 0 && loc[1] == 1))//up
									{
										if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
										{
											if (loc[2] == 3 || (loc[3] == 3 && loc[2] == 1))//right
											{
												if (arr[yPos][xPos + 1] == '*')
												{

												}
												else
													return right;
											}
										}
										else
											return up;
									}

							}
							else
							{
								return down;
							}
						}
						else
							if (loc[0] == 0) //if the shortest1 distance was ////up
							{
								if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
								{
									if (loc[1] == 3 || (loc[2] == 3 && loc[1] == 1))//right
									{
										if (arr[yPos][xPos + 1] == '*')
										{

											if ((loc[3] == 2 && loc[2] == 1) || loc[2] == 2)//down 
											{
												if (arr[yPos + 1][xPos] == '*')
												{

												}
												else
													return down;


											}
										}
										else
											return right;

									}
									else
										if (loc[1] == 2 || (loc[2] == 2 && loc[1] == 1))//down
										{
											if (arr[yPos - 1][xPos] == '*')
											{
												if (loc[2] == 3 || (loc[3] == 3 && loc[2] == 1))//right
												{
													if (arr[yPos][xPos + 1] == '*')
													{

													}
												}
												else
													return right;
											}


										}
										else
											return down;


								}
								else
									return up;
							}
							else
								if (loc[0] == 1)//left
								{


									if (loc[1] == 3)//right
									{
										if (arr[yPos][xPos + 1] == '*')
										{

											if (loc[2] == 2)//down 
											{
												if (arr[yPos - 1][xPos] == '*')
												{

													if (loc[3] == 0)//up
													{
														if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
														{
														}
														else
															return up;

													}
												}
												else
													return down;


											}
											else
												if (loc[2] == 0)//up ///if shortest3 or 4 is right and not a wall then move else take a 180 turn
												{
													if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
													{

														if (loc[3] == 1)//left
														{
															if (arr[yPos - 1][xPos] == '*')
															{
															}
															else
																return down;

														}
													}
													else
														return up;
												}
										}
										else
											return right;

									}
									else
										if (loc[1] == 2)//down
										{
											if (arr[yPos + 1][xPos] == '*')
											{
												if (loc[2] == 3)//right
												{
													if (arr[yPos][xPos + 1] == '*')
													{
														if (loc[3] == 0)//up
														{
															if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
															{
															}
															else
																return up;
														}
													}
													else
														return right;
												}
												else
													if (loc[2] == 0)//up
													{
														if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12)))
														{
															if (loc[3] == 3)//down
															{
																if (arr[yPos][xPos + 1] == '*')
																{
																}
																else
																	return right;
															}
														}
														else
															return up;
													}

											}
											else
												return down;
										}
										else
											if (loc[1] == 0)
											{
												if (arr[yPos - 1][xPos] == '*' && ((xPos != 14 || yPos != 13) && (xPos != 13 || yPos != 13)) && ((xPos != 14 || yPos != 12) && (xPos != 13 || yPos != 12))) //up
												{
													if (loc[2] == 2)//down
													{
														if (arr[yPos + 1][xPos] == '*')
														{
															if (loc[3] == 3)//right
															{
																if (arr[yPos][xPos + 1] == '*')
																{
																}
																else
																	return right;
															}
														}
														else
															return down;
													}
													else
														if (loc[2] == 3)//right
														{
															if (arr[yPos][xPos + 1] == '*')
															{
																if (loc[3] == 2)//down
																{
																	if (arr[yPos + 1][xPos] == '*')
																	{
																	}
																	else
																		return down;
																}
															}
															else
																return right;
														}

												}
												else
													return up;
											}

								}
				}

}



//////////////////////////////////////

void Blinky::setFace(char arr[31][28], char x)
{
	blinky = x;
}
int Blinky::getXpos()
{
	return xPos;
}
int Blinky::getPrevMove()
{
	return prevMove;
}
char Blinky::getPrev()
{
	return prev;
}
int Blinky::getYpos()
{
	return yPos;
}

void Blinky::setPrevMove(int move)
{
	prevMove = move;
}
void Blinky::setPrev(char x)
{
	prev = x;
}
int Blinky::getFace()
{
	return blinky;
}

void Blinky::setXpos(int x)
{
	xPos = x;
}
void Blinky::setYpos(int y)
{
	yPos = y;
}
Blinky::~Blinky()
{}
Blinky::Blinky()
{
	blinky = '2';
	xPos = 14;
	yPos = 11;
	prev = ' ';
	prevMove = 1;
}

void Blinky::locate(char arr[31][28])
{
	arr[yPos][xPos] = blinky;
}

void Blinky::move(char arr[31][28], int shortest, Ghost* g[4])
{
	int up = 0;
	int left = 1;
	int down = 2;
	int right = 3;

	if (prev == '1' || prev == 'c')
	{
		prev = g[0]->getPrev();
	}
	if (prev == '4' || prev == 'i')
	{
		prev = g[3]->getPrev();
	}
	if (prev == '3' || prev == 'p')
	{
		prev = g[2]->getPrev();
	}

	if (shortest == up && arr[yPos - 1][xPos] != '*' || shortest == down && arr[yPos + 1][xPos] != '*' || shortest == left && arr[yPos][xPos - 1] != '*' || shortest == right && arr[yPos][xPos + 1] != '*')
	{
		if (shortest == up)
		{
			arr[yPos][xPos] = prev;
			prev = arr[yPos - 1][xPos];
			arr[yPos - 1][xPos] = blinky;
			yPos--;
		}

		else
			if (shortest == left)
			{
				arr[yPos][xPos] = prev;
				prev = arr[yPos][xPos - 1];
				arr[yPos][xPos - 1] = blinky;
				xPos--;
			}
			else
				if (shortest == down)
				{
					arr[yPos][xPos] = prev;
					prev = arr[yPos + 1][xPos];
					arr[yPos + 1][xPos] = blinky;
					yPos++;
				}
				else
					if (shortest == right)
					{
						arr[yPos][xPos] = prev;
						prev = arr[yPos][xPos + 1];
						arr[yPos][xPos + 1] = blinky;
						xPos++;
					}

		prevMove = shortest;
	}
}

void Blinky::chaseMode(char arr[31][28], pacman p, Ghost* g[4])
{
	int pacmanx = p.getXpos();
	int pacmany = p.getYpos();
	bool check = true;
	int shortest = target(arr, pacmanx, pacmany, xPos, yPos, prevMove);

	move(arr, shortest, g);

}

void Blinky::scatterMode(char arr[31][28], Ghost* g[4])
{

	int up = 0;
	int left = 1;
	int down = 2;
	int right = 3;
	bool check = true;
	int shortest = target(arr, 27, 0, xPos, yPos, prevMove);//it will move towards the targetted tile.
	while ((shortest == up && arr[yPos - 1][xPos] == '*') || (shortest == down && arr[yPos + 1][xPos] == '*') || (shortest == left && arr[yPos][xPos - 1] == '*') || (shortest == right && arr[yPos][xPos + 1] == '*'))
	{
		shortest = target(arr, 27, 0, xPos, yPos, prevMove);
	}


	move(arr, shortest, g);
}

bool Blinky::annihilated(char arr[31][28])
{
	int up = 0;
	int left = 1;
	int down = 2;
	int right = 3;

	int x = 14;
	int y = 11;
	bool check = true;
	int shortest = target(arr, x, y, xPos, yPos, prevMove);//it will move towards the targetted tile.
	while ((shortest == up && arr[yPos - 1][xPos] == '*') || (shortest == down && arr[yPos + 1][xPos] == '*') || (shortest == left && arr[yPos][xPos - 1] == '*') || (shortest == right && arr[yPos][xPos + 1] == '*'))
	{
		shortest = target(arr, x, y, xPos, yPos, prevMove);
	}


	if (shortest == up && arr[yPos - 1][xPos] != '*' || shortest == down && arr[yPos + 1][xPos] != '*' || shortest == left && arr[yPos][xPos - 1] != '*' || shortest == right && arr[yPos][xPos + 1] != '*')
	{
		if (shortest == up)
		{
			arr[yPos][xPos] = prev;
			prev = arr[yPos - 1][xPos];
			arr[yPos - 1][xPos] = '%';
			yPos--;
		}

		else
			if (shortest == left)
			{
				arr[yPos][xPos] = prev;
				prev = arr[yPos][xPos - 1];
				arr[yPos][xPos - 1] = '%';
				xPos--;
			}
			else
				if (shortest == down)
				{
					arr[yPos][xPos] = prev;
					prev = arr[yPos + 1][xPos];
					arr[yPos + 1][xPos] = '%';
					yPos++;
				}
				else
					if (shortest == right)
					{
						arr[yPos][xPos] = prev;
						prev = arr[yPos][xPos + 1];
						arr[yPos][xPos + 1] = '%';
						xPos++;
					}


		prevMove = shortest;
	}


	if (xPos != 14 || yPos != 11)
		return false;
	else
		return true;
}



/////////////////////////////////////////////
Clyde::~Clyde()
{}
void Clyde::setXpos(int x)
{
	xPos = x;
}
void Clyde::setYpos(int y)
{
	yPos = y;
}
int Clyde::getPrevMove()
{
	return prevMove;
}
char Clyde::getPrev()
{
	return prev;
}

void Clyde::setPrevMove(int move)
{
	prevMove = move;
}
void Clyde::setPrev(char x)
{
	prev = x;
}
int Clyde::getFace()
{
	return clyde;
}
void Clyde::setFace(char arr[31][28], char x)
{
	clyde = x;
}
int Clyde::getXpos()
{
	return xPos;
}
int Clyde::getYpos()
{
	return yPos;
}
Clyde::Clyde()
{
	clyde = '1';
	xPos = 16;
	yPos = 14;
	prev = ' ';
	prevMove = 1;
}

void Clyde::locate(char arr[31][28])
{
	arr[yPos][xPos] = clyde;
}

void Clyde::move(char arr[31][28], int shortest, Ghost* g[4])
{
	int up = 0;
	int left = 1;
	int down = 2;
	int right = 3;

	if (prev == '2' || prev == 'b')
	{
		prev = g[1]->getPrev();
	}
	if (prev == '4' || prev == 'i')
	{
		prev = g[3]->getPrev();
	}
	if (prev == '3' || prev == 'p')
	{
		prev = g[2]->getPrev();
	}


	if (shortest == up && (arr[yPos - 1][xPos] != '*' || (arr[yPos - 1][xPos] == '*' && ((xPos == 14 && yPos == 13) || (xPos == 13 && yPos == 13)))) || shortest == down && arr[yPos + 1][xPos] != '*' || shortest == left && arr[yPos][xPos - 1] != '*' || shortest == right && arr[yPos][xPos + 1] != '*')
	{
		if (shortest == up)
		{
			arr[yPos][xPos] = prev;
			prev = arr[yPos - 1][xPos];
			arr[yPos - 1][xPos] = clyde;
			yPos--;
		}
		else
			if (shortest == left)
			{
				arr[yPos][xPos] = prev;
				prev = arr[yPos][xPos - 1];
				arr[yPos][xPos - 1] = clyde;
				xPos--;
			}
			else
				if (shortest == down)
				{
					arr[yPos][xPos] = prev;
					prev = arr[yPos + 1][xPos];
					arr[yPos + 1][xPos] = clyde;
					yPos++;
				}
				else
					if (shortest == right)
					{
						arr[yPos][xPos] = prev;
						prev = arr[yPos][xPos + 1];
						arr[yPos][xPos + 1] = clyde;
						xPos++;
					}

		prevMove = shortest;
	}
}
void Clyde::scatterMode(char arr[31][28], Ghost* g[4])
{
	bool check = true;
	int shortest = target(arr, 0, 30, xPos, yPos, prevMove);//it will move towards the targetted tile.
	move(arr, shortest, g);
}

void Clyde::chaseMode(char arr[31][28], pacman p, Ghost* g[4])
{
	bool check = true;
	int pacmanx = p.getXpos();
	int pacmany = p.getYpos();

	if (abs(yPos - p.getYpos()) > 8 || abs(xPos - p.getXpos()) > 8)
	{
		int shortest = target(arr, pacmanx, pacmany, xPos, yPos, prevMove);
		move(arr, shortest, g);

	}
	else
	{
		scatterMode(arr, g);
	}
}

bool Clyde::annihilated(char arr[31][28]) //eaten
{
	int up = 0;
	int left = 1;
	int down = 2;
	int right = 3;

	int x = 14;
	int y = 11;
	bool check = true;
	int shortest = target(arr, x, y, xPos, yPos, prevMove);//it will move towards the targetted tile.

	cout << shortest << endl;

	while ((shortest == up && arr[yPos - 1][xPos] == '*') || (shortest == down && arr[yPos + 1][xPos] == '*') || (shortest == left && arr[yPos][xPos - 1] == '*') || (shortest == right && arr[yPos][xPos + 1] == '*'))
	{
		shortest = target(arr, x, y, xPos, yPos, prevMove);
	}

	if (shortest == up && arr[yPos - 1][xPos] != '*' || shortest == down && arr[yPos + 1][xPos] != '*' || shortest == left && arr[yPos][xPos - 1] != '*' || shortest == right && arr[yPos][xPos + 1] != '*')
	{
		if (shortest == up)
		{
			arr[yPos][xPos] = prev;
			prev = arr[yPos - 1][xPos];
			arr[yPos - 1][xPos] = '%';
			yPos--;
		}

		else
			if (shortest == left)
			{
				arr[yPos][xPos] = prev;
				prev = arr[yPos][xPos - 1];
				arr[yPos][xPos - 1] = '%';
				xPos--;
			}
			else
				if (shortest == down)
				{
					arr[yPos][xPos] = prev;
					prev = arr[yPos + 1][xPos];
					arr[yPos + 1][xPos] = '%';
					yPos++;
				}
				else
					if (shortest == right)
					{
						arr[yPos][xPos] = prev;
						prev = arr[yPos][xPos + 1];
						arr[yPos][xPos + 1] = '%';
						xPos++;
					}


		prevMove = shortest;
	}


	if (xPos != 14 || yPos != 11)
		return false;
	else
		return true;
}

/////////////////////////////////////////////////
Pinky::~Pinky()
{}
void Pinky::setXpos(int x)
{
	xPos = x;
}
void Pinky::setYpos(int y)
{
	yPos = y;
}
int Pinky::getPrevMove()
{
	return prevMove;
}
char Pinky::getPrev()
{
	return prev;
}

void Pinky::setPrevMove(int move)
{
	prevMove = move;
}
void Pinky::setPrev(char x)
{
	prev = x;
}
int Pinky::getFace()
{
	return pinky;
}
void Pinky::setFace(char arr[31][28], char x)
{
	pinky = x;
}
int Pinky::getXpos()
{
	return xPos;
}
int Pinky::getYpos()
{
	return yPos;
}

Pinky::Pinky()
{
	pinky = '3';
	xPos = 14;
	yPos = 14;
	prev = ' ';
	prevMove = 1;
}

void Pinky::locate(char arr[31][28])
{
	arr[yPos][xPos] = pinky;
}

void Pinky::move(char arr[31][28], int shortest, Ghost* g[4])
{
	int up = 0;
	int left = 1;
	int down = 2;
	int right = 3;

	if (prev == '1' || prev == 'c')
	{
		prev = g[0]->getPrev();
	}
	if (prev == '4' || prev == 'i')
	{
		prev = g[3]->getPrev();
	}
	if (prev == '2' || prev == 'b')
	{
		prev = g[1]->getPrev();
	}

	if (shortest == up && (arr[yPos - 1][xPos] != '*' || (arr[yPos - 1][xPos] == '*' && ((xPos == 14 && yPos == 13) || (xPos == 13 && yPos == 13)))) || shortest == down && arr[yPos + 1][xPos] != '*' || shortest == left && arr[yPos][xPos - 1] != '*' || shortest == right && arr[yPos][xPos + 1] != '*')
	{
		if (shortest == up)
		{
			arr[yPos][xPos] = prev;
			prev = arr[yPos - 1][xPos];
			arr[yPos - 1][xPos] = pinky;
			yPos--;
		}

		else
			if (shortest == left)
			{
				arr[yPos][xPos] = prev;
				prev = arr[yPos][xPos - 1];
				arr[yPos][xPos - 1] = pinky;
				xPos--;
			}
			else
				if (shortest == down)
				{
					arr[yPos][xPos] = prev;
					prev = arr[yPos + 1][xPos];
					arr[yPos + 1][xPos] = pinky;
					yPos++;
				}
				else
					if (shortest == right)
					{
						arr[yPos][xPos] = prev;
						prev = arr[yPos][xPos + 1];
						arr[yPos][xPos + 1] = pinky;
						xPos++;
					}

		prevMove = shortest;
	}

}

void Pinky::chaseMode(char arr[31][28], pacman p, Ghost* g[4])
{
	int pacMove = p.getDirection();
	bool check = true;
	if (pacMove == 1) //left
	{
		int pacmanx = p.getXpos() - 4;
		int pacmany = p.getYpos();

		int shortest = target(arr, pacmanx, pacmany, xPos, yPos, prevMove);
		move(arr, shortest, g);
	}

	if (pacMove == 3) //right
	{
		int pacmanx = p.getXpos() + 4;
		int pacmany = p.getYpos();

		int shortest = target(arr, pacmanx, pacmany, xPos, yPos, prevMove);
		move(arr, shortest, g);
	}

	if (pacMove == 2) //down
	{
		int pacmanx = p.getXpos();
		int pacmany = p.getYpos() + 4;

		int shortest = target(arr, pacmanx, pacmany, xPos, yPos, prevMove);
		move(arr, shortest, g);
	}

	if (pacMove == 0) //up
	{
		int pacmanx = p.getXpos() + 4;
		int pacmany = p.getYpos() - 4;

		int shortest = target(arr, pacmanx, pacmany, xPos, yPos, prevMove);
		move(arr, shortest, g);
	}
}

void Pinky::scatterMode(char arr[31][28], Ghost* g[4])
{
	bool check = true;
	int shortest = target(arr, 0, 0, xPos, yPos, prevMove);//it will move towards the targetted tile.
	move(arr, shortest, g);
}

bool Pinky::annihilated(char arr[31][28])
{
	int up = 0;
	int left = 1;
	int down = 2;
	int right = 3;

	int x = 14;
	int y = 11;
	bool check = true;

	int shortest = target(arr, x, y, xPos, yPos, prevMove);//it will move towards the targetted tile.
	while ((shortest == up && arr[yPos - 1][xPos] == '*') || (shortest == down && arr[yPos + 1][xPos] == '*') || (shortest == left && arr[yPos][xPos - 1] == '*') || (shortest == right && arr[yPos][xPos + 1] == '*'))
	{
		shortest = target(arr, x, y, xPos, yPos, prevMove);
	}

	if (shortest == up && arr[yPos - 1][xPos] != '*' || shortest == down && arr[yPos + 1][xPos] != '*' || shortest == left && arr[yPos][xPos - 1] != '*' || shortest == right && arr[yPos][xPos + 1] != '*')
	{
		if (shortest == up)
		{
			arr[yPos][xPos] = prev;
			prev = arr[yPos - 1][xPos];
			arr[yPos - 1][xPos] = '%';
			yPos--;
		}

		else
			if (shortest == left)
			{
				arr[yPos][xPos] = prev;
				prev = arr[yPos][xPos - 1];
				arr[yPos][xPos - 1] = '%';
				xPos--;
			}
			else
				if (shortest == down)
				{
					arr[yPos][xPos] = prev;
					prev = arr[yPos + 1][xPos];
					arr[yPos + 1][xPos] = '%';
					yPos++;
				}
				else
					if (shortest == right)
					{
						arr[yPos][xPos] = prev;
						prev = arr[yPos][xPos + 1];
						arr[yPos][xPos + 1] = '%';
						xPos++;
					}


		prevMove = shortest;
	}

	if (xPos != 14 || yPos != 11)
		return false;
	else
		return true;
}

/////////////////////////////////////////////
Inky::~Inky()
{}
void Inky::setXpos(int x)
{
	xPos = x;
}
void Inky::setYpos(int y)
{
	yPos = y;
}
int Inky::getPrevMove()
{
	return prevMove;
}
char Inky::getPrev()
{
	return prev;
}

void Inky::setPrevMove(int move)
{
	prevMove = move;
}
void Inky::setPrev(char x)
{
	prev = x;
}
int Inky::getFace()
{
	return inky;
}
void Inky::setFace(char arr[31][28], char x)
{
	inky = x;
}
int Inky::getXpos()
{
	return xPos;
}
int Inky::getYpos()
{
	return yPos;
}
Inky::Inky()
{
	inky = '4';
	xPos = 12;
	yPos = 14;
	prev = ' ';
	prevMove = 1;
}

void Inky::locate(char arr[31][28])
{
	arr[yPos][xPos] = inky;
}

void Inky::move(char arr[31][28], int shortest, Ghost* g[4])
{
	int up = 0;
	int left = 1;
	int down = 2;
	int right = 3;

	if (prev == '2' || prev == 'b')
	{
		prev = g[1]->getPrev();
	}
	if (prev == '3' || prev == 'p')
	{
		prev = g[2]->getPrev();
	}
	if (prev == '1' || prev == 'c')
	{
		prev = g[0]->getPrev();
	}

	if (shortest == up && (arr[yPos - 1][xPos] != '*' || (arr[yPos - 1][xPos] == '*' && ((xPos == 14 && yPos == 13) || (xPos == 13 && yPos == 13)))) || shortest == down && arr[yPos + 1][xPos] != '*' || shortest == left && arr[yPos][xPos - 1] != '*' || shortest == right && arr[yPos][xPos + 1] != '*')
	{
		if (shortest == up)
		{
			arr[yPos][xPos] = prev;
			prev = arr[yPos - 1][xPos];
			arr[yPos - 1][xPos] = inky;
			yPos--;
		}

		else
			if (shortest == left)
			{
				arr[yPos][xPos] = prev;
				prev = arr[yPos][xPos - 1];
				arr[yPos][xPos - 1] = inky;
				xPos--;
			}
			else
				if (shortest == down)
				{
					arr[yPos][xPos] = prev;
					prev = arr[yPos + 1][xPos];
					arr[yPos + 1][xPos] = inky;
					yPos++;
				}
				else
					if (shortest == right)
					{
						arr[yPos][xPos] = prev;
						prev = arr[yPos][xPos + 1];
						arr[yPos][xPos + 1] = inky;
						xPos++;
					}

		prevMove = shortest;

	}
}
void Inky::chaseMode(char arr[31][28], pacman p, Ghost* g[4])
{
	int pacMove = p.getDirection();

	if (pacMove == 1) //left
	{
		int pacmanx = p.getXpos() - 2;
		int pacmany = p.getYpos();

		int blinkyx = b.getXpos();
		int blinkyy = b.getYpos();

		int targx = -1;
		int targy = -1;

		if (blinkyx < p.getXpos() && blinkyy < p.getYpos() || blinkyx < pacmanx && blinkyy == pacmany)
		{
			targx = pacmanx + (pacmanx - blinkyx);
			targy = pacmany + (pacmany - blinkyy);
		}
		else if (blinkyx < p.getXpos() && blinkyy > p.getYpos() || blinkyx == pacmanx && blinkyy > pacmany)
		{
			targx = pacmanx + (pacmanx - blinkyx);
			targy = pacmany - (blinkyy - pacmany);
		}
		else if (blinkyx > p.getXpos() && blinkyy > p.getYpos() || blinkyx > pacmanx && blinkyy == pacmany)
		{
			targx = pacmanx - (blinkyx - pacmanx);
			targy = pacmany - (blinkyy - pacmany);
		}
		else if (blinkyx > p.getXpos() && blinkyy < p.getYpos() || blinkyx == pacmanx && blinkyy < pacmany)
		{
			targx = pacmanx - (blinkyx - pacmanx);
			targy = pacmany + (pacmany - blinkyy);
		}
		bool check = true;
		int shortest = target(arr, targx, targy, xPos, yPos, prevMove);
		move(arr, shortest, g);
	}

	if (pacMove == 3) //right
	{
		int pacmanx = p.getXpos() + 2;
		int pacmany = p.getYpos();

		int blinkyx = b.getXpos();
		int blinkyy = b.getYpos();

		int targx = -1;
		int targy = -1;

		if (blinkyx < p.getXpos() && blinkyy < p.getYpos() || blinkyx < pacmanx && blinkyy == pacmany)
		{
			targx = pacmanx + (pacmanx - blinkyx);
			targy = pacmany + (pacmany - blinkyy);
		}

		else if (blinkyx > p.getXpos() && blinkyy < p.getYpos() || blinkyx == pacmanx && blinkyy < pacmany)
		{
			targx = pacmanx - (blinkyx - pacmanx);
			targy = pacmany + (pacmany - blinkyy);
		}

		else if (blinkyx > p.getXpos() && blinkyy > p.getYpos() || blinkyx > pacmanx && blinkyy == pacmany)
		{
			targx = pacmanx - (blinkyx - pacmanx);
			targy = pacmany - (blinkyy - pacmany);
		}

		else if (blinkyx < p.getXpos() && blinkyy > p.getYpos() || blinkyx == pacmanx && blinkyy > pacmany)
		{
			targx = pacmanx + (pacmanx - blinkyx);
			targy = pacmany - (blinkyy - pacmany);
		}

		int shortest = target(arr, targx, targy, xPos, yPos, prevMove);
		move(arr, shortest, g);
	}

	if (pacMove == 2) //down
	{
		int pacmanx = p.getXpos();
		int pacmany = p.getYpos() + 2;

		int blinkyx = b.getXpos();
		int blinkyy = b.getYpos();

		int targx = -1;
		int targy = -1;

		if (blinkyx < p.getXpos() && blinkyy < p.getYpos() || blinkyx < pacmanx && blinkyy == pacmany)
		{
			targx = pacmanx + (pacmanx - blinkyx);
			targy = pacmany + (pacmany - blinkyy);
		}

		else if (blinkyx > p.getXpos() && blinkyy < p.getYpos() || blinkyx == pacmanx && blinkyy < pacmany)
		{
			targx = pacmanx - (blinkyx - pacmanx);
			targy = pacmany + (pacmany - blinkyy);
		}

		else if (blinkyx > p.getXpos() && blinkyy > p.getYpos() || blinkyx > pacmanx && blinkyy == pacmany)
		{
			targx = pacmanx - (blinkyx - pacmanx);
			targy = pacmany - (blinkyy - pacmany);
		}

		else if (blinkyx < p.getXpos() && blinkyy > p.getYpos() || blinkyx == pacmanx && blinkyy > pacmany)
		{
			targx = pacmanx + (pacmanx - blinkyx);
			targy = pacmany - (blinkyy - pacmany);
		}


		int shortest = target(arr, targx, targy, xPos, yPos, prevMove);
		move(arr, shortest, g);
	}

	if (pacMove == 0) //up
	{
		int pacmanx = p.getXpos() - 2;
		int pacmany = p.getYpos() - 2;

		int blinkyx = b.getXpos();
		int blinkyy = b.getYpos();

		int targx = -1;
		int targy = -1;

		if (blinkyx < p.getXpos() && blinkyy < p.getYpos() || blinkyx < pacmanx && blinkyy == pacmany)
		{
			targx = pacmanx + (pacmanx - blinkyx);
			targy = pacmany + (pacmany - blinkyy);
		}
		else if (blinkyx < p.getXpos() && blinkyy > p.getYpos() || blinkyx == pacmanx && blinkyy > pacmany)
		{
			targx = pacmanx + (pacmanx - blinkyx);
			targy = pacmany - (blinkyy - pacmany);
		}
		else if (blinkyx > p.getXpos() && blinkyy > p.getYpos() || blinkyx > pacmanx && blinkyy == pacmany)
		{
			targx = pacmanx - (blinkyx - pacmanx);
			targy = pacmany - (blinkyy - pacmany);
		}
		else if (blinkyx > p.getXpos() && blinkyy < p.getYpos() || blinkyx == pacmanx && blinkyy < pacmany)
		{
			targx = pacmanx - (blinkyx - pacmanx);
			targy = pacmany + (pacmany - blinkyy);
		}

		int shortest = target(arr, targx, targy, xPos, yPos, prevMove);
		move(arr, shortest, g);
	}
}
void Inky::scatterMode(char arr[31][28], Ghost* g[4])
{

	int shortest = target(arr, 27, 30, xPos, yPos, prevMove);//it will move towards the targetted tile.
	move(arr, shortest, g);
}

bool Inky::annihilated(char arr[31][28])
{
	int up = 0;
	int left = 1;
	int down = 2;
	int right = 3;

	int x = 14;
	int y = 11;

	int shortest = target(arr, x, y, xPos, yPos, prevMove);//it will move towards the targetted tile.
	while ((shortest == up && arr[yPos - 1][xPos] == '*') || (shortest == down && arr[yPos + 1][xPos] == '*') || (shortest == left && arr[yPos][xPos - 1] == '*') || (shortest == right && arr[yPos][xPos + 1] == '*'))
	{
		shortest = target(arr, x, y, xPos, yPos, prevMove);
	}

	if (shortest == up && arr[yPos - 1][xPos] != '*' || shortest == down && arr[yPos + 1][xPos] != '*' || shortest == left && arr[yPos][xPos - 1] != '*' || shortest == right && arr[yPos][xPos + 1] != '*')
	{
		if (shortest == up)
		{
			arr[yPos][xPos] = prev;
			prev = arr[yPos - 1][xPos];
			arr[yPos - 1][xPos] = '%';
			yPos--;
		}

		else
			if (shortest == left)
			{
				arr[yPos][xPos] = prev;
				prev = arr[yPos][xPos - 1];
				arr[yPos][xPos - 1] = '%';
				xPos--;
			}
			else
				if (shortest == down)
				{
					arr[yPos][xPos] = prev;
					prev = arr[yPos + 1][xPos];
					arr[yPos + 1][xPos] = '%';
					yPos++;
				}
				else
					if (shortest == right)
					{
						arr[yPos][xPos] = prev;
						prev = arr[yPos][xPos + 1];
						arr[yPos][xPos + 1] = '%';
						xPos++;
					}


		prevMove = shortest;
	}

	if (xPos != 14 || yPos != 11)
		return false;
	else
		return true;
}

////////////////////////////////////////


pacman::pacman()
{
	face = 'P';
	xpos = 13;
	ypos = 23;
	score = 0;
	prevChar = ' ';
	pelletsEaten = 0;
	direction = 1;
}
char pacman::getPrevChar()
{
	return prevChar;
}
void pacman::setPrevChar(char x)
{
	prevChar = x;
}

int pacman::getPelletsEaten()
{
	return pelletsEaten;
}
int pacman::getScore()
{
	return score;
}
int pacman::getYpos()
{
	return ypos;
}
int pacman::getXpos()
{
	return xpos;
}
void pacman::setYpos(int y)
{
	ypos = y;
}
void pacman::setXpos(int x)
{
	xpos = x;
}
pacman::~pacman()
{

}
void pacman::setFace(char x)
{
	face = x;
}
int pacman::getDirection()
{
	return direction;
}

void pacman::locate(char arr[31][28])
{
	arr[ypos][xpos] = face;
}
void pacman::increaseScore(int s)
{
	score = score + s;
}
char pacman::getFace()
{
	return face;
}
void pacman::displayscore()
{
	cout << endl << "score:  " << score << endl;

}
void pacman::move(int m, char arr[31][28])
{
	const int KEY_ARROW_CHAR1 = 224;
	const int KEY_ARROW_UP = 72;
	const int KEY_ARROW_DOWN = 80;
	const int KEY_ARROW_LEFT = 75;
	const int KEY_ARROW_RIGHT = 77;


	if (m == KEY_ARROW_UP)
	{
		prevChar = arr[ypos - 1][xpos];
		if (arr[ypos - 1][xpos] != '*')
		{
			if (arr[ypos - 1][xpos] == '@')
			{
				increaseScore(5);
			}
			else
				if (arr[ypos - 1][xpos] == '`')
				{

					increaseScore(1);
					pelletsEaten++;
				}

			arr[ypos][xpos] = ' ';
			arr[ypos - 1][xpos] = face;

			direction = 0;
			ypos--;


		}
	}
	if (m == KEY_ARROW_DOWN)
	{
		prevChar = arr[ypos + 1][xpos];
		if (arr[ypos + 1][xpos] != '*')
		{
			if (arr[ypos + 1][xpos] == '@')
			{
				increaseScore(5);
			}
			else
				if (arr[ypos + 1][xpos] == '`')
				{
					increaseScore(1);
					pelletsEaten++;
				}
			arr[ypos][xpos] = ' ';
			arr[ypos + 1][xpos] = face;


			direction = 2;
			ypos++;
		}
	}
	if (m == KEY_ARROW_LEFT)
	{

		if (xpos == 0 && ypos == 14)
		{
			arr[ypos][xpos] = ' ';

			ypos = 14;
			xpos = 27;
			arr[ypos][xpos] = face;
			prevChar = ' ';
		}
		else
		{
			prevChar = arr[ypos][xpos - 1];
			if (arr[ypos][xpos - 1] != '*') //NOTE:warnings but due to checks they wont cause any error/****************************//
			{
				if (arr[ypos][xpos - 1] == '@')
				{
					increaseScore(5);

				}
				else
					if (arr[ypos][xpos - 1] == '`')
					{

						increaseScore(1);
						pelletsEaten++;

					}

				arr[ypos][xpos] = ' ';
				arr[ypos][xpos - 1] = face;

				direction = 1;
				xpos--;
			}
		}
	}
	if (m == KEY_ARROW_RIGHT)
	{
		if (xpos == 27 && ypos == 14)
		{
			prevChar = ' ';
			arr[ypos][xpos] = ' ';

			ypos = 14;
			xpos = 0;
			arr[ypos][xpos] = face;

		}
		else
			if (arr[ypos][xpos + 1] != '*')
			{
				prevChar = arr[ypos][xpos + 1];
				if (arr[ypos][xpos + 1] == '@')
				{
					increaseScore(5);
					//frightenedmode
				}
				else
					if (arr[ypos + 1][xpos + 1] == '`')
					{
						increaseScore(1);
						pelletsEaten++;
					}


				arr[ypos][xpos] = ' ';
				arr[ypos][xpos + 1] = face;

				direction = 3;
				xpos++;
			}
	}
}

bool pacman::checkMove(int m, char arr[31][28])
{
	const int KEY_ARROW_CHAR1 = 224;
	const int KEY_ARROW_UP = 72;
	const int KEY_ARROW_DOWN = 80;
	const int KEY_ARROW_LEFT = 75;
	const int KEY_ARROW_RIGHT = 77;

	if ((m == KEY_ARROW_LEFT && xpos == 0 && ypos == 14) || (m == KEY_ARROW_RIGHT && xpos == 27 && ypos == 14))
	{
		return true;
	}
	else
		if (m == KEY_ARROW_UP && arr[ypos - 1][xpos] != '*')
		{
			return true;
		}
		else
			if (m == KEY_ARROW_DOWN && arr[ypos + 1][xpos] != '*')
				return true;
			else
				if (m == KEY_ARROW_LEFT && arr[ypos][xpos - 1] != '*')
					return true;
				else
					if (m == KEY_ARROW_RIGHT && arr[ypos][xpos + 1] != '*')
						return true;
					else
						return false;

}
bool pacman::gameOver(char arr[31][28])
{
	bool check = true;

	for (int i = 0; i < 31; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			if (arr[i][j] == '`' || arr[i][j] == '@')
				check = false;
		}
	}

	return check;
}
