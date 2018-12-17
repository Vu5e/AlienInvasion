#include <iostream>
#include <fstream>
#include "conio_yp.c"

using namespace std;

struct OBJECT
{
    int x, y, x0, y0, count, counter, counTER, colour;
    char chaR;
    bool alive;        
};
void writeHighscores(int score)
{
    string name;
    system("cls");
    cout <<"PLEASE ENTER USER NAME: ";
    cin >> name;
    ofstream write;
    
    write.open("highscores.txt");
    write << name <<"\t\t"<< score <<endl;
    write.close();
}

int readHighscores()
{
    int score;
    string name;
    ifstream read;
    
    read.open("highscores.txt");
    read >> name >> score;
    read.close();
}

void viewHighscores()
{
    int score = 0, choice;
    string name ="NULL";
    system("cls");
    ifstream read;
    
    read.open("highscores.txt");
    read >> name >> score;
    read.close();
    cout <<"NAME\t\t"<<"SCORE"<<endl<<endl;
    cout << name <<"\t\t"<<score<<endl<<endl;
    cout <<"Press number : "<<endl;
    cout <<"1. To play game"<<endl;
    cout <<"2. To exit game"<<endl<<endl;
    cout <<"Your choice is : ";
    cin >> choice;
    if(choice == 2) exit(1);
}

void menu()
{
    int choice;
    int toggleBlink = 0;
    int counterDelay = 0;
    char anyButtonPressed = ']';
    
    do{       
        if(toggleBlink == 1)
        {
            textcolor(WHITE);
            gotoxy(20,20);
            cout <<"ALIEN INVASION";
            
            counterDelay++;
            if(counterDelay > 10)
            {
               counterDelay = 0;             
               toggleBlink = 0;
            }
        }
        if(toggleBlink == 0)
        {
            textcolor(YELLOW); 
            gotoxy(20,20);          
            cout <<"ALIEN INVASION";

            counterDelay++;
            if(counterDelay > 10)
            {
               counterDelay = 0;             
               toggleBlink = 1;
            }
        }
        
        if(kbhit())
        {
          anyButtonPressed = getch();
        }
        system("cls");
    }while(anyButtonPressed == ']');
    gotoxy(58,40);
    
    system("cls");
    gotoxy(20,20);
    cout <<"1. PLAY"<<endl;
    gotoxy(20,21);
    cout <<"2. HIGHSCORES"<<endl;
    gotoxy(20,22);
    cout <<"Your choice is : ";
    cin >> choice;
    if(choice == 2)
    {
        viewHighscores();
    }
    system("cls");
    system("PAUSE");
    system("cls");
}


void data(int score, int life)
{
    textcolor(YELLOW);
    gotoxy(6,34);
    cout <<"YOUR SCORE NOW IS : " <<score<<endl;
    gotoxy(6,35);
    cout <<"YOUR LIFE NOW IS  : " <<life<<" "<<endl;
}

void drawInterface()
{
    textcolor(WHITE);
    for(int i=5; i<55; i++)
    {
        gotoxy(i,5);
        cout <<"=";
        gotoxy(i,30);
        cout <<"=";
    }
    for(int i=6; i<30; i++)
    {
        gotoxy(5,i);
        cout <<"|";
        gotoxy(54,i);
        cout <<"|";
    }
      
}

int main()
{
    //! it all begins here!!!
    
    //! console window size    
    system("mode con: cols=58 lines=40");
    
    //! loading screen + main menu
    menu();
    
    //! seed the random function with current system time
    srand( time(NULL) );
    
    drawInterface();
    
    OBJECT spaceship[5];
    spaceship[0].chaR ='<';  spaceship[0].x =20;  spaceship[0].y =29; spaceship[0].colour = YELLOW;   
    spaceship[1].chaR ='@';  spaceship[1].x =21;  spaceship[1].y =29; spaceship[1].colour = WHITE;  
    spaceship[2].chaR ='$';  spaceship[2].x =22;  spaceship[2].y =29; spaceship[2].colour = WHITE;  
    spaceship[3].chaR ='@';  spaceship[3].x =23;  spaceship[3].y =29; spaceship[3].colour = WHITE;      
    spaceship[4].chaR ='>';  spaceship[4].x =24;  spaceship[4].y =29; spaceship[4].colour = YELLOW;
    
    for(int i=0; i<5; i++)
    {
        int m = spaceship[i].x;
        int n = spaceship[i].y;
        gotoxy(m,n);
        cout << spaceship[i].chaR;
    }
    
    for(int i=0; i<5; i++)
    {
        spaceship[i].x0 = spaceship[i].x;
        spaceship[i].y0 = spaceship[i].y;
    }
     
    OBJECT alien[4];
    
    alien[0].x = 7 + rand()%45;    alien[0].y = 6;    alien[0].chaR = 'X'; alien[0].colour = YELLOW;    alien[0].counTER = 100;
    alien[1].x = 7 + rand()%45;    alien[1].y = 6;    alien[1].chaR = 'X'; alien[1].colour = LIGHTRED;    alien[1].counTER = 112;
    alien[2].x = 7 + rand()%45;    alien[2].y = 6;    alien[2].chaR = 'X'; alien[2].colour = LIGHTCYAN;    alien[2].counTER = 106;
    alien[3].x = 7 + rand()%45;    alien[3].y = 6;    alien[3].chaR = 'X'; alien[3].colour = LIGHTBLUE;    alien[3].counTER = 119;
    
    for(int i=0; i<4; i++)
    {
        alien[i].counter = 0;
        alien[i].alive = true;
        int m = alien[i].x;
        int n = alien[i].y;
        gotoxy(m,n);
        cout << alien[i].chaR;
    }
    
    for(int i=0; i<4; i++)
    {
        alien[i].x0 = alien[i].x;
        alien[i].y0 = alien[i].y;
    }
    
    OBJECT bullet;
    
    bullet.chaR ='|';  bullet.x =spaceship[2].x;  bullet.y =spaceship[2].y; 
    bullet.colour = YELLOW;    bullet.counter = 0;   bullet.counTER = 0;   
    bullet.alive = false;
    
    OBJECT fire[4];
    
    for(int i=0; i<4; i++)
    {
        fire[i].chaR ='=';     fire[i].colour = WHITE;    fire[i].counter = 0; fire[i].count = 2;
        fire[i].counTER = alien[i].counTER + 30 + rand()%100;        fire[i].alive = false;
    }
    
    OBJECT lifeup;
    
    lifeup.chaR = 3;        lifeup.x= 6 + rand()%10;        lifeup.y = 6;
    lifeup.counter = 0; lifeup.counTER = 1000 + rand()%1000;    lifeup.alive = false;
        
    int score = 0, life =100;
    char button;
    
    do{
    if(kbhit())
    {
        button=getch();
    
        if( (button =='a' || button =='A') && spaceship[0].x > 6)
        {
                for(int i=0; i<5; i++)
                {
                       int m = spaceship[i].x - 1;
                       int n = spaceship[i].y;
                        
                       spaceship[i].x--;
                       
                       textcolor(WHITE); 
                       gotoxy(m,n);
                       cout << spaceship[i].chaR;
                       gotoxy(58,40);
                       
                       int m0 = spaceship[4].x0;
                       int n0 = spaceship[4].y0;
                       gotoxy(m0,n0);
                       cout <<" ";
                       gotoxy(58,40);
                        
                       spaceship[i].x0 = m;
                       spaceship[i].y0 = n;
                }
        }
                
        else if( (button =='d' || button =='D') && spaceship[4].x < 53)
        {
                for(int i=4; i>-1; i--)
                {
                       int m = spaceship[i].x + 1;
                       int n = spaceship[i].y;
                        
                       spaceship[i].x++;
                        
                       textcolor(WHITE);
                       gotoxy(m,n);
                       cout << spaceship[i].chaR;
                       gotoxy(58,40);
                                
                       int m0 = spaceship[0].x0;
                       int n0 = spaceship[0].y0;
                       gotoxy(m0,n0);
                       cout <<" ";
                       gotoxy(58,40);
                        
                       spaceship[i].x0 = m;
                       spaceship[i].y0 = n;
                }
        }
                
        else if( (button =='s' || button =='S') && spaceship[0].y < 29)
        {
                for(int i=4; i>-1; i--)
                {
                       int m = spaceship[i].x;
                       int n = spaceship[i].y + 1;
                        
                       spaceship[i].y++;
                        
                       textcolor(WHITE);
                       gotoxy(m,n);
                       cout << spaceship[i].chaR;
                       gotoxy(58,40);
                                
                       int m0 = spaceship[i].x0;
                       int n0 = spaceship[i].y0;
                       gotoxy(m0,n0);
                       cout <<" ";
                       gotoxy(58,40);
                        
                       spaceship[i].x0 = m;
                       spaceship[i].y0 = n;
                }
        }
                
        else if( (button =='w' || button =='W') && spaceship[0].y > 6)
        {
                for(int i=4; i>-1; i--)
                {
                       int m = spaceship[i].x;
                       int n = spaceship[i].y - 1;
                        
                       spaceship[i].y--;
                        
                       textcolor(WHITE);
                       gotoxy(m,n);
                       cout << spaceship[i].chaR;
                       gotoxy(58,40);
                                
                       int m0 = spaceship[i].x0;
                       int n0 = spaceship[i].y0;
                       gotoxy(m0,n0);
                       cout <<" ";
                       gotoxy(58,40);
                        
                       spaceship[i].x0 = m;
                       spaceship[i].y0 = n;
                }
        }
        else if(button == ' ' && bullet.alive == false)
        {
                Beep(2000,20);
                bullet.alive = true;
                bullet.x = spaceship[2].x;
                bullet.y = spaceship[2].y;
                
        }
                                          
    }
    
    if( bullet.alive == true)
    {
                int m = bullet.x;
                int n = bullet.y - 1;
                        
                bullet.y--;
                        
                gotoxy(m,n);
                cout << bullet.chaR;
                gotoxy(58,40);
                Sleep(20);
                gotoxy(m,n);
                cout <<" ";
                gotoxy(58,40);
                bullet.counter = 0;
    }
    
    for(int i=0; i<4; i++)
    {
        //alien[i].counter++;
        fire[i].counter++;
        if(alien[i].alive == true && alien[i].counter >= alien[i].counTER)
        {
        
        int r = rand()%10;
       
        if(r%2==0)
        {
                alien[i].y++;
                alien[i].x++;
                int m = alien[i].x;
                int n = alien[i].y;
                
                textcolor(alien[i].colour);
                gotoxy(m,n);
                cout << alien[i].chaR;
                gotoxy(58,40);
                Sleep(50);
                
                int m0 = alien[i].x0;
                int n0 = alien[i].y0;
                gotoxy(m0,n0);
                cout <<" ";
                gotoxy(58,40);
                
                alien[i].x0 = m;
                alien[i].y0 = n;
                alien[i].counter = 0;
        }
        
        else if(r%2!=0)
        {
                alien[i].y++;
                alien[i].x--;
                int m = alien[i].x;
                int n = alien[i].y;
                
                textcolor(alien[i].colour);
                gotoxy(m,n);
                cout << alien[i].chaR;
                gotoxy(58,40);
                Sleep(50);
                
                int m0 = alien[i].x0;
                int n0 = alien[i].y0;
                gotoxy(m0,n0);
                cout <<" ";
                gotoxy(58,40);
                
                alien[i].x0 = m;
                alien[i].y0 = n;
                alien[i].counter = 0;
       }
       }
       
       if(fire[i].counter >= fire[i].counTER)
       {
                fire[i].alive = true;
                fire[i].x = alien[i].x;    
                fire[i].y = alien[i].y;
       }
    }
        
    for(int i=0; i<4; i++)
    {
        fire[i].count++;
        if(fire[i].alive == true && fire[i].count >= 2)
       {
                fire[i].y++;
                int m = fire[i].x;
                int n = fire[i].y;
                
                textcolor(WHITE);
                gotoxy(m,n);
                cout << fire[i].chaR;
                gotoxy(58,40);
                Sleep(50);
                
                gotoxy(m,n-1);
                cout <<" ";
                gotoxy(58,40);
                fire[i].counter = 0;
                fire[i].count = 0;
                
       }
    }
    
    if(lifeup.counter >= lifeup.counTER)        
    {
        lifeup.alive = true;
        lifeup.counter = 0;
    }
    
    if(lifeup.alive == true)
    {
        lifeup.y++;
        textcolor(YELLOW);
        gotoxy(lifeup.x, lifeup.y);
        cout << lifeup.chaR;
        gotoxy(70,40);
        Sleep(30);
        gotoxy(lifeup.x, lifeup.y - 1);
        cout <<" ";
    }
    
    if(bullet.y == 6) bullet.alive = false;           
    bullet.counter++;
    for(int i=0; i<5; i++)
    {
        if((lifeup.x == spaceship[i].x) && (lifeup.y == spaceship[i].y))
        {
                lifeup.alive = false;
                textcolor(WHITE);
                gotoxy(lifeup.x,lifeup.y);
                cout <<spaceship[i].chaR;
                lifeup.counter = 0;
                lifeup.x = 6 + rand()%45;
                lifeup.y = 6;
                lifeup.counTER = 1000 + rand()%1000;
                life+=10;
        }
    }
    if(lifeup.y >28) 
    {
        lifeup.alive = false;
        gotoxy(lifeup.x,lifeup.y);
        cout <<" ";
        lifeup.counter = 0;
        lifeup.x = 6 + rand()%45;
        lifeup.y = 6;
        lifeup.counTER = 1000 + rand()%1000;
    }
    
    lifeup.counter++;
       
    for(int i=0; i<4; i++)
    {
        alien[i].counter+=3;
        if(alien[i].y >28 || alien[i].x <7 || alien[i].x >52 ) alien[i].alive = false;
        if(fire[i].y >29) fire[i].alive = false;
        if((alien[i].x == bullet.x) && (alien[i].y == bullet.y))
        {
                alien[i].alive = false;
                score+=5;
        }
        for(int j=0; j<5; j++)
        {
        if(((alien[i].x == spaceship[j].x-1) && (alien[i].y == spaceship[j].y-1)) 
        || ((alien[i].x == spaceship[j].x+1) && (alien[i].y == spaceship[j].y-1))
        || ((alien[i].x == spaceship[j].x) && (alien[i].y == spaceship[j].y)))
        {
                alien[i].alive = false;
                score+=5;
                life -=2;
        }
        if((fire[i].x == spaceship[j].x) && (fire[i].y == spaceship[j].y - 1))
        {
                fire[i].alive = false;
                gotoxy(fire[i].x,fire[i].y);
                cout <<" ";
                score +=2;
                life -=5;
                fire[i].x = -1;
        }
        if(((fire[i].x == bullet.x) && (fire[i].y == bullet.y))
        || ((fire[i].x == bullet.x) && (fire[i].y == bullet.y-1)))
        {
                fire[i].alive = false;
                gotoxy(fire[i].x,fire[i].y);
                cout <<" ";
                score +=3;
                fire[i].x = -1;
        }
        }
        if(alien[i].alive == false)
        {
                alien[i].alive = true;
                alien[i].x = 6 + rand()%45;
                alien[i].y = 6;
        }
    }
    data(score, life);
    }while(button != 27 && score < 500 && life > 0);
    int highScores = readHighscores();
    if(score > highScores) writeHighscores(score);
    
    system("PAUSE");
    return 0;
}
