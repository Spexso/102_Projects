#include <stdio.h>

/* 
	1
   5
   9

   4
   8
   12

   7
   11
   15
*/


int main()
{
	int num;
	int i;
	int k;
	int l;

	int spc;

		printf("Enter the num:");
		scanf("%d", &num);

			if (!(num > 0))
			{
				printf("Error");
				return 0;
			}

	for(i=0;i<num;i++)
	{
		for(k=0;k<num-i+1;k++)
		{
				printf(" ");
		}
		
		for(k=0;k<=3*i-2;k++)
		{
		
			printf("*");

		}
		printf("\n");
	}
	
	for(i=0;i<num;i++)
	{
		spc = num;
			while(spc != 0)
			{
				printf(" ");
				spc--;
			
			
			}
		for(k=0;k<num;k++)
		{
			printf("*");
		}
		printf("\n");
	}

	printf("\n");
}