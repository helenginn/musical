// sound shit

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <alsa/asoundlib.h>
#include "sound.h"
#include "notes.h"
#include "timing.h"

typedef struct
{
	int left;
	int right;
} Harmony;

int main(int argc, char **argv)
{
	snd_pcm_t *playback_handle;
	setup_sound(&playback_handle);

	int count = 0;
	double sampling = 44100;
	double hz = 440;
	double repeat_freq = sampling / hz;
	const size_t bufsize = 1;

	double xval = 0;
	short buf[bufsize];

	double wall = s_and_ms_as_double();
	double now = 0;
	
	Harmony notes[] = 
	{{-5, 0}, {-5, 7}, {-5, 7},
	 {-5, 5}, {-12, 3}, {-12, 2},
	{-12, 0}, {-12, -2}, {-5, 0},
	{-5, 2}, {-5, 3}, {-5, 5},
	{-9, 7}, {-9, 7}, {-9, 7},
	{-9, 0}, {-12, 0}, {-12, 7},
	{-12, 7}, {-12, 5}, {-5, 3},
	{-5, 2}, {-5, 0}, {-5, -2},
	{-9, 0}, {-9, 2}, {-9, 3}, 
	{-9, 5}, {-5, 7}, {-5, 7},
	{-5, 7}, {-2, 7}, {0, 8},
	{-4, 5}, {-2, 7}, {0, 8},
	{2, 10}, {3, 12}, {-2, 7},
	{-4, 5}, {-5, 3}, {-9, 0},
	{-7, 2}, {-5, 3}, {-4, 5},
	{-4, 5}};
	
	size_t total = sizeof(notes) / sizeof(Harmony);

	int c = 0;

	while (c < total)
	{
		xval += 2 * M_PI / repeat_freq;

		short val = 0;
		val += sound_contribution(notes[c].left, xval);
		val += sound_contribution(notes[c].right, xval);

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
			c++;
			printf("Loading note i\n", c);
		}
	}

	snd_pcm_drain(playback_handle);
	cleanup_sound(playback_handle);

	return 0;
}
