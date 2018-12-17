#include "AllHeaderFiles.h"

Bullet::Bullet(BULLET_TYPE type) : GameObject()
{
	if(type == STRAIGHT)
	{
		row = 1;
		column = 1;
		
		char tempCharArray[1][1] =
		{
			{'X'}
		};
		
		charArray = new char*[row];
		for(int i = 0; i < row; i++)
		{
			charArray[i] = new char[column];
			for(int j = 0; j < column; j++)
			{
				charArray[i][j] = tempCharArray[i][j];
			}
		}
		
		colour = LIGHTCYAN;
		x = 20;
		y = 15;	
	}
	
	else if(type == DUAL)
	{
		row = 1;
		column = 3;
		
		char tempCharArray[1][3] =
		{
			{'|', ' ', '|'}
		};
		
		charArray = new char*[row];
		for(int i = 0; i < row; i++)
		{
			charArray[i] = new char[column];
			for(int j = 0; j < column; j++)
			{
				charArray[i][j] = tempCharArray[i][j];
			}
		}
		
		colour = LIGHTCYAN;
		x = 20;
		y = 15;	
	}
	
	isAlive = true;
}
             
void Bullet::Update()
{
	if(CheckTopBoundary() == false)
	{
		MoveUp();
	}
	
	else
	{
		isAlive = false;
	}
}
