#include "sha1.h"

void padding(Plaintext *chunk,unsigned int lastIndex)
{	
	int i;	
	//added 1 after last char and then 0's
	chunk->_64x8[lastIndex]=0x80;// 0x80 = 1000 0000
	
	for(i = lastIndex+1 ; i < 64 ; i++)
	{
		//set padding bits
		chunk->_64x8[i] = 0x00;
	}
}

void addLength(Plaintext *chunk,unsigned long long msgLength)
{
	int i;
	//set length bits to end
	for(i = 56; i < 64 ; i++)
	{		
		chunk->_64x8[i] = (msgLength >> ((63-i)*8)) & 0xff;		
	}
}

void extendMessage(Plaintext *plaintext,unsigned int *extendedMsg)
{
	int i=0;
	//values are repeating from 0 to 16
	for(;i<16;i++)
	{
		extendedMsg[i] = plaintext->_16x32[i];
	}
	for(;i<80;i++)
	{
		extendedMsg[i] = ((extendedMsg[i-3] ^ extendedMsg[i-8] ^ extendedMsg[i-14] ^ extendedMsg[i-16]) << 1);
	}
}

unsigned int func(int i, unsigned int B, unsigned int C, unsigned int D)
{
	if(i>=0 && i<=19)
		return ((B & C) | ((~B) & D));
	else if(i>=20 && i<=39)
		return ( B ^ C ^ D );
	else if(i>=40 && i<=59)
		return (( B & C ) | ( B & D ) | ( C & D ));
	else if(i>=60 && i<=79)
		return ( B ^ C ^ D );
}

void hashBlock(Plaintext *chunk,unsigned int *keys,unsigned int *H)
{
	unsigned int temp, j;
	unsigned int A,B,C,D,E;
	unsigned int *extendedMessage = (unsigned int *) calloc(80,sizeof(unsigned int));
	
	extendMessage(chunk,extendedMessage);

	A = H[0];
	B = H[1];
	C = H[2];
	D = H[3];
	E = H[4];
	//main loop
	for(j=0;j<=79;j++)
	{
		temp = ((A)<<5) + func(j,B,C,D) + E + extendedMessage[j] + keys[j/20];
		E = D;
		D = C;
		C = (B << 30);
		B = A;
		A = temp;
	}
	
	H[0] += A;
	H[1] += B;
	H[2] += C;
	H[3] += D;
	H[4] += E;
	
}

char* sha1(unsigned char *path,unsigned int *keys,unsigned int *H)
{
	unsigned long long i;//index of chunks
	unsigned int j;//index of word
	unsigned long msgLength;
	char ch;
	FILE *fp;
	//each hex number is 4 bit.But we need 1 byte to show it inside string
	//output=160bit=160/4 hex number=40 char and +1 for '\0'
	char *hashResult = (char *) calloc(41,sizeof(char));
	
	Plaintext *chunk=(Plaintext *) calloc(1,sizeof(Plaintext)); 
	
	if((fp = fopen(path,"rb")) == NULL )
	{
		printf("Dosya bulunamadi");
		getch();
		exit(-1);
	}
	
	//get size length
	fseek(fp, 0L, SEEK_END);
	msgLength = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	
	if(msgLength >= pow(2.0 , 64.0))
	{
		printf("Dosya boyutu 2^64 `den kucuk olmali");
		getch();
		exit(-1);
	}

	//max count of chunks = msgLength / (byte size x chunk length) = {2^64bit} / {512bit}
	for(i=0;i<=msgLength/64;i++)
	{
		//get 64 byte into block
		for(j=0;j<64;j++)
		{	
			ch = getc(fp);
			//If it's the last block,we need to add it 1 and 0's 
			if( (i*64+j) >= msgLength )
			{	
				//add 1 and then 0's to the end
				padding(chunk, j);
				//if we did't touch length area(last 64bit) add length and continue
				if(j<56)
				{
					addLength(chunk,msgLength);
				}
				//or we need to add lenth to the new chunk
				else
				{
					hashBlock(chunk,keys,H);

					for(j=0;j<64;j++)
					{
						chunk->_64x8[j]=0x00;
					}

					addLength(chunk,msgLength);					

				}				
				break;
			}
			//put 64 characters in chunk
			chunk->_64x8[j] = ch;
		}
		
		hashBlock(chunk,keys,H);
		//take next chunk
	}

	H[0] = ~(H[0] ^ 0x00);
	H[1] = ~(H[1] ^ 0x00);
	H[2] = ~(H[2] ^ 0x00);
	H[3] = ~(H[3] ^ 0x00);
	H[4] = ~(H[4] ^ 0x00);
	printf("%x\n%x\n%x\n%x\n%x\n",H[0],H[1],H[2],H[3],H[4]);
	sprintf(hashResult,"%x%x%x%x%x\0",H[0],H[1],H[2],H[3],H[4]);
	fclose(fp);
	
	free(chunk);

	return hashResult;
}

