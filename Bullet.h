#include "AllHeaderFiles.h"

class Bullet : public GameObject
{
public :
	// Typedef enumerations
	BULLET_TYPE type;
	
	// Variables
	bool isAlive;
	
	// Constructor
	Bullet(BULLET_TYPE type);
	
	// Methods
	void Update();
};
