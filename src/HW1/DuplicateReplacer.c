
#include <stdio.h>	/* Main library */
#include <stdlib.h> /* Library for file operations */

/*
										EFFIENCY OF MY PROGRAM
	My function is simply reading an integer then from that point , its starting to scan for duplicate so for every integer my program reading (all integers - read integers) times integers and
	and checks them in a loop so formula of read items is [all integers * (all integers - read integers)] so its something like [pow(x,2)-x*y] (if we say all integers is x and read integers is y)
	if I want to build this program for specific time challanged work I can figure out to use which algorithm from cost of time point of view by using this explanation also I readlized that this
	formula representing that derivative of square of x goes to the 0 because y is 0 at the start then its goes up to x at the end So we can look this way of solution as 2x.

My function does the following:

-Reads the characters
-If it is integer stores it in a variable
-Then starts checking for duplication of that integers by reading
	1-If a duplicate exist puts space as count of digits
	2-Then goes back to integer
	3-If duplication doesnt exist returns to the integers without editing anything
-Reads all integers until the end-of-file

*/

int main()
{
	/*
	int i = 1;						(For test purposes)
	int a = 1;
	*/

	int status;

	int y;
	int sup_y;
	int digit_y; /* Variable to count integer's digit number */

	int pos;
	int sup_pos = 0;

	int numofDigit; /* Counted digits */
	int space_t;

	/*
	int ind;				A variable to check samples of functions (For test purposes)
	*/

	FILE *fp; /* Pointer that represent the file */

	fp = fopen("example.txt", "r+"); /* Opens the file in reading and writing mod */

	if (fp == NULL) /* Opens the file for reading and writing and checks for succesful operation */
	{
		printf("ERROR! File couldn't open\n");
		return 0;
	}

	while (!feof(fp)) /* Loop to end-of file */
	{
		numofDigit = 0;
		status = fscanf(fp, "%d", &y);

		if (status == 1) /* If the reading an integer is succesful then does the following: */
		{

			digit_y = y;

			do /* Counts the digits of stored integer */
			{
				numofDigit++;
				digit_y = digit_y / 10;

			} while (!(digit_y == 0));

			pos = ftell(fp); /* Stores the cursor position in pos variable to return later */

			while (!feof(fp))
			{
				status = fscanf(fp, "%d", &sup_y);
				if (status == 1)
				{
					if (sup_y == y)
					{
						if (sup_y < 0)
						{
							fseek(fp, -(numofDigit + 1), SEEK_CUR); /* Sets the cursor position to start of the integer that needs to get cleaned */
							fputs(" ", fp);
						}
						else
						{
							fseek(fp, -numofDigit, SEEK_CUR); /* Sets the cursor position to start of the integer that needs to get cleaned */
						}

						for (space_t = 0; space_t < numofDigit; space_t++) /* Puts spaces as number of digits */
						{
							fputs(" ", fp);
						}
					}
				}
			}
			sup_pos = ftell(fp);				   /* Stores the current position of cursor in sup_pos variable */
			fseek(fp, -(sup_pos - pos), SEEK_CUR); /* Returns the cursor to the previous position (Before scan for duplicate) */
		}
	}

	fclose(fp); /* Closes the file */
	printf("\n\nDuplicated integers have been removed\n\n");
	printf("Have a good day!\n");
}