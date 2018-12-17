//! include guard (make sure only include/define once)
#ifndef	_ALL_HEADER_FILES_H_
#define	_ALL_HEADER_FILES_H_


//! normal library/header
#include <iostream>
#include <fstream>
#include <windows.h>
#include <vector>
#include <time.h>

using namespace std;

#define BOUNDARY_LEFT 5
#define BOUNDARY_RIGHT 55
#define BOUNDARY_TOP 2
#define BOUNDARY_BOTTOM 30

#define ENEMY_SPAWN_DURATION 50
#define MAX_BULLET 5
#define MAX_ENEMY 5

typedef enum{
        NORMAL,
        BOSS,
        TOTAL_ENEMY_TYPE
} ENEMY_TYPE;

typedef enum{
        STRAIGHT,
        DUAL,
        TOTAL_BULLET_TYPE
} BULLET_TYPE;

typedef enum{
		SLOW,
		HEART,
		COIN,
		BULLET,
		TOTAL_PICKUP_TYPE
} PICKUP_TYPE;

typedef enum{
		SLOW_ENEMY,
		HEAL,
		EXTRA_SCORE,
		CHANGE_BULLET
} POWER_TYPE;

//! externally declaring the class Enemy berfore the actual declaration
extern "C" class Enemy;
extern "C" class Player;

//! custom classes
#include "conio_yp.h"
#include "GameObject.h"
#include "Bullet.h"
#include "ETC.h"
#include "Player.h"
#include "Enemy.h"

#endif
