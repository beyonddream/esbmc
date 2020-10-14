
#ifdef _WIN32
	//#define _INC_TIME_INL
	//#define __CRT__NO_INLINE
	//#define time crt_time
#endif

#include <time.h>
//#undef time

int main()
{
	int t;

	time(&t);
	return 0;
}

