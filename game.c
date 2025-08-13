#include <stdint.h>
#include <pic32mx.h>
#include "miniproj.h"

int fishx=15;       //fish initial x position
int fishy=9;        //fish initial y position
int gameState;      //Which game screen
int randNum;        //random number to make it feel random
int difficulty;     //current difficulty
int pipeTh;     //Pipe thickness
int pipeSec=100; 
int pipeFir=60;
int topSec;
int topFir;
int Highscore;      //Highscore
int Second;     //Second HighestScore
int Third;      //Third HighestScore
int currentScore;       //User current score
char initial1 = 'A';
char initial2 = 'A';
char initial3 = 'A';
int initialSelect = 0; // To track which initial is being selected (0, 1, 2)

void gameState4() {
    WriteText("SELECT", 0, 0);
    WriteText("INITIALS", 0, 50);
    char initialsDisplay[4] = {initial1, initial2, initial3, '\0'};
    WriteText(initialsDisplay, 1, 40);

    int btn = getbtns();

    // Button 1: Move to next initial
    if (btn & 0x1) {
        initialSelect++;
        if (initialSelect > 2) {
            initialSelect = 0;
            gameState = 0; // Move to gameState0 after selecting all initials
        }
        delay(200); // Delay to debounce button press
    }

    // Button 2: Increment character
    if (btn & 0x2) {
        if (initialSelect == 0) {
            initial1++;
            if (initial1 > 'Z') initial1 = 'A';
        } else if (initialSelect == 1) {
            initial2++;
            if (initial2 > 'Z') initial2 = 'A';
        } else if (initialSelect == 2) {
            initial3++;
            if (initial3 > 'Z') initial3 = 'A';
        }
        delay(200); // Delay to debounce button press
    }

    // Button 3: Decrement character
    if (btn & 0x4) {
        if (initialSelect == 0) {
            initial1--;
            if (initial1 < 'A') initial1 = 'Z';
        } else if (initialSelect == 1) {
            initial2--;
            if (initial2 < 'A') initial2 = 'Z';
        } else if (initialSelect == 2) {
            initial3--;
            if (initial3 < 'A') initial3 = 'Z';
        }
        delay(200); // Delay to debounce button press
    }
}
void zeroAllScores(void){ //Initially when game is first started set all to zero
    Highscore=0;
    Second=0;
    Third=0;
    currentScore=0;
}

    
  void updScore(void) { //After every death in gameState0
    if (currentScore > Highscore) {
        Third = Second;
        Second = Highscore;
        Highscore = currentScore;
    } else if (currentScore > Second) {
        Third = Second;
        Second = currentScore;
    } else if (currentScore > Third) {
        Third = currentScore;
    }
}


void readScore(int score, int line, int position) { //getting the score and changing it to string because we need to use the ChartoArray method on it
    char scoreString[3]; // Assuming score will be within 3 digits (0-99)
    int temp = score;
    int digitCount = 0;
    int i;
    // Count the number of digits in the score
    do {
        digitCount++;
        temp /= 10;
    } while (temp != 0); // checking how many digits the score is


    if (score == 0) { //if score is just 0 then we skip the for loop and get ascii for 0
        scoreString[0] = '0';
        scoreString[1] = '\0'; 
    } else {
        for (i = digitCount - 1; i >= 0; i--) {         //extracting digits biggest to smallest
            scoreString[i] = '0' + (score % 10); // Convert digit to ascii character, modulo 10 will ensure us getting the last digit
            score /= 10;
        }
        scoreString[digitCount] = '\0'; // Null-terminate the string
    }

    WriteText(scoreString, line, position);
}

const uint8_t stupidFish[5][9]= {   //how the stupidFish will look like const cause we dont want the stupidFish to change
    {1,0,0,0,1,1,1,0,0},
    {1,1,0,1,1,1,1,0,0},
    {1,1,1,1,1,1,1,1,1},
    {1,1,0,1,1,1,1,1,0},
    {1,0,0,0,1,1,1,0,0},
};

 void gnPipe(int pipePos, int randOffset1, int randOffset2, int pipeThickness, int *tip) {
    int i, j;
    for (i = 0; i < 7; i++) { // i is thickness, j is length
        for (j = 0 - (randOffset1 % 6); j < 6 + pipeThickness; j++) {
            screen[j + (randOffset1 % 6)][pipePos + i] = 1;
            *tip = j + (randOffset1 % 6);
        }
        for (j = 20; j < 32 - (randOffset2 % 6); j++) {
            screen[j + (randOffset2 % 6)][pipePos + i] = 1;
        }
    }
}

void gnrndPipes() { 
    int randOffset1 = randNum % 6;
    int randOffset2 = randNum % 8;

    gnPipe(pipeSec, randOffset1, randOffset1, pipeTh, &topSec);
    gnPipe(pipeFir, randOffset2, randOffset2, pipeTh, &topFir);
}


int crash(){
    if(fishy >= 28 || fishy<0 || fishx>127 || fishx<0){ //out of bound,2 to not make it crash 
        fishy=15;
        fishx=9;
        pipeSec=100;
        pipeFir=60;
        gameState=2;
        delay(500);
    }
    if((fishx > pipeFir-4 && fishx < pipeFir+4) && (fishy <= topFir || fishy >= (topFir+12))){  // if the fish is moving on the x axis the score isnt updating
        fishy=15;
        fishx=9;
        pipeSec=100;
        pipeFir=60;
        gameState=2;
        delay(500);
    }
    if((fishx > pipeSec-4 && fishx < pipeSec+4) && (fishy <= topSec || fishy >= (topSec+12))){
        fishy=15;
        fishx=9;
        pipeSec=100;
        pipeFir=60;
        gameState=2;
        delay(500);
    }
}

void scores(){
    if((fishx > pipeFir-3 && fishx < pipeFir+3) && !(fishy <= topFir || fishy >= (topFir+14-pipeTh)) ){
        currentScore++;
        delay(50);   
    }
   if( (fishx > pipeSec-3 && fishx < pipeSec+3)&& !(fishy <= topSec || fishy >= (topSec+14-pipeTh))){
        currentScore++;
        delay(50);
   }
}

void scorestwo(){
    if((fishx > pipeFir-4 && fishx < pipeFir+4) && !(fishy <= topFir || fishy>=(topFir+14-pipeTh)) ){
        currentScore++;
        delay(50);   
    }
   if( (fishx > pipeSec-4 && fishx < pipeSec+4) && !(fishy <= topSec || fishy >= (topSec+14-pipeTh))){
       currentScore++;
        delay(50);
   }
}

void gameState0(){
    updScore();
    WriteText("HS1", 0, 0);
    readScore(Highscore, 0, 40);
    WriteText("HS2", 0, 64);
    readScore(Second, 0, 104);
    WriteText("HS3", 1, 0);
    readScore(Third, 1, 40);
    
    // Display initials
    char initialsDisplay[4] = {initial1, initial2, initial3, '\0'};
    WriteText(initialsDisplay, 1, 90); // Change the position as needed

    WriteText("FLAPPY", 2, 20);
    WriteText("FISH", 2, 76);
    WriteText("PRESS", 3, 0);
    WriteText("BTN2", 3, 45);
    currentScore = 0;
    difficulty = 0;
    pipeTh = 0;
    int btn = getbtns();
    if (btn & 0x1){
        gameState = 1;
    }
}


void gameState1(){
    difficulty = 0;
    int i;
    int j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 5; j++) {
            screen[fishy + j][fishx + i] = stupidFish[j][i];
        }
    }
    gnrndPipes();
    int btn= getbtns();
    if(btn & 1){
        fishy--;//fish jumping
        delay( 100 ) ;
    }
    else{
        fishy++;//fishs falling down
        delay(150);
    }
    if(btn & 1){ //move right 
        fishx++;
    }
    if(btn & 4){//move left
        fishx--;
    }
    pipeSec--;
    pipeFir--;
    pipeSec--;
    pipeFir--;
    pipeSec--;
    pipeFir--;
    pipeSec--;
    pipeFir--;
    if(currentScore >= 5){
        pipeSec--;
        pipeFir--;
    }
    if(currentScore >= 10){
        pipeSec--;
        pipeFir--;
    }

    if(currentScore >= 15){
        pipeSec--;
        pipeFir--;
    }

    if(currentScore >= 25){
        pipeSec--;
        pipeFir--;
    }

    if(pipeSec<=8){
        pipeSec=100;
    }
    if(pipeFir<=8){
        pipeFir=100;
    }
    if(fishx>pipeSec+5&&fishx<pipeSec+8){
        difficulty++;
    }
    if(difficulty==1){
        pipeTh++;
        difficulty=0;
    }
    if(pipeTh>=5){
        pipeTh=5;
    }
    if(currentScore<10){
            scores();
        }
        else{
            scorestwo();
        }
}

void gameState2(){
    WriteText("FISH",0,5);
    WriteText("DIED",0,41);
    WriteText("YOU",1,5);
     WriteText("SCORED",1,35);
     WriteText("PRESS",2,5);
    WriteText("BTN3",2,50);
     WriteText("GOOD",3,0);
      WriteText("JOB",3,37);
     char initialsDisplay[4] = {initial1, initial2, initial3, '\0'};
    WriteText(initialsDisplay, 3, 70); // Change the position as needed
    readScore(currentScore,1,86);
    int btn= getbtns();
    if(btn & 0x2){
        gameState=0;
    }

}

void init(){
    TRISD |=0xE0;//btn 2-4
    TRISF|=0x2;//btn 1
    DisplayOn();//turning on the display
    screen_flush();
    gameState=4;
    zeroAllScores();
    currentScore=0;
    randNum=31;
    difficulty=0;
    pipeTh=0;
    int fishx=15;
    int fishy=9;
}

void work(){
    screen_flush();
     if (gameState == 4) {
        gameState4();
        render();
    }
    if(gameState==1){
        gameState1();
        crash();
        
        render();
        randNum++;
    }
    if(gameState==0){
        gameState0();
        render();

    }
    if(gameState==2){
        gameState2();
        render();
    }
}