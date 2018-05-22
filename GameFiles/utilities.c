// Useful functions that can be used anywhere in the game

#include <lpc17xx.h>
#include <math.h>
#include <stdlib.h>
#include "utilities.h"
#include "GLCD.h"

#define BG		Black
#define PC		Cyan
#define GF      White
#define EC      Red

int gameOver = 0;

unsigned short playerBitmap[100] = {  BG, BG, BG, BG, PC, PC, BG, BG, BG, BG,
                                      BG, BG, BG, PC, PC, PC, PC, BG, BG, BG,
                                      BG, BG, PC, PC, PC, PC, PC, PC, BG, BG,
                                      BG, PC, PC, PC, PC, PC, PC, PC, PC, BG,
                                      PC, PC, PC, PC, PC, PC, PC, PC, PC, PC,
                                      PC, PC, PC, PC, PC, PC, PC, PC, PC, PC,
                                      BG, PC, PC, PC, PC, PC, PC, PC, PC, BG,
                                      BG, BG, PC, PC, PC, PC, PC, PC, BG, BG,
                                      BG, BG, BG, PC, PC, PC, PC, BG, BG, BG,
                                      BG, BG, BG, BG, PC, PC, BG, BG, BG, BG };

unsigned short enemyBitmap[100] = {   BG, BG, BG, BG, EC, EC, BG, BG, BG, BG,
                                      BG, BG, BG, EC, EC, EC, EC, BG, BG, BG,
                                      BG, BG, EC, EC, EC, EC, EC, EC, BG, BG,
                                      BG, EC, EC, EC, EC, EC, EC, EC, EC, BG,
                                      EC, EC, EC, EC, EC, EC, EC, EC, EC, EC,
                                      EC, EC, EC, EC, EC, EC, EC, EC, EC, EC,
                                      BG, EC, EC, EC, EC, EC, EC, EC, EC, BG,
                                      BG, BG, EC, EC, EC, EC, EC, EC, BG, BG,
                                      BG, BG, BG, EC, EC, EC, EC, BG, BG, BG,
                                      BG, BG, BG, BG, EC, EC, BG, BG, BG, BG };	

unsigned short blankBitmap[100] = {	  BG, BG, BG, BG, BG, BG, BG, BG, BG, BG,
                                      BG, BG, BG, BG, BG, BG, BG, BG, BG, BG,                                      
                                      BG, BG, BG, BG, BG, BG, BG, BG, BG, BG,                                      
                                      BG, BG, BG, BG, BG, BG, BG, BG, BG, BG,                                      
                                      BG, BG, BG, BG, BG, BG, BG, BG, BG, BG,                                      
                                      BG, BG, BG, BG, BG, BG, BG, BG, BG, BG,                                      
                                      BG, BG, BG, BG, BG, BG, BG, BG, BG, BG,                                      
                                      BG, BG, BG, BG, BG, BG, BG, BG, BG, BG,                                      
                                      BG, BG, BG, BG, BG, BG, BG, BG, BG, BG,                                      
                                      BG, BG, BG, BG, BG, BG, BG, BG, BG, BG };	

unsigned short block100[100] = {      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF };  

unsigned short block200[200] = {      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF,                                      
                                      GF, GF, GF, GF, GF, GF, GF, GF, GF, GF };
    
// Note: THIS DOES NOT HANDLE NEGATIVE EXPONENTS!
int power(int base, int exp) {
    if (exp == 0)
        return 1;
    else if (exp % 2)
        return base * power(base, exp - 1);
    else {
        int temp = power(base, exp / 2);
        return temp * temp;
    }
}

// Bit twiddling thingy for finding log2 of an unsigned 32 bit integer
// From: http://graphics.stanford.edu/~seander/bithacks.html#IntegerLog
int log2Number(uint32_t v){
	
	int r;      // result goes here

	static const int MultiplyDeBruijnBitPosition[32] = 
	{
		0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
		8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
	};

	v |= v >> 1; // first round down to one less than a power of 2 
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;

	r = MultiplyDeBruijnBitPosition[(uint32_t)(v * 0x07C4ACDDU) >> 27];
	
	return r;
}

