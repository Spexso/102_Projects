/*
This program reads a single line from an input text file (input.txt) and processes
the line character by character. It tracks the nesting depth of parentheses, printing
each character (other than commas) to an output file (output.txt). The nesting depth is
represented by a series of dashes (-).
*/

#include <stdio.h>
#include <string.h>

#define MAX_LEN 250

int rec(FILE *out, char *line, int count, int i); /* Recursive function to do the task */

int main()
{
	int count_of_minus = 0; /* Variable to track the count of -'s in output.txt */
	int count_line = 0;		/* Counts the inside paranthesis */
	char str[MAX_LEN];		/* String to hold the line from txt file */

	FILE *f;  /* Pointer for input file */
	FILE *of; /* Pointer for output file */

	of = fopen("output.txt", "w");

	if (of == NULL)
	{
		/*Failed to open the file */
		return -1;
	}

	if ((f = fopen("input.txt", "r")) == NULL)
	{
		/*Failed to open the file */
		return -1;
	}

	fgets(str, MAX_LEN, f); /* Reads the line from txt file */

	rec(of, str, count_of_minus, count_line); /* Calls the recursive function */
}

int rec(FILE *out, char *line, int count, int i)
{
	int k;

	if (line[i] == '(')
	{
		count++;
	}
	else if (line[i] == ')')
	{
		count--;
	}
	else if (line[i] == '\0') /* If string ends it returns to the outer function */
	{
		return 0;
	}
	else if (line[i] != ',')
	{
		for (k = 0; k < count; k++)
		{
			fprintf(out, "-");
		}
		fprintf(out, "%c\n", line[i]); /* Prints the current character in line */
	}
	i++;
	rec(out, line, count, i); /* Recursive Part */
}
