#include <alsa/asoundlib.h>

int setup_sound(snd_pcm_t **playback_handle)
{
	int err;
	snd_pcm_hw_params_t *hw_params;

	if ((err = snd_pcm_open (playback_handle, "default", 
	                         SND_PCM_STREAM_PLAYBACK, 0)) < 0) {
		fprintf (stderr, "cannot open audio device %s (%s)\n", 
		         "default",
		         snd_strerror (err));
		return 1;
	}

	if ((err = snd_pcm_hw_params_malloc (&hw_params)) < 0) {
		fprintf (stderr, "cannot allocate hardware parameter structure (%s)\n",
		         snd_strerror (err));
		return 1;
	}

	if ((err = snd_pcm_hw_params_any (*playback_handle, hw_params)) < 0) {
		fprintf (stderr, "cannot initialize hardware parameter structure (%s)\n",
		         snd_strerror (err));
		return 1;
	}

	if ((err = snd_pcm_hw_params_set_access (*playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED)) < 0) {
		fprintf (stderr, "cannot set access type (%s)\n",
		         snd_strerror (err));
		return 1;
	}

	if ((err = snd_pcm_hw_params_set_format (*playback_handle, hw_params, SND_PCM_FORMAT_S16_LE)) < 0) {
		fprintf (stderr, "cannot set sample format (%s)\n",
		         snd_strerror (err));
		return 1;
	}
	
	unsigned int sampling = 44100;

	if ((err = snd_pcm_hw_params_set_rate_near (*playback_handle, hw_params, &sampling, 0)) < 0) {
		fprintf (stderr, "cannot set sample rate (%s)\n",
		         snd_strerror (err));
		return 1;
	}

	if ((err = snd_pcm_hw_params_set_channels (*playback_handle, hw_params, 2)) < 0) {
		fprintf (stderr, "cannot set channel count (%s)\n",
		         snd_strerror (err));
		return 1;
	}

	if ((err = snd_pcm_hw_params (*playback_handle, hw_params)) < 0) {
		fprintf (stderr, "cannot set parameters (%s)\n",
		         snd_strerror (err));
		return 1;
	}

	snd_pcm_hw_params_free (hw_params);

	if ((err = snd_pcm_prepare (*playback_handle)) < 0) {
		fprintf (stderr, "cannot prepare audio interface for use (%s)\n",
		         snd_strerror (err));
		return 1;
	}
	
	return 0;
}

void cleanup_sound(snd_pcm_t *playback_ptr)
{
	snd_pcm_close(playback_ptr);
}

void write_sound(snd_pcm_t **playback_handle, short *buf, const size_t bufsize)
{
	int err;
	if ((err = snd_pcm_writei (*playback_handle, buf, 
	                           bufsize)) != bufsize) 
	{
//		fprintf (stderr, "write to audio interface failed (%s)\n",
//		         snd_strerror (err));
		cleanup_sound(*playback_handle);

		setup_sound(playback_handle);
	}

}
