#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 100
#define sizea 10
void fill(int *a);

int main()
{
	int i;
	char s[100]={0};
	char *p = s;
	int ar[sizea];
	int n = 0;

	fill(ar);
	/*
		for(i=0;i<sizea;i++)
		{
			printf("%d\n", ar[i]);
		}	
	*/
	for(i=0;i<sizea;i++)
	{
		sprintf(p += strlen(p),"%d", ar[i]);
	}
	printf("%s\n", s);
	/*
	n = sizeof(ar) / sizeof(int);
	printf("-----------------");
	s = (char*)malloc(sizeof(char) * (n+2));
	/*
		for(i=0;i<n;i++)
		{
			s[i] = ar[i] + '0';
		}
	*/
	
	/*
		for(i=0;i<n;i++)
		{
			printf("%c ", s[i]);
		}
	*/
}


void fill(int *a)
{
	int i;
	for(i=0;i<sizea;i++)
	{
		scanf("%d", &a[i]);
	}
}

