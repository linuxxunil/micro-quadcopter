#ifndef _COMMON_H
#define _COMMON_H
#include <stdio.h>
#define DEBUG(fmt, args...) \
do {												\
	printf(fmt, ## args);			\
}while( 0 )				
#endif
