#ifndef HIGHSCORE_H_INCLUDED
#define HIGHSCORE_H_INCLUDED

int index;
int leaderBoard;
int typeScore;
char leaderboard_str[20],lbScore_str[7];
int highscorepage;


struct leaderBoard{
    char name[25];
    int scores;
}lb[10];


/*read the highest all scores from the COP file;called from iMain and iDraw method;return type void*/
void readHighScore(){
	FILE *fp = fopen("highscore.txt", "r");
   
    while(fscanf(fp,"%s %d",lb[index].name,&lb[index].scores)!=EOF)
		  index++;
}

void sortScores()
{
	iClear();

	int temp;
    char s[20];

	iShowImage(0,0, 1200,690 ,highscorepage);

    for (int i = 0; i < 10 - 1; i++){
       for (int j = 0; j<10-1-i; j++){
          if (lb[j].scores < lb[j+1].scores){
                    temp = lb[j].scores;
                    lb[j].scores = lb[j + 1].scores;
                    lb[j + 1].scores = temp;
                    strcpy(s, lb[j].name);
                    strcpy(lb[j].name, lb[j + 1].name);
                    strcpy(lb[j + 1].name, s);
		  }
	   }
	}

	iSetColor(25, 255, 100);
    for(int i=0,p=270,q=400;i<10;i++){

           strcpy(leaderboard_str,lb[i].name);
           iText(p,q,leaderboard_str,GLUT_BITMAP_TIMES_ROMAN_24);
		   sprintf(lbScore_str,"%d",lb[i].scores);
		    //_itoa(lb[i].scores,lbScore_str,10);
           // strcpy(leaderboard_str,lb[i].name);
		   iText(p+617,q,lbScore_str,GLUT_BITMAP_TIMES_ROMAN_24);
		   printf("%s%d",lb[i].name,lb[i].scores);
		   q-=40;
	}
}


#endif // HIGHSCORE_H_INCLUDED
