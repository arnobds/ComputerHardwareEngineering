#include <stdint.h>

// SPI
void DisplayOn(void);
uint8_t spi_send_recv(uint8_t data);
void spi_Reset(void);
void spi_Config(void);

#define SPI_DISPLAY_MODE_COMMAND (PORTF &= 0xffffffef) // Pin 39 (D/C#) is RF4, set to 0 is Command Mode
#define SPI_DISPLAY_MODE_DATA (PORTF |= 0x10) // 1 is Data Mode

// Display functions
void render();
void WriteText(char* str, uint8_t page, uint8_t col);
uint8_t screen[32][128];
void CharToArr(char c, uint8_t* ca);
void screen_flush(void);
// Game modes
void gameState0(void);
void gameState1(void);
void gameState2(void);
void gameState4(void);

void init( void );
void work( void );
// Generating pipes
void gnPipe(int pipePos, int randOffset1, int randOffset2, int pipeThickness, int *tip);
void gnrndPipes(void);

int getbtns(void);

// Crash and Score
extern int currentScore;
extern int Highscore;
extern int Second;
extern int Third;
void zeroAllScores(void);
void updScore(void);
void readScore(int score, int line, int position);
int crash(void);
void scores(void);
void scorestwo(void);

// Timer and delay
void delay( int ms );