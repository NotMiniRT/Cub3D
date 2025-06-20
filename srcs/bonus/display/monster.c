/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:43:35 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:43:36 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "common.h"
#include "image_b.h"
#include "libft.h"
#include "monster.h"
#include "parsing.h"
#include "sound.h"
#include "structs_b.h"
#include "timer_b.h"

static char	*build_sprite_name(int index)
{
	char	*temp;
	char	*name;
	char	*number;

	number = ft_itoa(index);
	if (!number)
		return (false);
	temp = ft_strjoin_free(MJ_NO_NB, number);
	if (!temp)
		return (NULL);
	name = ft_strjoin_free2(temp, XPM_EXTENSION);
	return (name);
}

static bool	get_mj_sprites(t_main_struct *main_struct)
{
	int		i;
	char	*name;

	main_struct->mj->sprite = malloc(sizeof(t_image_cub *) * 36);
	if (main_struct->mj->sprite == NULL)
		return (false);
	i = 0;
	while (i < MJ_SPRITES)
	{
		name = build_sprite_name(i);
		if (!name || !get_image_cub_from_xpm(main_struct, \
			&((main_struct->mj->sprite)[i]), name, 256))
		{
			if (name)
				free(name);
			(main_struct->mj->sprite)[i] = NULL;
			return (false);
		}
		free(name);
		i++;
	}
	return (true);
}

bool	set_mj(t_main_struct *main_struct, t_infos *infos)
{
	main_struct->mj = malloc(sizeof(t_monster));
	if (main_struct->mj == NULL)
		return (false);
	main_struct->mj->frame = 0;
	main_struct->mj->move_time = 0;
	main_struct->mj->dir_time = 0;
	if (!get_mj_sprites(main_struct))
		return (false);
	main_struct->mj->dir.x = 0;
	main_struct->mj->dir.y = 0;
	main_struct->mj->p1.x = 0;
	main_struct->mj->p1.y = 0;
	main_struct->mj->p2.x = 0;
	main_struct->mj->p2.y = 0;
	main_struct->mj->x = (double)(infos->scene->monster_positions[0] - 0.5);
	main_struct->mj->y = (double)(infos->scene->monster_positions[1] - 0.5);
	return (true);
}

void	move_monster(t_main_struct *main_struct)
{
	static int	i = 0;

	if (i == 0)
		get_monster_dir(main_struct);
	main_struct->mj->move_time = timestamp_in_ms(main_struct);
	main_struct->mj->x = main_struct->mj->x + main_struct->mj->dir.x * 0.1;
	main_struct->mj->y = main_struct->mj->y + main_struct->mj->dir.y * 0.1;
	if ((fabs(main_struct->mj->x - main_struct->player->x) + \
				fabs(main_struct->mj->y - main_struct->player->y)) <= 1)
	{
		main_struct->died = 1;
		return (play_sound(main_struct, SOUND_DEATH));
	}
	if (i % 3 == 0)
	{
		if (main_struct->mj->frame == 20)
			play_sound(main_struct, SOUND_MJ);
		main_struct->mj->frame = main_struct->mj->frame + 1;
		if (main_struct->mj->frame >= MJ_SPRITES)
			main_struct->mj->frame = 0;
	}
	if (i >= 9)
		i = 0;
	else
		i++;
}
