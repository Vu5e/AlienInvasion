#pragma once

#include "AllHeaderFiles.h"

using namespace std;

class TemporalObject : public GameObject
{
public:
	// Variables
	bool isExpired;
	int lifeTime;
	
	// Constructor
	TemporalObject();

	// Methods
	void Update();
};

class PickUp : public TemporalObject
{
public:
	// Typedef enumerations
	PICKUP_TYPE pickUp;
	
	// Constructor
	PickUp();
	
	// Methods
	void SetPosition(int x, int y);
	void SetItemType(PICKUP_TYPE item);
};

class Power : public TemporalObject
{
public:
	// Typedef enumerations
	POWER_TYPE power;
	
	// Constructor
	Power();
	
	// Methods
	void SetLifeTime(int lifeTime);
	void Execute(Player &player, vector<Enemy> &enemyList);
};
