/*
*Jonathan Sharman
*V00657709
*SENG 265 assignment 1
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
/*Declare compile time constants*/
#define MAX_NUM_EXCLUSION_WORDS 20
#define MAX_LEN_EXCLUSION_WORD 20
#define MAX_NUM_TO_BE_INDEXED 100
#define MAX_LEN_OF_LINE_2B_INDEXED 70
#define MAX_NUM_WORDS 35 /*single char words*/
/*Declare global variables  */
char exclusionWords[MAX_NUM_EXCLUSION_WORDS][MAX_LEN_EXCLUSION_WORD];
char lines2BIndexed[MAX_NUM_TO_BE_INDEXED][MAX_NUM_WORDS][MAX_LEN_OF_LINE_2B_INDEXED];
int *indexOfFirstReal;
char *uppercaseString;
int *lastWordToBeIndexed;

/*Declare functions to be used*/
int wordExcl(int,int);
int isWordLow(int,int,int, int);
int * smallestWord(int, int);
int * firstRealWord();
char * makeStringUpper(char *);
int * lastWord();

int main (int argc, char **argv) {
	

	/* temporary array*/
	char temp[MAX_LEN_OF_LINE_2B_INDEXED];		
	
	/* use scanf() to read the data into the program */	
	/* use a loop to fill the arrays */	
	scanf("%s",temp);
	scanf("%s",temp);
	scanf("%s",temp);
	
	int i = 0;
	int length;

	/*This works for the single word strings*/
	//do {	
	while ( strncmp(temp,"::",MAX_LEN_EXCLUSION_WORD)!=0 && i< MAX_NUM_EXCLUSION_WORDS) {
		strncpy(exclusionWords[i], temp , MAX_LEN_EXCLUSION_WORD);
		scanf("%s",temp);
		i++;
	};// while ( strncmp(temp,"::",MAX_LEN_EXCLUSION_WORD)!=0 && i< MAX_NUM_EXCLUSION_WORDS) ;
	/*Scan the lines to be indexed into the program */
	/*Tokenize the strings in lines to be indexed*/
	getchar();/*This function gets rid of the new line whitespace*/
	i = 0;
	int k; /* position in word*/
	int l; /* word number     */
	while ( scanf("%[^\n]",temp)>=0 &&  i < MAX_NUM_TO_BE_INDEXED) {
		/*Temp is now the line.  Use scanf to split it into words*/
		length = strlen(temp);
		if (strncmp(temp,"::",MAX_LEN_EXCLUSION_WORD)!=0){ 
			k=0;
			l=0;
			for (int j =0; j<length;j++){
				if (temp[j]!=' '){			
					lines2BIndexed[i][l][k] = temp[j];
					k++;
				} else {
					l++;
					k = 0;
				};
			};
			i++;		
		};
		getchar();
		
	};
	/*This array returns the next word we want indexed and printed*/
	int *wordToBeIndexed; 	
	
	/*Indices of previous word indexed*/
	int iprev=-1;
	int lprev=-1;
	/*Run this to find the last index word to be printed
	(will be needed for smallest word funtion to work properly) */
	lastWordToBeIndexed = lastWord();
	
	/*Now loop, always finding the next smallest index word, then print line.
	Terminate when no word is found less than prev word. */
	do {
		/*gets the coord of the next word to be indexed*/		
		wordToBeIndexed = smallestWord(iprev, lprev);
		/*assign the current word to prev*/
		iprev = wordToBeIndexed[0];
		lprev = wordToBeIndexed[1];		
		/*print that line with the index word in caps*/
		uppercaseString = makeStringUpper(lines2BIndexed[iprev][lprev]);		
		l=0;
		while (lines2BIndexed[iprev][l][0]){
			if (l>0){
				printf(" ");
			}			
			if (lprev==l){			
				printf("%s",uppercaseString);
			} else {
				printf("%s", lines2BIndexed[iprev][l]);
			}		
			l++;
		};
		printf("\n");
	} while (wordToBeIndexed[2]);
	

}

/******************/
/*Helper functions*/
/******************/

/*This function determines which word is lower alphabetically*/
int isWordLow(int line1, int word1,int line2, int word2){
	/*return -ve if worda is earlier alphabetically than wordb*/
	/*return +ve if worda is later alphabetically than wordb*/
	/*return 0 if they are the same word */
	//Compare first by alphabetical, then by line number, then by word number
	//This ensures repeats of the same word at different spots is not ignored
	int returnValue = strncmp(lines2BIndexed[line1][word1], lines2BIndexed[line2][word2], MAX_LEN_OF_LINE_2B_INDEXED);
	if (!returnValue ){
	// reaches here iff returnValue is 0
			if (line1 > line2){
				returnValue = +1;
			} else if (line1 < line2){
				returnValue = -1;
			} else if (word1 > word2 ) {
				returnValue = +1;
			} else if (word1 < word2 ){
				returnValue = -1;
			}
	}
	
	
//	return strncmp(lines2BIndexed[line1][word1], lines2BIndexed[line2][word2], MAX_LEN_OF_LINE_2B_INDEXED);
	return returnValue;	
}

/*This function checks if word number 'k' on line 'l' is to be excluded*/	
int wordExcl(int line, int word){
	//returns 1 if excluded
	int i = 0;	
	int returnInt = 0;	
	while (	exclusionWords[i][0]  ) {
		if (0 == strncmp(lines2BIndexed[line][word], exclusionWords[i], MAX_LEN_OF_LINE_2B_INDEXED)) {
			returnInt = 1;
			break;
		};			
		i++;
	};	
	return returnInt;
}

/*Find smallest non indexed word in the array*/
/*If line prev is -1 it means there is no previous word*/
int * smallestWord(int linePrev, int wordPrev){
	int i;
	int l;
	static int test[3];

	test[0] = lastWordToBeIndexed[0];/*This is the line the word is on*/
	test[1] = lastWordToBeIndexed[1];/*This is the word in the line*/
	test[2]	= 0;/*This tells us if the function has been called*/	

	//This edge case is if there was no previous line?
	if( linePrev ==-1){
		i=0;
		while (lines2BIndexed[i][0][0]) {
			l=0;
			while (lines2BIndexed[i][l][0]){
				/*Check that the word isn't excluded*/
				/*No word indexed yet*/		
				//test to figure out why rich isn't counted in test 8			
			
				if ( (wordExcl(i, l) != 1) & (isWordLow(test[0], test[1], i, l) > 0) ){						
					test[0] = i;
					test[1] = l;
					test[2] = 1;
				};
				l++;
			};
			i++;
		};	
	} else {
		
		/*loop over the entire array of words updating the test 
		vars with earliest non indexed word. */
		i=0;
		while (lines2BIndexed[i][0][0]) {
			l=0;
			while (lines2BIndexed[i][l][0]){
				/*Check that the word isn't excluded*/
				/*Find the earliest word not yet indexed*/
				/*Check that the new word is ahead of the previous one indexed*/				
				if (  (wordExcl(i, l) != 1) 
				& (isWordLow(linePrev, wordPrev, i, l) < 0) 
				& (isWordLow(test[0], test[1], i, l) > 0)  
				){ 												
						test[0] = i;
						test[1] = l;
						test[2] = 1;
				};
				l++;
			};
			i++;
		};

	};
	return test;
}

/*Calculates the index of the first non excluded word*/
int * firstRealWord(){
	int i;
	int l;
	static int ret[2];
	ret[0]=0;
	ret[1]=0;	
	i=0;
	while (lines2BIndexed[i][0][0]) {
		l=0;
		while (lines2BIndexed[i][l][0]){
			/*Check that the word isn't excluded*/	
			if (wordExcl(i, l) != 1){
				ret[0]=i;
				ret[1]=l;
				goto exitLoop;
			};
			l++;
		};
		i++;
	};
	exitLoop: return ret;

}

/*send a string to upper case*/
char * makeStringUpper(char *s) {
	static char outputChar[MAX_LEN_OF_LINE_2B_INDEXED];
	int i=0;	
	while (s[i]){
		outputChar[i] =toupper(s[i]);
		i++;
	};
	outputChar[i]='\0';/*Make sure there is an end of string char*/
	return outputChar;
}

/*returns word to be indexed*/
int * lastWord(){
	int i;
	int l;
	static int lastWordIndex[2];
	i=0;
	indexOfFirstReal = firstRealWord();
	int testi=indexOfFirstReal[0];
	int testl=indexOfFirstReal[1];
	while (lines2BIndexed[i][0][0]) {
		l=0;
		while (lines2BIndexed[i][l][0]){
			/*If word (i,l) is an indexable word*/
			/*and (i,l) is later alphebetically*/			
			if (wordExcl(i, l) != 1 && isWordLow(i,l,testi, testl) > 0 ){
				testi=i;
				testl=l;
			};
			l++;
		};
		i++;
	};
	lastWordIndex[0]=testi;
	lastWordIndex[1]=testl;
	/*exitLoop: return lastWordIndex;*/
	return lastWordIndex;

}

