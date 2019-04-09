/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_guide.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 20:30:30 by chorange          #+#    #+#             */
/*   Updated: 2019/04/09 20:37:28 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

static void	put_string(t_RTv1 *RTv1, int x, int y, char *string)
{
	mlx_string_put(RTv1->mlx_ptr, RTv1->win_ptr, x, y, 0xFFFFFF, string);
}
/*
void		draw_info(t_RTv1 *RTv1)
{
	put_string(RTv1, 40, 960, "Iterations count:");
	put_string(RTv1, 220, 960, ft_itoa(RTv1->transform.max_iterations));
}*/

void		draw_guide(t_RTv1 *RTv1)
{
	{
		put_string(RTv1, 40, 20, "RTv1");
        put_string(RTv1, 40, 40, "Selected x = ");
        put_string(RTv1, 40, 60, "Selected y = ");
        put_string(RTv1, 40, 80, "Selected z = ");

        put_string(RTv1, 200, 40, ft_itoa((int)RTv1->selected->center.x));
        put_string(RTv1, 200, 60, ft_itoa((int)RTv1->selected->center.y));
        put_string(RTv1, 200, 80, ft_itoa((int)RTv1->selected->center.z));
		
	}
	//draw_info(RTv1);
}
