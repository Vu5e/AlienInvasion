
#ifndef	_PLAYER_H_
#define	_PLAYER_H_

#include "AllHeaderFiles.h"

using namespace std;

class Player : public GameObject
{
public :
	// Typedef enumerations
	BULLET_TYPE bulletType;
	
	// Variables
	int health;
	int score;
	int shootDelayTimer;
	int shootDelayDuration;
	
	// Vector variables
	vector<Bullet> bulletList;
	vector<Power> powerList;
	
	// Constructor
	Player();
	
	// Methods
	void Update();
	void Shoot();
};

#endif
