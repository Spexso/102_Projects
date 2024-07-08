#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_LINE 1000
#define MAX_UNIT 100
#define UNIT 1

/*
Program Description:
--------------------
This program processes polynomial expressions from an input file, evaluates them for given values, and writes the results to an output file. The process is broken down into several key steps:

1. Initialization: Initializes arrays to hold polynomial coefficients, powers, and input values.

2. Input Reading:
   a. Reads values from 'values.txt', which are the x-values for which the polynomial will be evaluated.
   b. Reads the polynomial expression from 'polynomial.txt'.

3. Polynomial Parsing:
   a. Extracts coefficients and powers from the polynomial string.
   b. Handles different sections of the polynomial separately:
      - First, it captures all coefficients except the last one.
      - Next, it extracts the last coefficient based on the sign preceding it.
      - Extracts all powers of x except the last one.
      - Finally, captures the last power of x if it exists.

4. Evaluation:
   - Uses the extracted coefficients and powers to compute the polynomial value for each input x-value.
   - Writes the computed values to 'evaluations.txt'.

Efficiency Considerations:
--------------------------
The program handles the polynomial in segments to efficiently map coefficients to their respective powers. Given the static maximum limits (MAX_LINE and MAX_UNIT), the program manages memory usage effectively. The polynomial parsing is performed in a linear pass, optimizing the handling of input data.

Challenges addressed:
---------------------
- Dynamically determining the length of coefficients and powers within the polynomial string.
- Managing signs and different formats of polynomial expressions (e.g., handling missing powers or coefficients of 1).
- Efficiently writing the results to an output file after computing the polynomial value for each input.

This structured approach ensures that the polynomial is parsed correctly and evaluated efficiently for each provided input value.
*/

int main()
{
	double val[100];		/* To hold values */
	double hold_v;			/* To hold single double number */
	double f_pol[MAX_UNIT]; /* Told hold coefficents */
	double power;			/* To hold single power number */
	int pow_n[MAX_UNIT];	/* To hold powers */

	char pow_s[MAX_UNIT]; /* String to hold powers */
	char pol[MAX_LINE];	  /* To hold string which program gets with fgets */
	char mono[MAX_LINE];  /* String for editing to cut the needed part */
	char pol_sub[MAX_LINE];

	int flag = 0; /* To justify certain condition */
	int c_line;
	int c_line1;
	double sum = 0; /* For evaluation */

	int i = 0; /* For loops */
	int k = 0;
	int t = 0;
	int l = 0;

	int test = 0; /* For testing */
	int n = 0;

	char *tok;
	char *tok1;

	char sign2[] = "x";

	int c = 0;
	int status;

	/* Filling arrays with zeros */
	for (test = 0; test < MAX_UNIT; test++)
	{
		f_pol[test] = 0;
	}
	for (test = 0; test < MAX_UNIT; test++)
	{
		pow_n[test] = 0;
	}

	FILE *v;
	FILE *p;
	FILE *e;

	v = fopen("values.txt", "r");
	p = fopen("polynomial.txt", "r");
	e = fopen("evaluations.txt", "w");

	if (v == NULL || p == NULL || e == NULL)
	{
		printf("ERROR file or files couldn't handle\n");
		return 0;
	}

	while (!feof(v))
	{
		status = fscanf(v, "%lf", &hold_v);

		if (status == 1)
		{
			val[c] = hold_v;
			c++;
		}
	}

	/*
	for(int i = 0;i<100;i++)				 Test
	{
		printf("%lf\n", val[i]);
	}
	*/
	c = 0;
	fgets(pol, MAX_LINE, p); /* Reads the polynomial txt and writes it into a string */

	c_line = strlen(pol);
	/*
	printf("%d", c_line);
	*/

	/*Loop for coefficents */
	while (pol[i] != '\0')
	{

		if (pol[i] == '+')
		{
			strncpy(mono, pol, i);
			sscanf(mono, "%lf", &hold_v);

			if (pol[c] == '-')
			{
				hold_v = -1 * hold_v;
			}
			f_pol[k] = hold_v;
			k++;
			strcpy(mono, "");
			c = i;
		}
		else if (pol[i] == '-')
		{
			strncpy(mono, pol + c, i - c);

			sscanf(mono, "%lf", &hold_v);

			if (pol[c] == '-')
			{
				hold_v = -1 * hold_v;
			}

			f_pol[k] = hold_v;
			k++;
			strcpy(mono, "");
			c = i;
		}
		i++;
	}
	strcpy(mono, "");
	i = 0;
	c_line = 0;

	/* Loop for the last coefficent */
	tok = strrchr(pol, '-');
	tok1 = strrchr(pol, '+');

	c_line = strlen(tok);
	c_line1 = strlen(tok1);

	if (c_line > c_line1)
	{
		tok1 = strtok(tok1, sign2);
		status = sscanf(tok1, "%lf", &hold_v);
		if (status == 1)
		{
			f_pol[k] = hold_v;
			k++;
		}
		else
			f_pol[k] = -1;
		flag = 1;
	}
	else if (c_line < c_line1)
	{

		tok = strtok(tok, sign2);
		status = sscanf(tok, "%lf", &hold_v);

		if (status == 1)
		{
			f_pol[k] = hold_v;
			k++;
		}
		else
			f_pol[k] = -1;
		/*
		printf("%lf" , hold_v);
		*/
		flag = -1;
	}
	k = 0;

	/*Loop for powers */
	while (pol[i] != '\0')
	{
		/*
		printf("%c", pol[i]);
		*/
		if (pol[i] == 'x')
		{
			if (pol[i + 1] == '^')
			{
				l = i + 2;
				/*
				printf("%d", (int)pol[l]);
				*/
				while (!(pol[l] < 45))
				{
					pow_s[t] = pol[l];
					l++;
					t++;
				}

				sscanf(pow_s, "%lf", &hold_v);
				pow_n[k] = hold_v;
				k++;
				t = 0;
				strcpy(pow_s, "");
			}
			else
			{
				pow_n[k] = 1;
				k++;
			}
		}
		i++;
	}
	l = 0;
	t = 0;
	i = 0;
	strcpy(pow_s, "");
	/*Loop for last power */

	fseek(p, 0, SEEK_SET);
	fgets(pol_sub, MAX_LINE, p);

	c_line = strlen(pol_sub);

	/*
	printf("\n\n%d\n\n", c_line);
	*/

	if (pol[c_line - 2] != 'x')
	{
		tok = strrchr(pol_sub, 'x');
		/*
		printf("%s", tok);
		*/
		while (tok[i + 2] != '\0')
		{
			mono[i] = tok[i + 2];
			i++;
		}
		sscanf(mono, "%lf", &hold_v);
		pow_n[k] = hold_v;
		k++;
	}
	else
	{
		pow_n[k] = 1;
		k++;
	}

	/*
	printf("\n//COE\n");
	for(test = 0; test < k; test++)
	{
		if(f_pol[test] != 0)
		printf("%lf\n", f_pol[test]);
	}
	printf("\n//POW\n");
	for(test = 0; test < k; test++)
	{
		if(pow_n[test] != 0)
		printf("%d\n", pow_n[test]);
	}
	*/

	/* Evaluation */
	k = 0;
	l = 0;
	while (val[l] != 0) /* Evaluation of all datas */
	{
		while (f_pol[k] != 0)
		{
			if (f_pol[k] != 0 && pow_n[k] != 0)
			{
				/*
				printf("\n(%lf)\n", val[l]);
				printf("(%d)\n", pow_n[k]);
				printf("(%lf)\n", f_pol[k]);
				*/
				power = pow(val[l], pow_n[k]);
				sum = sum + (f_pol[k] * power);
			}
			k++;
		}
		if (sum != 0)
		{
			fprintf(e, "%.2lf\n", sum);
		}

		sum = 0;
		l++;
		k = 0;
	}

	fclose(p);
	fclose(e);
	fclose(v);
}