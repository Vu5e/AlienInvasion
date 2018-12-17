
#ifndef	_ENEMY_H_
#define	_ENEMY_H_

#include "AllHeaderFiles.h"

using namespace std;

class Enemy : public GameObject
{
public :
	// Typedef enumerations
	ENEMY_TYPE enemyType;
	
	// Variables
	bool isAlive;
	int updateDelayTimer;
	int updateDelayDuration;
	
	
	// Class objects
	PickUp drops;
	bool dropsAvail;
	
	// Constructor
	Enemy(ENEMY_TYPE enemyType);
	
	// Methods
	void Update();
};

#endif
