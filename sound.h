#ifndef __sound__
#define __sound__

/** Silently returns 0 on successful setup, and 1 if there
 *  was an error. */
int setup_sound(snd_pcm_t **playback_ptr);

/** Clean up sound */
void cleanup_sound(snd_pcm_t *playback_ptr);

/** Write to sound buffer */
void write_sound(snd_pcm_t **playback_handle, short *buf, 
                 const size_t bufsize);

#endif
