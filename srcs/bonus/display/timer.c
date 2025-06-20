/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:44:07 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:44:08 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

#include "structs.h"

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
