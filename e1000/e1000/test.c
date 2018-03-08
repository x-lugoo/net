#include<stdio.h>

typedef unsigned int u32;
static u32 jntohl(u32 i)
{
          u32  ret ;
         ret = ( ((0xff000000 )&  (i << 24)) |
          ((0x00ff0000 )&  (i << 8)) |
         ( (0x0000ff00) &  (i >> 8)) |
         ( (0x000000ff) &  (i >> 24)));
        return ret;
}

int main(void)
{
	int i = 0x12345678; 
	printf("i=%08X\n",jntohl(i));
	return 0;
}

