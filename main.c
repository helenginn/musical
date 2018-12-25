// sound shit

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <alsa/asoundlib.h>
#include "sound.h"
#include "timing.h"

int main(int argc, char **argv)
{
	snd_pcm_t *playback_handle;
	setup_sound(&playback_handle);

	int count = 0;
	double sampling = 44100;
	double hz = 440 * 1;
	double repeat_freq = 0;
	const size_t bufsize = 1;

	double tonic = 0;
	short buf[bufsize];

	double wall = s_and_ms_as_double();
	double now = 0;
	
	int notes[] = {0, 7, 7, 5, 3, 2, 0, -2, 0,
		2, 3, 5, 7, 7, 7, 0, 0, 7, 7, 5, 3, 2, 0, -2,
		0, 2, 3, 5, 7, 7, 7, 7, 8, 5, 7, 8, 10, 12,
		7, 5, 3, 0, 2, 3, 5, 5};
	size_t total = sizeof(notes);

	int current = 0;

	while (current < total)
	{
		repeat_freq = sampling / hz;
		tonic += (1 / repeat_freq) * 2 * M_PI;

		short val = sin(tonic) * 2000;

		val *= 2;
		buf[count] = val;
		count++;
		
		if (count >= bufsize)
		{
			write_sound(&playback_handle, buf, bufsize);

			count = 0;
		}

		now = s_and_ms_as_double();
		if (now - wall >= 0.2)
		{
			wall = now;
			hz = 440 * pow(2, (notes[current] / 12.));
			current++;
		}
	}

	cleanup_sound(playback_handle);

	return 0;
}
