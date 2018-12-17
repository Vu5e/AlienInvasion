#include "AllHeaderFiles.h"

int enemySpawnTimer = 0;

void DrawBoundary()
{
    textcolor(WHITE);
    for(int i = BOUNDARY_LEFT; i <= BOUNDARY_RIGHT; i++)
    {
        gotoxy(i, BOUNDARY_TOP);
        cout << "=";
        gotoxy(i, BOUNDARY_BOTTOM);
        cout << "=";
    }
    for(int i = BOUNDARY_TOP + 1; i < BOUNDARY_BOTTOM; i++)
    {
        gotoxy(BOUNDARY_LEFT, i);
        cout << "|";
        gotoxy(BOUNDARY_RIGHT, i);
        cout << "|";
    }      
}


void DrawHUD(Player& player)
{
	textcolor(WHITE);
	gotoxy(5, BOUNDARY_BOTTOM + 2);
	cout << "Health : " << player.health << " ";
	gotoxy(5, BOUNDARY_BOTTOM + 3);
	cout << "Score : " << player.score;
	gotoxy(5, BOUNDARY_BOTTOM + 4);
	cout << "Skill : " << (player.powerList.size() == 1) ? player.powerList[0].lifeTime : 0;
}

bool RectangleIntersect(int obj1_x, int obj1_y, int obj1_height, int obj1_width, int obj2_x, int obj2_y, int obj2_height, int obj2_width)
{
	if (obj1_x > obj2_x + obj2_width  || 
		obj1_x + obj1_width < obj2_x  ||
		obj1_y > obj2_y + obj2_height ||
		obj1_y + obj1_height < obj2_y )
	{
		return false;
	}
	return true;
}

void EnemyOverlappingCheck(Enemy& enemy, vector<Enemy>& enemyList)
{
	bool isOverlapping;
	do
	{
		isOverlapping = false;
		enemy.x = rand() % (BOUNDARY_RIGHT - BOUNDARY_LEFT - enemy.column) + BOUNDARY_LEFT + 1;
		enemy.y = -1 * rand() % 10;
		
		for(int i = 0; i < enemyList.size(); i++)
		{
			if(RectangleIntersect(enemy.x, enemy.y, enemy.row, enemy.column, enemyList[i].x, enemyList[i].y, enemyList[i].row, enemyList[i].column))
			{
				isOverlapping = true;
				break;
			}
		}
		
	}while(isOverlapping);
}

void SpawnEnemy(vector<Enemy>& enemyList)
{
	enemySpawnTimer ++;
	if(enemySpawnTimer > ENEMY_SPAWN_DURATION)
	{
		int numberOfEnemyToSpawn = rand() % MAX_ENEMY;
		
		for(int i = 0; i < numberOfEnemyToSpawn; i++)
		{
			int randEnemyType = rand() % TOTAL_ENEMY_TYPE; 
			Enemy newEnemy((ENEMY_TYPE)randEnemyType);
			EnemyOverlappingCheck(newEnemy, enemyList);
			enemyList.push_back(newEnemy); 
		}
		enemySpawnTimer = 0;
	}
}

void CollisionCheck(Player& player, vector<Enemy>& enemyList)
{
	//! player vs enemy
	for (int i = 0; i < enemyList.size(); i++)
	{
		Enemy* enemy = &enemyList[i];
		if (RectangleIntersect(player.x, player.y, player.row, player.column, enemy->x, enemy->y, enemy->row, enemy->column))
		{
			player.health --;
			player.score += 10;
			enemy->isAlive = false;
		}
		
		for (int j = 0; j < player.bulletList.size(); j++)
		{
			Bullet* bullet = &player.bulletList[j];
			if(RectangleIntersect(bullet->x, bullet->y, bullet->row, bullet->column, enemy->x, enemy->y, enemy->row, enemy->column))
			{
				player.score += 10;
				bullet->isAlive = false;
				enemy->isAlive = false;
				if(enemy->enemyType == BOSS)
				{
					enemy->drops.SetPosition(enemy->x, enemy->y);
					enemy->dropsAvail = ((rand() % 9) < 5) ?  true : false;
				}
			}
		}
	}
}

void LootCheck(Player &player, vector<PickUp>& drops)
{
	for(int i = 0; i < drops.size(); i++)
	{
		if (RectangleIntersect(player.x, player.y, player.row, player.column, drops[i].x, drops[i].y, drops[i].row, drops[i].column))
		{
			drops[i].isExpired = true;
			Power power;
			power.power = (POWER_TYPE)(drops[i].pickUp);
			power.SetLifeTime(1000);
			player.powerList.push_back(power);
		}
	}	
}

inline void ResetSpeed(vector<Enemy> &enemyList)
{
	for(int i = 0; i < enemyList.size(); i++)
	{
		if(enemyList[i].enemyType == BOSS)
			enemyList[i].updateDelayDuration = 5;
		else
			enemyList[i].updateDelayDuration = 1;
	}
}

int main()
{
    system("mode con: cols=58 lines=40");
    srand(time(NULL));
    
    DrawBoundary();
    
    hideCursor();

    char button;
    
    Player player;
    vector<Enemy> enemyList;
    vector<PickUp> drops;
    
    do
	{
		ResetSpeed(enemyList);
		for(int i = 0; i < player.powerList.size(); i++)
		{
			player.powerList[i].Update();
			if (player.powerList[i].isExpired == true)
				player.powerList.erase(player.powerList.begin() + i);
			else
			{
				switch(player.powerList[i].power)
				{
					case SLOW_ENEMY:
					{
						for(int j = 0; j < enemyList.size(); j++)
							if (enemyList[j].updateDelayDuration <= 5)
								enemyList[j].updateDelayDuration += 10;
						break;
					}
					case HEAL:
					{
						if(player.health < 100)
							player.health++;
						player.powerList[i].isExpired = true;
						break;
					}
					case EXTRA_SCORE:
					{
						player.score += 100;
						player.powerList[i].isExpired = true;
						break;
					}
					case CHANGE_BULLET:
					{
						player.bulletType = (BULLET_TYPE)(rand() % TOTAL_BULLET_TYPE);
						player.powerList[i].isExpired = true;
						break;
					}
				};
			}
		}
		
		player.Update();
		player.Draw();
		
		if (player.health <= 0)
			break; // Game over
		
		for(int i = 0; i < enemyList.size(); i++)
		{
			enemyList[i].Update();
			if(enemyList[i].isAlive == false)
			{
				if(enemyList[i].dropsAvail == true)
					drops.push_back(enemyList[i].drops);
					
				enemyList[i].DrawTrail();
				enemyList.erase(enemyList.begin() + i);
			}
			else
				enemyList[i].Draw();
		}
		
		for(int i = 0; i < drops.size(); i++)
		{
			drops[i].Update();
			if(drops[i].isExpired == true)
			{
				drops[i].DrawTrail();
				drops.erase(drops.begin() + i);
			}
			else
				drops[i].Draw();
		}
		
		CollisionCheck(player, enemyList);
		LootCheck(player, drops);
		SpawnEnemy(enemyList);
		DrawHUD(player);
		
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            button = 27;
        }
        
        Sleep(20);
    } while(button != 27);
    
    cout << endl;
    gotoxy(1, BOUNDARY_BOTTOM + 2);
    
    system("pause");
    return 0;
}
