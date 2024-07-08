/*
The LogicalGatesProcessor program reads a description of a logic circuit from a file,
sets up the circuit by linking logic gates based on their connections, and evaluates 
the output of the circuit for a set of input values. The program supports four types of 
logic gates: AND, OR, NOT, and FLIPFLOP.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define VAR_LEN 10
	

typedef struct gate{										/*Main struct to store data */
	int type;
	char name[VAR_LEN];
	char inp_1_name[VAR_LEN];
	char inp_2_name[VAR_LEN];
	struct gate* in1;
	struct gate* in2;
	int output;
	int mem;
}gate;

int count_line();											/* Function to count lines and inputs */
void search_and_link(gate** gates,int max_c, int inp_c);	/* Function to link nodes to each other */
int eva(gate* g);											/* Function to calculate results of circuit */

enum type_n{INPUT, AND, OR, NOT, FLIPFLOP};


int main()
{	
	FILE *circ;			/* pointers for files */
	FILE *inp;

	char type_name[VAR_LEN];
	int line_c;
	int in_c = 0;
	int inp_l_c=0;

	int i=0;			/* Variables for loops */
	int k;

	int temp_l;			/* Variables to store input count and line count */
	int temp_inp;

	int test=0;	

	int hold_v;			/* Variable to hold circuit results */

	char buff[10];
	char ch;

	int len_of_l = 0;	/* Variable to store lenght of 1 line in txt file */






	line_c = count_line(&in_c); 													/* Calls the function to count lines and inputs */
	
	/*
	printf("%d\n", line_c-1);
	printf("%d\n", in_c);						
	*/	
		temp_l = line_c + in_c;	
		temp_inp = in_c;

	gate** gates = (gate**)malloc(sizeof(gate*) * (line_c-1 + in_c) );				/* Memory allocation for struct */

	/*	
	gates[0]->type = INPUT;
	printf("%d\n", gates[0]->type);
	*/


	circ = fopen("circuit.txt","r");

		if(circ == NULL)
		{
			printf("ERROR->File could not open\n");	
			return 0;
		}

	/*Buffer to get INPUT line */
	fscanf(circ,"%s",buff);
	
	while(in_c != 0)
	{
		gates[i] = malloc(sizeof(gate));											/* Memory allocation for struct */

			

		fscanf(circ,"%s",gates[i]->name);
			gates[i]->type = 0;
		in_c--;
		i++;
		test++;
	}
						
	while(line_c !=0)
	{	
		gates[i] = malloc(sizeof(gate));											/* Memory allocation for struct */

		fscanf(circ,"%s %s", type_name, gates[i]->name);
			
		/* Assings the type variable to {1,2,3,4} range */	

			if(strcmp(type_name,"AND") == 0)
				{
					gates[i]->type = 1;
					fscanf(circ,"%s %s", gates[i]->inp_1_name, gates[i]->inp_2_name);
				}
			else if(strcmp(type_name,"OR") == 0)
				{
					gates[i]->type = 2 ;
					fscanf(circ,"%s %s", gates[i]->inp_1_name, gates[i]->inp_2_name);
				}
			else if(strcmp(type_name,"NOT") == 0)
				{
					gates[i]->type = 3;
					fscanf(circ,"%s", gates[i]->inp_1_name);
				}
			else if(strcmp(type_name,"FLIPFLOP") == 0)
				{
					gates[i]->type = 4;
					fscanf(circ,"%s", gates[i]->inp_1_name);
				}

		/*
		printf("(%d)\n", line_c);
		printf("%d", test);
		*/

		line_c--;
		i++;
	}
	fclose(circ);

	/*	
	printf("//\n");

		for(k=0;k<9;k++)
		{
			printf("\n%d-%s-%s-%s\n", gates[k]->type, gates[k]->name, gates[k]->inp_1_name, gates[k]->inp_2_name);
		}
	*/	
	
	search_and_link(gates, temp_l, temp_inp);

	/*
	printf("^^^^^^^^^^^^^^^^^^^\n");
	for(i=0;i<9;i++)
	{
		printf("%d-%d\n", gates[i]->in1, gates[i]->in2);		For test purposes
	}
	printf("^^^^^^^^^^^^^^^^^^^\n");
	*/
	inp = fopen("input.txt","r");
	
	if(inp == NULL)
	{
		printf("ERROR->File could not open\n");
		return 0;
	}
	
		while( (ch=fgetc(inp)) != EOF)
		{
			if(ch == '\n')
			inp_l_c++;
		}

	fseek(inp, 0,SEEK_SET);							/* Resets the cursor position on file */


	for(i=0;i<inp_l_c;i++)
	{
		for(k=0;k<temp_inp;k++)
		{
			fscanf(inp,"%d", &hold_v);
				
				gates[k]->output = hold_v;
		}
		/*
		hold_v = eva(gates[temp_inp+temp_l-2]);
		*/
		printf("%d\n", hold_v);
	}
		
	free(gates);
	fclose(inp);
}	

int count_line(int *inp)
{
	FILE *cir;

	char single;
	char *line;
	char *tok;

	int l_count = 0;
	int len = 0;
	
	cir = fopen("circuit.txt","r");


	if(cir == NULL)
	{
		printf("ERROR! -> No such file exist");

	}

		while( (single=fgetc(cir)) != EOF)
		{
			if(single == '\n')
			l_count++;
		}

	fseek(cir, 0,SEEK_SET);									/* Resets the cursor position on file */

		while((single=fgetc(cir) != '\n'))
		{
			len++;
		}
		
	line = (char*)malloc(len * sizeof(char));	

		fseek(cir, 0,SEEK_SET);								/* Resets the cursor position on file */

	fscanf(cir,"%[^\n]", line);

		/*
		printf("%s\n", line);
		*/
															/*Do parse operation to separately get the data for struct members */
	tok = strtok(line, " ");

		while(tok !=NULL )
		{
			if(strcmp(tok,"INPUT") != 0)
			{
				(*inp)++;
			}
			/*
			printf("%s\n", tok);
			*/
			tok = strtok(NULL, " ");
		}
	free(line);
	fclose(cir);
		return l_count;
}

void search_and_link(gate** gates,int max_l,int max_c)
{	
	max_l = max_l - 2;
	int k;
	int m;
	
	/*
	printf("/////////");
	for(k=0;k<max_l;k++)
		{
			printf("///%d-%s-%s-%s///\n", gates[k]->type, gates[k]->name, gates[k]->inp_1_name, gates[k]->inp_2_name);
		}
	printf("\n///////\n");
	*/

	for(k=0;k<max_l;k++)
	{
		for(m=0;m<max_l;m++)
		{	
			if(!(k==m))
			{
				if(strcmp(gates[k]->name,gates[m]->inp_1_name) == 0)
				{	
					gates[k]->in1 = gates[m];
				}
				if(strcmp(gates[k]->name,gates[m]->inp_2_name) == 0)
				{
					gates[k]->in2 = gates[m];
				}

			}

			

		}
		

	}

}

int eva(gate* g)
{
	
	int in1 = eva(g->in1);
	int in2 = eva(g->in2);	


		if(g->type == 1)							/* AND OPERATION */
		{
			return in1 && in2;
		}	
		else if(g->type == 2)						/* OR OPERATION */
		{
			return in1 || in2;
		}
		else if(g->type == 3)						/* NOT OPERATION */
		{
			return in1 !=in2;
		}
		else if(g->type == 4)						/* FLIPFLOP OPERATION */
		{
			if(g->mem == in1)
			{
				return 0;
			}
			else 
				return 1;
			
		}
}