#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define UP 0
#define DOWN 1
#define NO 0
#define YES 1

typedef enum{
	right=1,down=2,left=3,up=4
}directions;

void getCommand(char command[]);
int getArraySize(char **commandPointer);
int getSquareNum(char **commandPointer);

int main(){
	
	int commandSize=100;
	char command[commandSize];
	char *commandPointer=command;
	
	directions direction = right; // default direction
	int brush = UP; // default brush status
	int x=1,y=1; // default position
	
	getCommand(command); // displays menu, gets the command, and checks it.
	
	int arraySize = getArraySize(&commandPointer); // gets the arraySize, and increments commandPointer to point next command
	printf("Array Size: %d\n",arraySize); // **********************
	char board[arraySize+2][arraySize+2]; // creates an array whose size is arraySize+2 because we have borders.
	int i;
	for(i=0;i<arraySize+2;i++){
		int j;
		for(j=0;j<arraySize+2;j++){
			if(i==0 || i==arraySize+1){ // puts * in first line and last line
				board[i][j]='*';
			}
			else if( j==0 || j==arraySize+1){ // puts * in first column and last column
				board[i][j]='*';
			}
			else{
				board[i][j]=' ';
			} 	
		}
	}

	int ext=NO;
	while(ext!=YES){
	  while(*commandPointer != '\0'){
		char next_command = *commandPointer;
		printf("next_command: %c\n",*commandPointer); //**************************
		if(next_command=='1'){
			brush = DOWN;
		}
		if(next_command=='2'){
			brush = UP;
		}
		if(next_command=='3'){
			if(direction==up){ // sag sinirda ise
				direction = right; // sol uca git, basa don
			}
			else direction++;
		}
		if(next_command=='4'){
			if(direction==right){ // sol sinirda ise 
				direction = up; // sag uca git, sona git
			}
			else direction--;
			printf("direction: %s\n",direction); // *******************************
		}
		if(next_command=='5'){
			int squareNum = getSquareNum(&commandPointer);
			printf("squareNum: %d\n",squareNum); //************************************
			if( direction==up ){
				int k;
				for(k=0;k<squareNum;k++){
					x--;
					if( x == 0){		    // check if player is in the border 
						x=arraySize; 
					}
					if(brush==DOWN){
						board[x][y]='*';
					}
				}	
			}
			if( direction==down ){
				int k;
				for(k=0;k<squareNum;k++){
					x++;
					if( x == arraySize+1 ){	// check if player is in the border 
						x=1;
					}
					if(brush==DOWN){
						board[x][y]='*';
					}
				}
			}
			if( direction==right ){
				int k;
				for(k=0;k<squareNum;k++){
					y++;
					if( y==arraySize+1 ){ 	// check if player is in the border 
						y=1;
					}
					if(brush==DOWN){
						board[x][y]='*';
					}
				}
			}
			if( direction==left ){
				int k;
				for(k=0;k<squareNum;k++){
					y--;
					if(y==0){ 				// check if player is in the border 
						y=arraySize;
					}
					if(brush==DOWN){
						board[x][y]='*';
					}
				}
			}	
		}
		if(next_command=='7'){				// reverse direction
			if(direction==up){
				direction==down;
			}
			else direction+=2;
		}
		if(next_command=='8'){
			int i,j;
			for(i=0;i<arraySize+2;i++){
				for(j=0;j<arraySize+2;j++){
					printf("%c",board[i][j]);
				}
				printf("\n");
			}
			printf("\n");		
		}
		if(next_command=='0'){
			ext=YES;
		}
		commandPointer+=2; // In that way, we skip '+' character.
	  }
	  // When one command string is done, then get new command.!
	  strcpy(command,""); // clear command buffer
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
	for(i=0; command[i]!='\0' ;i++){	// check if input command is in proper format
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
	*commandPointer+=1; 	// so that commandPointer points the next element directly
	
	int size=atoi(arraySize);
	return size;
}

int getSquareNum(char **commandPointer){
	int squareNum;
	if(*((*commandPointer)+1)=='_'){ 
		*commandPointer+=2;
		squareNum = **commandPointer - '0'; 
	}
	else{					// if command is like ...+5+2+.... means 1 square
		squareNum=1;
	}
	return squareNum;
}

