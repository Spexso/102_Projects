#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 100
#define MAX_COM 25
#define MAX_LEN_COM 15
#define MIN_LEN_SIGN 2

double head(char *part);
char *get_line(char *str); /* Function to get line of string from stdin */
int check_line(char *s);   /* Function checks if the entered line is only contains numbers */

int main() /* Main function to start the program */
{
	double price;
	char obj[MAX_LEN];
	printf("Please Define the object:\n");
	scanf("%s", obj);

	price = head(obj);

	printf("Price of object is %.4lf\n", price);
}

double head(char *part)
{
	double price = 0;
	double total = 0; /* Total Worth of product */

	int qua;

	int i = 0; /* For loops*/
	int k = 0; /* HELPER */

	int count = 0;

	char *tok;

	const char sign[MIN_LEN_SIGN] = "+"; /* Sign for parsing */

	char buff[MAX_LEN];				  /* String to get line of input */
	int mult[MAX_COM] = {0};		  /* Array to store quantity of compounds */
	char com_n[MAX_COM][MAX_LEN_COM]; /* 2D array to store names of compounds */

	for (i = 0; i < MAX_COM; i++)
	{
		mult[i] = 0;
	}

	printf("What is %s ?\n", part);
	strcpy(buff, get_line(buff)); /* Copys the string to buff after getting it */
								  /*
									  printf("\n(%s", buff);
								  */
	i = 0;
	if (check_line(buff) == 1) /* If string does not contain only numbers */
	{

		tok = strtok(buff, sign);

		while (tok != NULL)
		{
			/*
			printf("\n%s\n", tok);
			*/
			sscanf(tok, "%d%*c%s", &mult[i], com_n[i]);

			tok = strtok(NULL, sign);
			i++;
		}

		i = 0;
		while (mult[i] != 0)
		{
			count++;
			i++;
		}

		for (i = 0; i < count; i++)
		{
			printf("\n%d-%s\n", mult[i], com_n[i]);
		}

		for (i = 0; i < count; i++)
		{
			/*
			printf("\nNAME OF THE OBJECT IS %s|\n", com_n[i]);
			printf("\nQUANTITY IS %d\n", mult[i]);
			*/
			price = head(com_n[i]);
			total = total + mult[i] * price;
		}

		return total;

		/*
		printf("Not only price");

		printf("/%s/%s/", com_n[0], com_n[1]);
		*/
	}
	else /*If string does contain only numbers */
	{
		price = atof(buff); /* Converts string to double*/
		printf(" \n//%lf-%s//\n", price, buff);
		return price;
		/*
		printf("Only price");
		*/
		/*
		return convert_to_num
		*/
	}
}

char *get_line(char *str)
{
	int ch;

	scanf("%s", str);
	/*
	while((ch = getchar()) != '\n' && ch !=EOF);						Another version of getting string from stdin
	fgets(str, MAX_LEN, stdin);
	*/
	return str;
}

int check_line(char *s)
{
	int i = 0;
	int flag = 0;
	int d;
	d = atof(s);

	for (i = 0; i < strlen(s); i++)
	{
		if (d == 0)
		{
			flag = 1;
			break;
		}
		if (!(s[i] >= 48 && s[i] <= 57)) /* If string does contain not number char flag becomes 1*/
		{
			flag = 1;
			break;
			//test();
		}

		/*
		printf("\n((%d))\n", flag);
		*/
	}
	return flag;
}
