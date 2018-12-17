#include "AllHeaderFiles.h"

Enemy::Enemy(ENEMY_TYPE enemyType) : GameObject()
{	
	dropsAvail = false;
	if(enemyType == NORMAL)
	{
		row = 3;
		column = 3;
		
		char tempCharArray[3][3] =
		{
			{'X', 'X', 'X'},
			{'1', 'X', '1'},
			{' ', 'X', ' '}
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
		
		colour = LIGHTRED;
		x = 20;
		y = 10;	
		updateDelayDuration = 0;
	}
	
	else if(enemyType == BOSS)
	{
		row = 5;
		column = 5;
		
		char tempCharArray[5][5] =
		{
			{'X', ' ', 'X', ' ', 'X'},
			{'X', 'X', '1', 'X', 'X'},
			{'X', 'X', '1', 'X', 'X'},
			{' ', 'X', '1', 'X', ' '},
			{' ', ' ', 'X', ' ', ' '}
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
		
		colour = LIGHTMAGENTA;
		x = 20;
		y = 10;	
		drops.SetItemType((PICKUP_TYPE)(rand() % TOTAL_PICKUP_TYPE));
		updateDelayDuration = 5;
	}
	
	updateDelayTimer = 0;
	this->enemyType = enemyType;
	isAlive = true;
}

void Enemy::Update()
{
	updateDelayTimer ++;
	if(updateDelayTimer < updateDelayDuration)
	{
		return;
	}
	updateDelayTimer = 0;
	
	if(CheckBottomBoundary() == false)
	{
		MoveDown();
	}
	
	else
	{
		isAlive = false;
	}

}
