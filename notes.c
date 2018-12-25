#include <math.h>
#include <stdio.h>

short sound_contribution(int semitone, double xval)
{
	double hz = 440 * pow(2, (double)semitone / 12.);
	xval *= hz / 440;
	short val = sin(xval) * 2000;

	return val;
}
