#define _POSIX_C_SOURCE 200809L

#include <inttypes.h>
#include <math.h>
#include <time.h>

void s_and_ms (time_t *s, long *ms)
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);

    *s  = spec.tv_sec;
	// Convert nanoseconds to milliseconds
    *ms = round(spec.tv_nsec / 1.0e6); 
    if (*ms > 999) {
        (*s)++;
        *ms = 0;
    }
}

double s_and_ms_as_double()
{
	time_t s, ms;
	s_and_ms(&s, &ms);
	
	double total = s + (double)ms / 1000.;
	return total;
}
