
#include <stdint.h>
#include <pic32mx.h>
#include "miniproj.h"
// Set Vdd Enable (Pin 38, RF6)
#define SPI_POWER_ON_VDD (PORTFCLR = 0x40)

// VBAT Enable (Pin 40, RF4)
#define SPI_POWER_ON_VBAT (PORTFCLR = 0x20)

// Reset Pin (Pin 10, RG9) Active Low
#define SPI_RESET_ON (PORTGCLR = 0x200)
#define SPI_RESET_OFF (PORTGSET = 0x200)

uint8_t font[] = {
	// 'A'
	0,0,0,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,1,1,1,0,0,
	0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,
	// 'B'
	0,0,1,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,1,1,0,0,0,
	0,0,1,1,1,1,0,0,
	0,0,1,0,0,0,1,0,
	0,0,1,1,1,1,0,0,
	// 'C'
	0,0,0,1,1,1,0,0,
	0,0,1,0,0,0,1,0,
	0,1,0,0,0,0,0,0,
	0,1,0,0,0,0,0,0,
	0,0,1,0,0,0,1,0,
	0,0,0,1,1,1,0,0,
	// 'D'
	0,1,1,1,1,0,0,0,
	0,1,0,0,0,1,0,0,
	0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,
	0,1,0,0,0,1,0,0,
	0,1,1,1,1,0,0,0,
	// 'E'
	0,0,1,1,1,1,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,1,1,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,1,1,1,0,0,
	// 'F'
	0,0,1,1,1,1,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,1,1,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,0,0,0,0,0,
	// 'G'
	0,0,0,1,1,1,0,0,
	0,0,1,0,0,0,1,0,
	0,1,0,0,0,0,0,0,
	0,1,0,0,1,1,1,0,
	0,1,0,0,0,0,1,0,
	0,0,1,1,1,1,1,0,
	// 'H'
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,1,1,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	// 'I'
	0,0,0,1,1,1,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,1,1,1,0,0,
	// 'J'
	0,0,0,0,1,1,1,0,
	0,0,0,0,0,1,0,0,
	0,0,0,0,0,1,0,0,
	0,0,0,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
	// 'K'
	0,1,0,0,1,0,0,0,
	0,1,0,1,0,0,0,0,
	0,1,1,0,0,0,0,0,
	0,1,0,1,0,0,0,0,
	0,1,0,0,1,0,0,0,
	0,1,0,0,0,1,0,0,
	// 'L'
	0,0,1,0,0,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,1,1,1,0,0,
	// 'M'
	0,1,0,0,0,0,1,0,
	0,1,1,0,0,1,1,0,
	0,1,0,1,1,0,1,0,
	0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,
	// 'N'
	0,1,0,0,0,0,1,0,
	0,1,1,0,0,0,1,0,
	0,1,0,1,0,0,1,0,
	0,1,0,0,1,0,1,0,
	0,1,0,0,0,1,1,0,
	0,1,0,0,0,0,1,0,
	// 'O'
	0,0,0,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
	// 'P'
	0,0,1,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,1,1,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,0,0,0,0,0,
	// 'Q'
	0,0,0,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,1,0,0,0,0,1,0,
	0,1,0,0,1,0,1,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,1,0,
// 'R'
	0,0,1,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,0,1,0,
// 'S'
	0,0,0,1,1,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,0,1,1,0,0,0,
	0,0,0,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
// 'T'
	0,0,1,1,1,1,1,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
// U
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
// 'V'
	0,1,0,0,0,0,1,0,
	0,1,0,0,0,0,1,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
// 'W'
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	0,1,0,0,0,0,1,0,
	0,1,0,1,1,0,1,0,
	0,1,0,1,1,0,1,0,
	0,0,1,0,0,1,0,0,
// 'X'
	0,1,0,0,0,0,1,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
	0,0,0,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,1,0,0,0,0,1,0,
// 'Y'
	0,0,1,0,0,0,1,0,
	0,0,1,0,0,0,1,0,
	0,0,0,1,1,1,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
// 'Z'
	0,0,1,1,1,1,0,0,
	0,0,0,0,0,1,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,1,1,1,0,0,
// '0'
	0,0,0,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
// '1'
	0,0,0,0,1,0,0,0,
	0,0,0,1,1,0,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,1,1,1,0,0,
// '2'
	0,0,0,1,1,1,0,0,
	0,0,1,0,0,0,1,0,
	0,0,0,0,0,0,1,0,
	0,0,0,0,1,1,0,0,
	0,0,0,1,0,0,0,0,
	0,0,1,1,1,1,1,0,
// '3'
	0,0,1,1,1,1,1,0,
	0,0,0,0,0,1,0,0,
	0,0,0,0,1,1,0,0,
	0,0,0,0,0,0,1,0,
	0,0,1,0,0,0,1,0,
	0,0,0,1,1,1,0,0,
// '4'
	0,0,0,0,0,1,0,0,
	0,0,0,0,1,1,0,0,
	0,0,0,1,0,1,0,0,
	0,0,1,1,1,1,1,0,
	0,0,0,0,0,1,0,0,
	0,0,0,0,0,1,0,0,
// '5'
	0,0,1,1,1,1,1,0,
	0,0,1,0,0,0,0,0,
	0,0,1,1,1,1,0,0,
	0,0,0,0,0,0,1,0,
	0,0,1,0,0,0,1,0,
	0,0,0,1,1,1,0,0,
// '6'
	0,0,0,1,1,0,0,0,
	0,0,1,0,0,0,0,0,
	0,0,1,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
// '7'
	0,0,1,1,1,1,0,0,
	0,0,0,0,0,1,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,0,1,0,0,0,
	0,0,0,1,0,0,0,0,
	0,0,0,1,0,0,0,0,
// '8'
	0,0,0,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
// '9'
	0,0,0,1,1,0,0,0,
	0,0,1,0,0,1,0,0,
	0,0,1,0,0,1,0,0,
	0,0,0,1,1,1,0,0,
	0,0,0,0,0,1,0,0,
	0,0,0,1,1,0,0,0,
};



/*
========================== 23.3.3.1 MASTER MODE OPERATION ==============================
Perform the following steps to set up the SPI module for the Master mode operation:
1. Disable the SPI interrupts in the respective IECx register.
2. Stop and reset the SPI module by clearing the ON bit.
3. Clear the receive buffer.
4. Clear the ENHBUF bit (SPIxCON<16>) if using Standard Buffer mode or set the bit if using
Enhanced Buffer mode.
5. If SPI interrupts are not going to be used, skip this step and continue to step 5. Otherwise
the following additional steps are performed:
a) Clear the SPIx interrupt flags/events in the respective IFSx register.
b) Write the SPIx interrupt priority and subpriority bits in the respective IPCx register.
c) Set the SPIx interrupt enable bits in the respective IECx register.
6. Write the Baud Rate register, SPIxBRG.
7. Clear the SPIROV bit (SPIxSTAT<6>).
8. Write the desired settings to the SPIxCON register with MSTEN (SPIxCON<5>) = 1.
9. Enable SPI operation by setting the ON bit (SPIxCON<15>).
10. Write the data to be transmitted to the SPIxBUF register. Transmission (and reception) will
start as soon as data is written to the SPIxBUF register.


SPIxSTAT bit 6 SPIROV: Receive Overflow Flag bit
1 = A new data is completely received and discarded. The user software has not read the previous data in
the SPIxBUF register.
0 = No overflow has occurred
This bit is only set by hardware. It can be cleared by writing a zero, preferably with the command
SPIxSTATCLR = 1<<6. It can also be cleared by disabling and re-enabling the module using the
SPIxCON.ON bit.


Kristian Ruth
*/
void spi_Config(void)
{
	TRISECLR = 0xFF;
	TRISFCLR = 0x70;  //  Set D/C#, VDD, VCC as outputs
	TRISGCLR = 0x300; // Set SDIN as output (RG8), and RES# (RG9)
	PORTG |= 0x200;

	SPI2CON = 0;
	/* == Disable SPI Interrupts (SPI2RXIE, SPI2TXIE, SPI2EIE) ==*/
	IEC(1) &= 0xffffff1f;
	/* == Stop and reset the SPI module by clearing the ON bit == */
	SPI2CONCLR = 0x8000;
	/* == Clear the receive buffer == */
	SPI2BUF = 0;
	/* == Clear the ENHBUF bit (SPIxCON<16>) if using Standard Buffer mode or set the bit if using Enhanced Buffer mode == */
	SPI2CONCLR = 0x10000;
	/* == Write the Baud Rate register, SPIxBRG == */
	SPI2BRG = 4;
	/* == Clear the SPIROV bit (SPIxSTAT<6>) == */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
	SPI2CONSET = 0x40;
	/* == Write the desired settings to the SPIxCON register with MSTEN (SPIxCON<5>) = 1 == */
	SPI2CONSET = 0x20;
	/* == Enable SPI operation by setting the ON bit (SPIxCON<15>) == */
	SPI2CONSET = 0x8000;
}
/*
spi_send_recv:

Copyright (c) 2015, Axel Isaksson
Copyright (c) 2015, F Lundevall

If you're a student, and you have modified one or more files,
you must add your name here.
with permission of Kristian Ruth
with permission of Lennart Sturm
Arnob Dey Sarker
Zaid Alrabaia

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
uint8_t spi_send_recv(uint8_t data)
{
	while (!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while (!(SPI2STAT & 1));
	return SPI2BUF;
}

void spi_Reset(void) {
	SPI_RESET_ON;
	delay(1);
	SPI_RESET_OFF;
	delay(1);
}
/*
== Power on sequence ==
1.Apply power to VDD.
2.Send Display Off command.
3.Initialize display to desired operating mode.
4.Clear screen.
5.Apply power to VBAT.
6.Delay 100ms.
7.Send Display On command.
*/
void DisplayOn(void)
{
	spi_Config();

	SPI_POWER_ON_VDD;
	delay(10); // 1 millisecond

	SPI_DISPLAY_MODE_COMMAND;
	spi_send_recv(0xAE);

	SPI_RESET_ON;
	delay(1);
	SPI_RESET_OFF;
	delay(1);

	/* == Enable Charge Pump == */
	spi_send_recv(0x8D); // Charge Pump Setting
	spi_send_recv(0x14); // Enable Charge Pump

	/* == Set Pre-Charge Period == */
	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

	SPI_POWER_ON_VBAT;
	delay(10);

	spi_send_recv(0xAF);

	spi_send_recv(0xA1);
	spi_send_recv(0xC8);

	spi_send_recv(0xDA);
	spi_send_recv(0x20);

	// spi_send_recv(0x2E); // Deactivate Scroll

	spi_send_recv(0x20); // Horizontal Address Mode
	spi_send_recv(0x00);

	spi_send_recv(0x81);
	spi_send_recv(0xff);

	spi_send_recv(0x22);
	spi_send_recv(0x0);
	spi_send_recv(0x3);

}
//Our part
void render()
{
    uint8_t val; // Variable to store the 8-bit value for each column
    int page, col, row;

    SPI_DISPLAY_MODE_DATA; // Set display mode to data

    for (page = 0; page < 4; page++) { // Iterate over 4 pages
        for (col = 0; col < 128; col++) { // Iterate over 128 columns
            val = 0; // Reset the value for each new column
            for (row = 0; row < 8; row++) { // Iterate over 8 rows in a page
                // Combine the bits for each row into a single 8-bit value
                val |= screen[page * 8 + row][col] << row;
            }
            spi_send_recv(val); // Send the 8-bit value to the display
        }
    }
}


/*
Description: Selects and returns relevant section of font array based on parameter
Param: ASCII byte representing a number or a letter, 48 item array
Result: 48 item array (0/1), representing a matrix 8 cols x 6 rows (to leave some whitespace top & bottom)
*/
void CharToArr(char chara, uint8_t* outArray) {
    int asciiVal = (int) chara; // Convert character to its ASCII value
    int place; // Offset to find the correct character in the font array
    int i, j;
    // Initialize the character array to zero
    for (i = 0; i < 48; i++) {
        outArray[i] = 0;
    }

    // Determine the offset in the font array based on the ASCII value
    if (asciiVal <= 0x39) { // If the character is a number (0-9)
        place = 26 + (asciiVal - '0'); // Numbers start after 26 letters
    } else if (asciiVal <= 0x5A) { // If the character is an uppercase letter (A-Z)
        place = asciiVal - 'A'; // Calculate offset from 'A'
    }

    // Copy the font data for the specified character into the character array
    for (j = 0; j < 48; j++) {
        outArray[j] = font[j + 48 * place];
    }
}


void WriteText(char* txt, uint8_t pg, uint8_t col) {
    int charIndex = 0; // Index of the current character in the text
    uint8_t chBitShape[48]; // Bitmap for a single character, assuming each character is represented by 48 bits

    pg &= 3; // Ensure the page number is between 0 and 3
    uint8_t startRow = pg * 8 + 1; // Calculate starting row, adding 1 for spacing
    uint8_t currentRow, currentCol;
	int i;
	int j;
    // Process each character in the string
    while (txt[charIndex] != '\0') { // Check for the end of the string
        CharToArr(txt[charIndex], chBitShape); // Convert current character to its bitmap representation

        for (i = 0; i < 6; i++) { // Iterate over rows for each character
            for (j = 0; j < 8; j++) { // Iterate over columns for each character
                // Calculate the current row and column on the screen
                currentRow = startRow + i;
                currentCol = col + j + charIndex * 8;

                // Place the character bitmap onto the screen
                screen[currentRow][currentCol] = chBitShape[i * 8 + j];
            }
        }
        charIndex++; // Move to the next character in the text
    }
}

void screen_flush(void){
    int i,j;
    for(i=0;i<32;i++){
        for(j=0;j<128;j++){
                screen[i][j]=0;

        }
    }
}

//functions for the buttons
int getbtns(void){  //btns 4 3 2
    int value= PORTD & 0xE0; // 0xE0 equals to 11100000
    value= value>>5;
    return value;
}

void delay( int ms )
{
  int i;
  while( ms > 0 )
  {
    ms = ms - 1;
    for( i = 0; i < 4900; i = i + 1 )
    {

    }
  }
}

