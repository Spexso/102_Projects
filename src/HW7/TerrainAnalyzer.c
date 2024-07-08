#include <stdio.h>
#define LEN  512
#define WIDE 512
#define Matrix_i 512

/* 
Something like Flood Fill algorithm 
----------------------------------------------------------------------------
Program does scan an area (which is read from an input file) then finds the 

lands (The points which are greater than water level) and prints the single 

points from every unique Island to an output file  
----------------------------------------------------------------------------	
*/



int terrain01[LEN][WIDE];         /* Array to hold coordinates of every point // Data will be stored in the Heap Since I created the array as global */

int find_land(int r, int c, int land_type,int water_L); /* Function to find points that are above water and defines them as Islands */

int check_boundaries(int row, int column);				/* Function to make sure searched points are still in array */

void show_Islands(FILE *out);							/* Function to print the coordinates of lands to output.txt */


 
int main()
{
	int i;												/* Loop counter */
	int k;												/* Loop counter */

	int row = 0;
	int col = 0;
	int type_of_land = -1;
	
	int ref;											/* Variable to hold read integer from file */

	FILE *inp;
	FILE *out;


	int L;												/* Water level */


		inp = fopen("input.txt","r");

	if(inp == NULL)
	{
		printf("ERROR->File couldn't open!");			/* Checks for the proper input file */
		return -1;
	}

	
	fscanf(inp,"%d", &L);

		for(i=0;i<Matrix_i;i++)
		{
			for(k=0;k<Matrix_i;k++)
			{
				fscanf(inp,"%d", &ref);				/* Assigns the read value to a variable */
				terrain01[i][k] = ref ;				
			}
		}
	fclose(inp);

	for(row=0;row<LEN;row++)
	{
		for(col=0;col<WIDE;col++)
		{
			if(terrain01[row][col] > L)
			{
				find_land(row, col, type_of_land--, L);
			}
		}
	}
		
		show_Islands(out);
	/*
		for(i=0;i<Matrix_i;i++)
		{
			for(k=0;k<Matrix_i;k++)
			{
				printf("%d ", terrain01[i][k]);											For TEST Purposes 
			}
			printf("\n");
		}
	*/
}


int find_land(int r, int c, int land_type,int water_L)
{
	
	if(check_boundaries(r,c) )		/* Checks if the matrix still in allocated area */
	{
		return 0;
	}
	

	if(terrain01[r][c] > water_L)									/* If its greater than Water Level than its a land */
	{
		terrain01[r][c] = land_type;
	}
	


	if(terrain01[r][c+1] > water_L && terrain01[r][c+1] !=land_type)  			/* West */
	{
		find_land(r, c+1, land_type, water_L);
	}
	if(terrain01[r+1][c] > water_L && terrain01[r+1][c] !=land_type) 			/* South */
	{
		find_land(r+1, c, land_type, water_L);
	}
	if(terrain01[r][c-1] > water_L && terrain01[r][c-1] !=land_type) 			/* East */
	{
		find_land(r, c-1, land_type, water_L);
	}
	if(terrain01[r-1][c] > water_L && terrain01[r-1][c] !=land_type) 			/* North */
	{
		find_land(r-1, c, land_type, water_L);
	}
}

int check_boundaries(int row, int column)
{
	int res = 0;

	if(row > Matrix_i-1 || column > Matrix_i-1)					/* Checks if the counter are still inside borders of array */
	{
		res = 1;
	}
	else if(row < 0 || column < 0)
	{
		res = 1;
	}

	return res;
}

void show_Islands(FILE *out)
{
	int count = 1;											/* Variable to count Islands */
	int type_of_land;										/* Variable to pick out Islands from each other */
	int i;
	int k;

	out = fopen("output.txt","w");

	if(out == NULL)
	{
		printf("ERROR->File couldn't create!");			/* Check of file existence */
		return ;
	}
	
	type_of_land = -1;									

		for(i=0;i<Matrix_i;i++)							/* Loop to print out the Island coordinates */
		{
			for(k=0;k<Matrix_i;k++)
			{
				if(terrain01[i][k] == type_of_land)
				{
					fprintf(out,"%d_coordinate%d\t%d_coordinate%d\n", i, count, k, count);
					type_of_land--;						/* Decreases the type of land variable to count Islands separately */
					count++;
				}
			}
			
		}

	fclose(out);
	/*
	printf("\n%d\n", count);		TEST 
	*/
}