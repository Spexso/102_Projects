#include <stdio.h>
#include <stdlib.h>

#define MAX_INT 100

/* Program to read integers and their counts from a txt file then assign them to two different arrays then sorts
them after that writes them to a output file


Effiency:
------------------
Since we know there will be maximum 100 different numbers , my arrays stores 100 variables and second array holds
the count of numbers.So when we look at my algorithm for every increase in max number program needs 2 more array cell
When we look at the sorting part sorting does happen simultaneously it does check both arrays and swaps the variables
at the same time then prints all the variables and their counts to an output file
*/

int main()
{
	int temp_1; /* Variables to use at sorting from arrays */
	int temp_2;

	int num;
	int status; /* Variable to check for succesful fscanf from input file */
	int flag;

	int ar_1[MAX_INT]; /* Array for store variables */
	int ar_2[MAX_INT]; /* Array for store count of variables */

	int i = 0;
	int k = 0;
	int t; /* For test purposes */

	FILE *fp; /* File pointer for input.txt */
	FILE *op; /* File pointer for output.txt */

	for (t = 0; t < MAX_INT; t++)
	{
		ar_1[t] = 0;
	}

	for (t = 0; t < MAX_INT; t++)
	{
		ar_2[t] = 0;
	}

	fp = fopen("input.txt", "r");
	op = fopen("output.txt", "w");

	if (fp == NULL)
	{
		printf("ERROR! file couldn't open"); /* Checks if the operation is succesful */
		return 0;
	}

	if (op == NULL)
	{
		printf("ERROR! output file couldn't created"); /* Checks if the operation is succesful */
		return 0;
	}

	while (!feof(fp)) /* Loop does read integers from input file then stores them in first array */
	{
		status = fscanf(fp, "%d", &num);

		if (status == 1)
		{
			flag = 1;
			if (ar_1[i] != num)
			{
				for (k = 0; k < MAX_INT; k++)
				{
					if (ar_1[k] == num)
					{
						flag = 0;
					}
				}
				if (flag == 1)
				{
					ar_1[i] = num;
					i++;
				}
			}
		}
	}

	fseek(fp, 0, SEEK_SET); /* Sets the cursor to the start of file */

	while (!feof(fp)) /* Counts the number of repetitions */
	{
		status = fscanf(fp, "%d", &num);

		if (status == 1)
		{
			for (i = 0; i < MAX_INT; i++)
			{
				if (ar_1[i] == num)
				{
					ar_2[i]++;
				}
			}
		}
	}

	fclose(fp);

	for (i = 0; i < MAX_INT; i++) /* Sorts the counts of integers that inside second array also at the same time swaps the variables in first array */
	{
		for (k = i + 1; k < MAX_INT; k++)
		{
			if (ar_2[i] > ar_2[k] && ar_2[i] != 0 && ar_2[k] != 0)
			{
				/* Sort of second array */

				temp_2 = ar_2[k];

				ar_2[k] = ar_2[i];

				ar_2[i] = temp_2;

				/* Sort of first array */

				temp_1 = ar_1[k];

				ar_1[k] = ar_1[i];

				ar_1[i] = temp_1;
			}
			else if (ar_2[i] == ar_2[k] && ar_2[i] != 0 && ar_2[k] != 0) /* if the counts of integers inside array 2 are same for any reason then program checks the first array and smaller numbers get precedence at sorting */
			{
				if (ar_1[i] > ar_1[k] && ar_1[i] != 0 && ar_1[k] != 0)
				{
					temp_1 = ar_1[k];

					ar_1[k] = ar_1[i];

					ar_1[i] = temp_1;
				}
			}
		}
	}

	/*
		for(t=0;t<MAX_INT;t++)
		{
			if(ar_1[t] != 0)
			{
				printf("%d:%d\n", ar_1[t], ar_2[t]);			/* TEST PURPOSES
			}

		}

	*/

	for (i = 0; i < MAX_INT; i++) /* Writes arrays to output file in order */
	{
		if (ar_1[i] != 0 && ar_2[i] != 0)
		{
			fprintf(op, "%d:%d\n", ar_1[i], ar_2[i]);
		}
	}

	printf("\n---------Process has completed---------\n");
	fclose(op);

	return 0;
}