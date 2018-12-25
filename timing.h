#ifndef __timing__
#define __timing__

/* nab the current time and in milliseconds */
void s_and_ms(time_t *s, long *ms);

/* take seconds and milliseconds and flatten them into
 * double (in seconds) */
double s_and_ms_as_double();

#endif

