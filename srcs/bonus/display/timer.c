#include <sys/time.h>
#include <stdint.h>
#include "main_struct.h"


/**
 * @bug franchement, est-ce qu'on enleverai pas cette secu ?
 * Elle sert vraiment a rien...
 */
static size_t	gettimeofday_ms(void)
{
	static struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	return ((tv.tv_sec * (size_t)1000) + (tv.tv_usec / 1000));
}

size_t	timestamp_in_ms(t_main_struct *t_main_struct)
{
	size_t	secur;

	secur = gettimeofday_ms();
	if (secur == 0)
		return (0);
	if (t_main_struct->created_at == 0)
		t_main_struct->created_at = secur;
	return (secur - t_main_struct->created_at);
}
