/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer_b.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agantaum <agantaum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:42:41 by agantaum          #+#    #+#             */
/*   Updated: 2025/06/20 11:42:42 by agantaum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_B_H
# define TIMER_B_H

# include <stddef.h>

typedef struct s_main_struct	t_main_struct;

size_t	timestamp_in_ms(t_main_struct *t_main_struct);

#endif
