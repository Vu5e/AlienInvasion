#include "AllHeaderFiles.h"

void TemporalObject::Update()
{
	lifeTime --;
	
	if (lifeTime == 0)
		isExpired = true;
}

TemporalObject::TemporalObject() : GameObject()
{
	return;	
};

PickUp::PickUp() : TemporalObject()
{
	isExpired = false;
	lifeTime = 100;
}

void PickUp::SetPosition(int x, int y)
{
	this->x = x;
	this->y = y;
}

void PickUp::SetItemType(PICKUP_TYPE item)
{
	this->pickUp = item;
	row = 1;
	column = 1;
	
	switch(item)
	{
		case SLOW:
		{
			char tempCharArray[1][1] = {'T'};
			charArray = new char*[row];
			for(int i = 0; i < row; i++)
			{
				charArray[i] = new char[column];
				for(int j = 0; j < column; j++)
				{
					charArray[i][j] = tempCharArray[i][j];
				}
			}
			break;
		}
		case HEART:
		{
			char tempCharArray[1][1] = {(char)229};
			charArray = new char*[row];
			for(int i = 0; i < row; i++)
			{
				charArray[i] = new char[column];
				for(int j = 0; j < column; j++)
				{
					charArray[i][j] = tempCharArray[i][j];
				}
			}
			break;
		}
		case COIN:
		{
			char tempCharArray[1][1] = {(char)233};
			charArray = new char*[row];
			for(int i = 0; i < row; i++)
			{
				charArray[i] = new char[column];
				for(int j = 0; j < column; j++)
				{
					charArray[i][j] = tempCharArray[i][j];
				}
			}
			break;
		}
		case BULLET:
		{
			char tempCharArray[1][1] = {(char)236};
			charArray = new char*[row];
			for(int i = 0; i < row; i++)
			{
				charArray[i] = new char[column];
				for(int j = 0; j < column; j++)
				{
					charArray[i][j] = tempCharArray[i][j];
				}
			}
			break;
		}
		default:
		{
			char tempCharArray[1][1] = {'?'};
			charArray = new char*[row];
			for(int i = 0; i < row; i++)
			{
				charArray[i] = new char[column];
				for(int j = 0; j < column; j++)
				{
					charArray[i][j] = tempCharArray[i][j];
				}
			}
			break;
		}
	};
	
	colour = LIGHTCYAN;
}

Power::Power() : TemporalObject()
{
	isExpired = false;
}

void Power::SetLifeTime(int lifeTime)
{
	this->lifeTime = lifeTime;
}

void Power::Execute(Player &player, vector<Enemy> &enemyList)
{
	switch(power)
	{
		case SLOW_ENEMY:
		{
			for(int i = 0; i < enemyList.size(); i++)
			{
				enemyList[i].updateDelayDuration += 30;
			}
			break;
		}
	}
}
