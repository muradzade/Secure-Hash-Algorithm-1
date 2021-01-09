#ifndef sha1_h
#define sha1_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef union{
	unsigned char _64x8[64];
	unsigned int _16x32[18];	
}Plaintext;

void padding(Plaintext *,unsigned int );
void addLength(Plaintext *,unsigned long long );
void extendMessage(Plaintext *,unsigned int *);
unsigned int func(int , unsigned int , unsigned int , unsigned int );
void hashBlock(Plaintext *,unsigned int *,unsigned int *);
char* sha1(unsigned char *,unsigned int *,unsigned int *);


#endif
