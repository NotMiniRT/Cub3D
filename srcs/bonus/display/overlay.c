/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overlay.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:43:40 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:43:43 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fuel_bar.h"
#include "minimap.h"
#include "torch.h"

bool	overlay(t_main_struct *main_struct)
{
	if (!display_hud(main_struct)
		|| !display_minimap(main_struct)
		|| !display_torch(main_struct))
		return (false);
	return (true);
}
