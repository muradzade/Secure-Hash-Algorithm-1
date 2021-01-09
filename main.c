#include <stdio.h>
#include "sha1.h"



int main(int argc, char *argv[]) {
	
	unsigned char filePath[256];
	unsigned int keys[4];
	int i;
	unsigned int initialHashes[]={ 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};   

		
	keys[0] = 0x5A827999;
	keys[1] = 0x6ED9EBA1;
	keys[2] = 0x8F1BBCDC;
	keys[3] = 0xCA62C1D6;
	
		                   
	printf("Sifrelenecek dosyayi giriniz : ");
	scanf("%s",filePath);          
	/*		                           
	printf("\n4 adet hex formatinda anahtar giriniz (orn: 45a2b3cf)\n");
	for(i=0;i<4;i++)
	{
		printf("\n0x");		
		scanf("%x",&keys[i]);
	}	
	*/
	//Sifreleme
	char *result = sha1(filePath,keys,initialHashes);
	
	printf("\nSifreli mesaj:\n%s",result);
	
	free(result);
	getch();
	return 0;
}
