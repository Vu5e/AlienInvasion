#include "AllHeaderFiles.h"

Player::Player() : GameObject()
{
	bulletType = STRAIGHT;
	row = 3;
	column = 3;
	
	char tempCharArray[3][3] =
	{
		{' ', '1', ' '},
		{'1', '1', '1'},
		{'#', '#', '#'}
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
	
	colour = YELLOW;
	x = 20;
	y = 20;
	
	health = 100;
	score = 0;
	shootDelayTimer = 0;
	shootDelayDuration = 10;
}
             
void Player::Update()
{
	shootDelayTimer ++ ;
	
	if(GetAsyncKeyState(VK_LEFT))
	{
		if(CheckLeftBoundary() == false)
		{
			MoveLeft();
		}
	}
	
	if(GetAsyncKeyState(VK_RIGHT))
	{
		if(CheckRightBoundary() == false)
		{
			MoveRight();
		}
	}
	
	if(GetAsyncKeyState(VK_UP))
	{
		if(CheckTopBoundary() == false)
		{		
			MoveUp();
		}
	}
	
	if(GetAsyncKeyState(VK_DOWN))
	{
		if(CheckBottomBoundary() == false)
		{		
			MoveDown();
		}
	}
	
	if(GetAsyncKeyState(VK_SPACE))
	{
		if(shootDelayTimer > shootDelayDuration)
		{
			Shoot();
			shootDelayTimer = 0;
		}
	}
	
	for(int i = 0; i < bulletList.size(); i++)
	{
		bulletList[i].Update();
		
		if(bulletList[i].isAlive == false)
		{
			bulletList[i].DrawTrail();
			bulletList.erase(bulletList.begin() + i);
		}
		
		else
		{
			bulletList[i].Draw();
		}
	}
}

void Player::Shoot()
{
	if(bulletList.size() < MAX_BULLET)
	{
		Bullet newBullet(bulletType);
		switch(bulletType)
		{
			case STRAIGHT:
				newBullet.x = x + 1;
				break;
			case DUAL:
				newBullet.x = x;
				break;
		}
		newBullet.y = y;
		bulletList.push_back(newBullet);
	}
}
