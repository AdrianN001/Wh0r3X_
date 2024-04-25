#ifndef __ASSERT_H_
#define __ASSERT_H_

#include <stdlib.h>
#include <stdio.h>

#define assert(x) if((!(x))){printf("assertion error!\n error at %s() function\n",__func__); exit(1);}

#endif
