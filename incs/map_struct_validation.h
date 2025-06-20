/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_struct_validation.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:41:52 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:41:53 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_STRUCT_VALIDATION_H
# define MAP_STRUCT_VALIDATION_H

# include <stdbool.h>

typedef struct s_map_data	t_map_data;
typedef struct s_point		t_point;

bool	check_area_closed(t_map_data map_data);
bool	is_point_closed(t_map_data map_data, t_point p);

#endif
