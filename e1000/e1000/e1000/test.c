#include<stdio.h>
#define LOG "Tag:good "
#define pr_info(fmt,arg...)\
	printf(fmt,##arg)
#define er_info(fmt,...) \
	printf(LOG fmt,__VA_ARGS__)
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
	pr_info("i=%08X\n",jntohl(i));
	er_info("test%d\n",3);
	return 0;
}

