#include <stdio.h>
#include "staaf.h"

int lees(int *start,int *end,Gebruik *stru)
{	FILE *fin;
	int teller=0;
	fin=fopen(BESTN,"r");
	
	
	fread(start,sizeof(int),1,fin);
	fread(end,sizeof(int),1,fin);
	
	int i=0;
	while(1){
	fread(&stru[teller],sizeof(Gebruik),1,fin);
	if(feof(fin)){break;}
	teller++;
	}
	
	fclose(fin);
	return teller; 
}
