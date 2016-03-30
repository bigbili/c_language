#include <stdio.h>
int main(void)
{
	int x;
	for(x = 1; x <= 1000; x++)
	{
		int a = x;
		int y = x*x;
		int count = 10;
		
		while(a >= 10)
		{
			a /= 10;
			count *= 10;
		}
		int z = y % count;
		if(z == x)
		{
			printf("%d\n",x);
		}
		
	}
	
 } 
