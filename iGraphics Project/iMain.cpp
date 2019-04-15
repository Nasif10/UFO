#include "iGraphics.h"
#include "bitmap_loader.h"
#include "string.h"
#include "Highscore.h"


//Variables::
int screenWidth = 1200;
int	screenHeight = 690;

int score=0;
int flag = 0;
char name[30];
int image[10];
int ourShip;
int enemyship;
int x = 0;
int y = screenHeight;
int r,g,b;

//Game Mode Mechanisms:
bool start = true;
bool game = false;
bool gamestart = false;
bool gameover = false;
bool menu = true;
bool fireBullet = false;
bool hscore = false;
bool option = false;
bool about = false;

//page variables
int instructionpage;
int aboutpage;
int menupage;
int loginpage;


//buttons
int button[50];
int buttonview[6] = {true,true,true,true,true,true};
int back;

//menubutton
int buttonwidth = 200;
int buttonheight = 40;


void UP();
void DOWN();
void LEFT();
void RIGHT();
void fire();


// Structure for our spaceship 
struct ourShip{

	int ourX;
	int ourY;
	int bulletX;
	int bulletY;
	int score;
	//int life;


	ourShip(){
		ourX = 500; // x cordinate of our ship
		ourY = 10; // y cordinate of our ship
		bulletX = (ourX + 38); // bullet will come throug the middle of our ship, that's whyy some pixels has been added
		bulletY = (ourY + 40);
		//life = 200; 
	
	}
}ourCraft;


struct enemyCor{
	
	int corX; // x cordinate of enemy ship
	int corY; // y cordinate of enemy ship enemy 
	int gunCorX; // enemy's bullet x cordinate
	int gunCorY; // enemy's bullet y cordinate
	int x; 
	int y;
	bool isDead;


	enemyCor(){

		x= 25;
		y = 35;
		gunCorX = (corX+x);
		gunCorY = (corY-y);
	    isDead  = false;
	}
	
}enemy[7];


bool pointinrectangle(int  px,int py, int rectx,int recty, int rectw, int recth){

	if( ( px>=rectx && px<=rectx+rectw) && ( py>=recty && py<=recty+recth) ) return true;
	  return false;

}


bool collisionCheck(int ghostx,int ghosty){

	bool collided=false;

	for (int j = 0; j < 7; j++){	
	   if(pointinrectangle(ourCraft.bulletX,ourCraft.bulletY,enemy[j].corX,enemy[j].corY,160,70) || pointinrectangle(ourCraft.bulletX+70,ourCraft.bulletY,enemy[j].corX,enemy[j].corY,160,20)
		   || pointinrectangle(ourCraft.bulletX,ourCraft.bulletY+70,enemy[j].corX,enemy[j].corY,160,70) || pointinrectangle(ourCraft.bulletX+70,ourCraft.bulletY+100,enemy[j].corX,enemy[j].corY,160,20)){

            score+=5;
		    collided=true;
	    }
	    return collided;
	}
}


void enemyGenerate(){

	for (int j = 0; j < 7; j++){	
		enemy[j].corX = 200 + rand() % screenHeight;
		enemy[j].corY = screenHeight +rand()%500;
	}
}

void enemyMove(){

	for (int i = 0; i < 7; i++)
	   enemy[i].corY -= 20;
}


void showEnemy(){

	for (int i = 0; i < 7; i++){

	    if(enemy[i].isDead==true)
				continue;
		enemy[i].isDead = collisionCheck( enemy[i].corX, enemy[i].corY);
		if(enemy[i].isDead == false){
		   iShowBMP2(enemy[i].corX, enemy[i].corY,"enemy-1.bmp", 0);
	    }
	}

}

void Enemy(){

	for(int i=0; i<7; i++){
		if(enemy[i].corY<=0){

			enemy[i].corX = 100 + rand() % screenWidth;
			enemy[i].corY = screenHeight +rand()%500;		
		}
	}
}


void rectangle(){

	if (flag == 0){
		iRectangle(580, 400, 300, 80);
		iText(630, 430, "Enter Your Name", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if (flag == 1){

		iSetColor(0, 255, 0);
		iRectangle(580, 400, 300, 80);
		iSetColor(255, 100, 0);
		iText(600, 430, name, GLUT_BITMAP_TIMES_ROMAN_24);
		iSetColor(230, 230, 230);
	}
}


void iDraw()
{
	iClear();

	if(menu==true)
	{
		iShowImage(0, 0, screenWidth, screenHeight, menupage);

		if (buttonview[1])
			iShowImage(80, 300, buttonwidth, buttonheight, button[0]);
		if (!buttonview[1])
			iShowImage(80, 300, buttonwidth, buttonheight, button[5]);
		if (buttonview[2])
			iShowImage(80, 250, buttonwidth, buttonheight, button[1]);
		if (!buttonview[2])
			iShowImage(80, 250, buttonwidth, buttonheight, button[6]);
		if (buttonview[3])
			iShowImage(80, 200, buttonwidth, buttonheight, button[2]);
		if (!buttonview[3])
			iShowImage(80, 200, buttonwidth, buttonheight, button[7]);
		if (buttonview[4])
			iShowImage(80, 150, buttonwidth, buttonheight, button[3]);
		if (!buttonview[4])
			iShowImage(80, 150, buttonwidth, buttonheight, button[8]);
		if (buttonview[5])
			iShowImage(80, 100, buttonwidth, buttonheight, button[4]);
		if (!buttonview[5])
			iShowImage(80, 100, buttonwidth, buttonheight, button[9]);


	}

	if(hscore==true){

		sortScores();
	    iShowImage(-6, 645, 100, 50, back);

		iSetColor(25, 255, 255);
	   
	    iText(170, 400, "1.", GLUT_BITMAP_TIMES_ROMAN_24);   iText(170, 360, "2.", GLUT_BITMAP_TIMES_ROMAN_24);
	    iText(170, 320, "3.", GLUT_BITMAP_TIMES_ROMAN_24);   iText(170, 280, "4.", GLUT_BITMAP_TIMES_ROMAN_24);
	    iText(170, 240, "5.", GLUT_BITMAP_TIMES_ROMAN_24);   iText(170, 200, "6.", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(170, 160, "7.", GLUT_BITMAP_TIMES_ROMAN_24);   iText(170, 120, "8.", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(170, 80, "9.", GLUT_BITMAP_TIMES_ROMAN_24);    iText(170, 40, "10.", GLUT_BITMAP_TIMES_ROMAN_24);
	}

	if(option==true){
		iShowImage(0, 0, screenWidth, screenHeight, instructionpage);
		iShowImage(-6, 645, 100, 50, back);
	}

	if(about==true){
		iShowImage(0, 0, screenWidth, screenHeight, aboutpage);
	    iShowImage(-6, 645, 100, 50, back);
	}

	if(game==true)
    {
		iShowImage(0, 0, screenWidth, screenHeight, image[0]);

		iShowImage(ourCraft.bulletX, ourCraft.bulletY,10,40, image[3]);
		iShowImage(ourCraft.ourX, ourCraft.ourY, 80, 100, ourShip);
		iShowImage(20, 7, 70, 50, image[2]);
		showEnemy();
		Enemy();
		
		iSetColor(255, 100, 100);
		iFilledRectangle(46, 75, 20, 150);
		iRectangle(46, 75, 20, 150);

		iSetColor(r, g, b);
		iText(1010, 665, "SCORE :", GLUT_BITMAP_TIMES_ROMAN_24);

		
	}

}

void iPassiveMouse(int mx, int my)
{

	if (my >= 300 && my <= 340){
       if (mx >= 80 && mx <= 280){
			buttonview[1] = false;
	   }
	   else
			buttonview[1] = true;
	}
	else
		buttonview[1] = true;


	if (my >= 250 && my <= 290){
       if (mx >= 80 && mx <= 280){
			buttonview[2] = false;
	   }
	   else
			buttonview[2] = true;
	}
	else
		buttonview[2] = true;


	if (my >= 200 && my <= 240){
       if (mx >= 80 && mx <= 300){
			buttonview[3] = false;
	   }
		else
			buttonview[3] = true;
	}
	else
		buttonview[3] = true;


	if (my >= 150 && my <= 190){
	   if (mx >= 80 && mx <= 280){
	    	buttonview[4] = false;
	   }
	   else
			buttonview[4] = true;
	}
	else
		buttonview[4] = true;


	if (my >= 100 && my <= 140){
		if (mx >= 80 && mx <= 280){
	    	buttonview[5] = false;
		}
		else
			buttonview[5] = true;
	}
	else
		buttonview[5] = true;

}

void iMouseMove(int mx, int my)
{

}

void iMouse(int button, int state, int mx, int my){

   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){

      if (my >= 300 && my <= 340 && mx >= 80 && mx <= 280){
				game = true;
	  }

	  if (my >= 250 && my <= 290 && mx >= 80 && mx <= 280){
				hscore = true;	
				
	  }
	  if(hscore==true && mx>=0 && mx<=100 && my >=645 && my<=690){
		        hscore=false;
			    menu=true;    
	  }

	  if (my >= 200 && my <= 240 && mx >= 80 && mx <= 280){
				option = true;  
	  }
	  if(option==true && mx>=0 && mx<=100 && my >=645 && my<=690){
		        option=false;
			    menu=true;    
	  }

	  if (my >= 150 && my <= 190 && mx >= 80 && mx <= 280){
				about = true;
	  }
	  if(about==true && mx>=0 && mx<=100 && my >=645 && my<=690){
		        about=false;
			    menu=true;    
	  }

	  if (my >= 100 && my <= 140 && mx >= 80 && mx <= 280){
				exit(0);
	  }


   }

}

	

void iKeyboard(unsigned char key)
{
	if (key == 'q'){
		exit(0);
	}
	else if (key == 'p'){
		start = false;
	}
	else if (key == 'r'){
		start = true;
	}

	if (key == ' '){
		iPauseTimer(0);
	}
	if (key == 'v'){
		iResumeTimer(0);
	}
	if (key == 'z')
		fireBullet = true;
	if (key == 'x')
		fireBullet = false;

}

void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END){
		exit(0);
	}
	if (key == GLUT_KEY_RIGHT){
		RIGHT();
	}
	if (key == GLUT_KEY_LEFT){
		LEFT();
	}
	if(key == GLUT_KEY_UP){
		UP();
	}
	if(key == GLUT_KEY_DOWN){
		DOWN();
	}
}


void RGBAnimations(){
	r = rand() % 255; g = rand() % 255; b = rand() % 200;
}


void UP(){

	if (ourCraft.ourY<600 || ourCraft.bulletY < 600 + 38){
	  ourCraft.ourY += 10;
	  ourCraft.bulletY += 10;
	}
}

// our craft goes down.our craft cannot go less than 10 pixel in Y axis.
void DOWN(){
	ourCraft.ourY -= 10;
	ourCraft.bulletY -= 10;
	if(ourCraft.ourY < 10 || ourCraft.bulletY < 10+38){
		ourCraft.ourY = 10;
		ourCraft.bulletY = 10 + 38;
	}
}

// our craft goes left.our craft can not go less than 5 pixel in X axis
void LEFT(){
	ourCraft.ourX -= 10;
	ourCraft.bulletX -= 10;
	//ourCraft.fireBallX -=10;
	if(ourCraft.ourX < 5 || ourCraft.bulletX < 5 - 38){
		ourCraft.ourX = 5;
		ourCraft.bulletX = 5 + 38;
	}	
}

// our craft goes right.our craft cannot go more than 1120 pixel in X axis.
void RIGHT(){
	ourCraft.ourX += 10;
	ourCraft.bulletX += 10;
	//ourCraft.fireBallX +=10;
	if(ourCraft.ourX > 1200-80 || ourCraft.bulletX > 1120 + 38){
		ourCraft.ourX = 1120;
		ourCraft.bulletX = 1120 + 38;
	}	
}

void fire(){
	if(fireBullet){
		ourCraft.bulletY += 40;
		if(ourCraft.bulletY > 690){
			ourCraft.bulletY = (ourCraft.ourY + 45);
		}
	}
}


int main()
{
	enemyGenerate();
	iInitialize(screenWidth, screenHeight, "UFO");

	iSetTimer(100, RGBAnimations); 
	iSetTimer(4, fire);
	iSetTimer(300, enemyMove);

	

	//Ingame images::
	ourShip   = iLoadImage("images\\ourShip.png");
	enemyship= iLoadImage("images\\bomb.png");
	image[0] = iLoadImage("images\\back.png");
	image[2] = iLoadImage("images\\life.png");
	image[3] = iLoadImage("images\\bullet.png");
	
	//buttonimages
	button[0] = iLoadImage("images\\button\\newgame.png");
	button[1] = iLoadImage("images\\button\\highscore.png");
	button[2] = iLoadImage("images\\button\\option.png");
	button[3] = iLoadImage("images\\button\\about.png");
	button[4] = iLoadImage("images\\button\\quit.png");


	button[5] = iLoadImage("images\\button\\newgame2.png");
	button[6] = iLoadImage("images\\button\\highscore2.png");
	button[7] = iLoadImage("images\\button\\option2.png");
	button[8] = iLoadImage("images\\button\\about2.png");
	button[9] = iLoadImage("images\\button\\quit2.png");

	//Page iMAGES:
	menupage = iLoadImage("images\\gamecover.png");
	instructionpage = iLoadImage("images\\instruction.png");
	aboutpage = iLoadImage("images\\credits.png");
	highscorepage= iLoadImage("images\\highscore.png");
	loginpage= iLoadImage("images\\login.png");
	back=iLoadImage("images\\backButton.png"); //back button


	readHighScore();

	iStart(); // it will start drawing

	return 0;
}

