#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>


//global variables
char mnemonic[][],destination[][],Reg1[][],Reg2[][];	//defining instruction opcodes variables
char Instr_ptr[][];			// Initializing the instruction pointer

//Dependency Detect functions
void Data_Dependency(int);
void Name_Dependency(int);
void Control_Dependency(int);

void main()
{
	
	FILE *file = fopen ( "C:\\MIPS_Dependencies_program.txt", "r" );
	int i, j, k, check;
	char Str_line[200],* Str_ptr, Str_temp[30]; /* or other suitable maximum line size */

	
/*Assuming each string is automatically initialized to NULL by the compiler*/



//checking for availability of file.

	if ( file == NULL )
{
	printf( "Could not open the given file!!! \n" );
}		

	else
{
	     i=0;
	     while ( fgets ( Str_line, 200, file ) != NULL ) // read a line from file
	     {
			 strcpy(Instr_ptr[i], Str_line);
	         i++;
		 }
	 fclose (file);
	 check=0;


	 //copy line into temporary string array as well as print the program instructions and split the instruction opcodes into words
	 
	for(j=0;j<i;j++)
	 {
		 strcpy(Str_temp,Instr_ptr[j]);
		 printf("%s",Str_temp);

		 //Splitting the strings into tokens and using pointer to point to each word in the line

		 Str_ptr=strtok(Str_temp," ");

		 while(Str_ptr!=NULL)
		 {

			 //copy each pointer location to appropriate string variable
			 if((check%4)==0)
				 strcpy(nemonic[j],Str_ptr);
			 else if((check%4)==1)
				 strcpy(dreg[j],Str_ptr);
			 else if((check%4)==2)
				 strcpy(reg1[j],Str_ptr);
			 else if((check%4)==3)
				 strcpy(reg2[j],Str_ptr);
			 
			 Str_ptr = strtok (NULL, " ");		//split string into words, each word being a token with ' ' character as delimiter
			 ++check;
		 }
	 }



	 for(k=0;k<j;k++)
	 {
		 printf("\n mnemonic[%d] = %s\t",k,mnemonic[k]);
		 printf("destination[%d] = %s\t",k,destination[k]);
		 printf("Reg1[%d] = %s\t",k,Reg1[k]);
		 printf("Reg2[%d] = %s",k,Reg2[k]);
		 printf("\n");
	 }
	 printf("\n Press Enter to start\n");
	 getch();
	}

	//calling the functions to check dependency
	Data_Dependency(j);
	Name_Dependency(j);
	Control_Dependency(j);

	getch(); 
}



void Data_Dependency(int j)
{
	int i, A, B;


	for(i=0;i<j;i++)
	{
		//compare instructions i and i+1 for data dependences
		A=strcmp(destination[i],Reg1[i+1]);
		B=strcmp(destination[i],Reg2[i+1]);

		if( (A==0) || (B==0) )
		{
			printf("\n\n\nData dependence:\t%s                \t%s\n",Instr_ptr[i],Instr_ptr[i+1]);
			printf("READ AFTER WRITE hazard because true dependency exists.");
		}
	}
}


void Name_Dependency(int j)
{
	int i, A, B;


	for(i=0;i<j;i++)
	{
		//compare instructions i and i+1 for anti-dependences
		A=strcmp(destination[i+1],Reg1[i]);
		B=strcmp(destination[i+1],Reg2[i]);
		
		if( (A==0) || (B==0) )
		{
			printf("\n\n\nAnti-dependence:\t%s                \t%s",Instr_ptr[i],Instr_ptr[i+1]);
			printf("\ncauses WRITE AFTER READ hazard.");
		}
	}

	for(i=0;i<j;i++)
	{
		//compare instructions i and i+1 for output dependences
		A=strcmp(destination[i+1],destination[i]);
		
		if(compare1==0)
		{
			printf("\n\n\nOutput dependence:\t%s                  \t%s",Instr_ptr[i],Instr_ptr[i+1]);
			printf("\ncauses WRITE AFTER WRITE hazard.");
		}
	}
}


void Control_Dependency(int j)
{
	int i, Prog_Count;

	for(i=0;i<j;i++)
	{
		int A;

		//check to see if there is any instruction involving BNE
		A=strcmp(mnemonic[i],"BNE");

		if( A == 0)	//if yes, find the instruction where it branches to
		{
			Prog_Count=atoi(Reg2[i]);	//converts string to integer type

			//Here program counter is the number of instructions by which the program counter will jump
			printf("\n\n\nControl dependence:\t%s                   \t%s\n",Instr_ptr[i],Instr_ptr[i+Prog_Count]);
			printf("Instruction %d is executed only if instruction %d is true.",i+Prog_Count,i);
		}
	}
}

