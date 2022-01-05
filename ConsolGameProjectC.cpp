#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define UP 0
#define DOWN 1

void getCommand(char command[]);
int getArraySize(char **commandPointer);

int main(){
	
	int commandSize=100;
	char command[commandSize];
	char *commandPointer=command;
	
	char directions[4][5]={"Up","Right","Down","Left"};
	int directionPointer=1; //car direction as default, points right
	int brush = UP; // brush position as defauult
	int x=1,y=1; // car's positions as default
	
	char **commandPtrPtr = &commandPointer; 
	getCommand(command); // Displays menu, gets the command, and checks it.
	
	int arraySize = getArraySize(commandPtrPtr); // gets the arraySize, and increments commandPointer for it to point next command btw;
	printf("Array Size: %d\n",arraySize); // **********************
	char array[arraySize+2][arraySize+2]; // creates an array whose size is arraySize+2 because we have borders.
	int i;
	for(i=0;i<arraySize+2;i++){
		int j;
		for(j=0;j<arraySize+2;j++){
			if(i==0 || i==arraySize+1){ // Puts * in first line and last line
				array[i][j]='*';
			}
			else if( j==0 || j==arraySize+1){ //Puts * in first column and last column
				array[i][j]='*';
			}
			else{
				array[i][j]=' ';
			} 	
		}
	}

	int ext=0;
	while(!ext){
	  while(*commandPointer != '\0'){
		char next_command = *commandPointer;
		printf("next_command: %c\n",*commandPointer); //**************************
		if(next_command=='1'){
			brush = DOWN;
			printf("brush state: %d\n",brush); /*************************/
		}
		if(next_command=='2'){
			brush = UP;
		}
		if(next_command=='3'){
			if(directionPointer==3){ // sag sinirda ise
				directionPointer=0; // sol uca git, basa don
			}
			else directionPointer++;
		}
		if(next_command=='4'){
			if(directionPointer==0){ // sol sinirda ise 
				directionPointer=3; // sag uca git, sona git
			}
			else directionPointer--;
			printf("direction: %s\n",directions[directionPointer]); // *******************************
		}
		if(next_command=='5'){
			int squareNum;
			if(*(commandPointer+1)=='_'){
				commandPointer+=2;
	/*	squareNum=atoi(*commandPointer); //That's false, because atoi expects a string. It does not convert a char. */
				squareNum = *commandPointer - '0'; // We can use that instead.
			}
			else{
				squareNum=1;
			}
			printf("squareNum: %d\n",squareNum); //************************************
			char direction = directions[directionPointer][0];
			if( direction=='U' ){
				int k;
				for(k=0;k<squareNum;k++){
					x--;
					if( x == 0){ // x'i azalttim, border kontrolu yaptim.
						x=arraySize; 
					}
					if(brush==DOWN){
						array[x][y]='*';
					}
				}	
			}
			if( direction=='D' ){
				int k;
				for(k=0;k<squareNum;k++){
					x++;
					if( x == arraySize+1 ){
						x=1;
					}
					if(brush==DOWN){
						array[x][y]='*';
					}
				}
			}
			if( direction=='R'){
				int k;
				for(k=0;k<squareNum;k++){
					y++;
					if( y==arraySize+1 ){
						y=1;
					}
					if(brush==DOWN){
						array[x][y]='*';
					}
				}
			}
			if( direction=='L' ){
				int k;
				for(k=0;k<squareNum;k++){
					y--;
					if(y==0){
						y=arraySize;
					}
					if(brush==DOWN){
						array[x][y]='*';
					}
				}
			}	
		}
		if(next_command=='7'){
			if(directionPointer==3){
				directionPointer=1;
			}
			else directionPointer+=2;
		}
		
		if(next_command=='8'){
			int i,j;
			for(i=0;i<arraySize+2;i++){
				for(j=0;j<arraySize+2;j++){
					printf("%c",array[i][j]);
				}
				printf("\n");
			}
			printf("\n");		
		}
		if(next_command=='0'){
			ext=1;
		}
		commandPointer+=2; // In that way, we skip '+' character.
	  }
	  // When one command string is done, then get new command.!
	  strcpy(command,"");
	  getCommand(command);
	  commandPointer = command;
    }
				
	return 0;
}

void getCommand(char command[]){
	printf("(1)Brush Down\n");
	printf("(2)Brush Up\n");
	printf("(3)Turn Right\n");
	printf("(4)Turn Left\n");
	printf("(5)Move up to x\n");
	//printf("(6)Jump\n"); // I have not been added that function yet.
	printf("(7)Reverse Direction\n");
	printf("(8)View the matris\n");
	printf("(0)END Program\n");
	
	printf("Please enter the command: ");
	scanf("%s",command);
	
	int i;
	for(i=0; command[i]!='\0' ;i++){
		if(command[i]=='+' || command[i]=='_' || ( ('0'<=command[i])&&(command[i]<='8') ) ){
			continue;
		}
		else{
			getCommand(command);
		}
	}
	printf("command: %s\n",command);
}

int getArraySize(char **commandPointer){ // ****To increment the adress that a pointer points in a function, we need variable type of pointer's pointer!!
	int i=0;
	char arraySize[5];
	
	while(**commandPointer!='+' && **commandPointer!='\0'){
		arraySize[i]=**commandPointer;  
		i++;
		*commandPointer+=1;  
	}
	*commandPointer+=1; // so that commandPointer points the next element directly
	
	int size=atoi(arraySize);
	return size;
}


