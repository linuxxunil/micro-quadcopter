#ifndef _COMMON_H
#define _COMMON_H

#define DEBUG(arg...)	\
do{																	\
	printf("%s", ## arg);							\
}while( 0 ) 
#endif
