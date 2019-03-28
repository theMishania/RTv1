/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cocummin <cocummin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 12:38:21 by cocummin          #+#    #+#             */
/*   Updated: 2019/03/28 11:33:05 by cocummin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

int mouse_pressed(int button, int x, int y, void *param)
{
	t_RTv1 *RTv1;
	t_vector pixel_pos_3d;
	double trash = 99999.0;
	static t_obj *ptr = NULL;
	RTv1 = (t_RTv1 *)param;
	if (button == 1)
	{
        RTv1->left_mouse_pressed = 1;
		pixel_pos_3d = get_pixel_pisition(x - CW / 2, -y + CH / 2);
		ptr = get_closest_object(&trash, RTv1->scene.camera.center, pixel_pos_3d, &(RTv1->scene));
		if (ptr)
			RTv1->selected = ptr;
        else
            RTv1->left_mouse_pressed = 0;
        
	}
	else if (button == 4)
	{
		RTv1->scene.camera.center.z -= 0.2;
	}

	else if (button == 5)
		RTv1->scene.camera.center.z += 0.2;
    else if (button == 2)
    {
        RTv1->right_mouse_pressed = 1;
        RTv1->origin_x = x;
        RTv1->origin_y = y;        
    }
    provider(RTv1);
	return (0);
}

int mouse_release(int button, int x, int y, void *param)
{
    t_RTv1 *RTv1;

    RTv1 = (t_RTv1 *)param;
    RTv1->left_mouse_pressed = 0;
    RTv1->right_mouse_pressed = 0;
    provider(RTv1);
    return (0);
}

int mouse_move(int x, int y, void *param)
{
    t_RTv1 *RTv1;
    int dx;
    int dy;

    RTv1 = (t_RTv1 *)param;
    
    if (RTv1->right_mouse_pressed)
    {
        dx = x - RTv1->origin_x;
        dy = y - RTv1->origin_y;
        RTv1->scene.view_alpha = atan((double)dy * 0.003 / (double)(VW));
        RTv1->scene.view_beta = atan((double)dx * 0.003 / (double)(VW));
    }
    else if (RTv1->left_mouse_pressed)
    {
        dx = x - RTv1->prev_x;
        dy = y - RTv1->prev_y;
        if (!(RTv1->selected))
            RTv1->selected = &(RTv1->scene.objs[0]);
        RTv1->selected->center.x += 0.005 * dx;
        RTv1->selected->center.y -= 0.005 * dy;
    }
    RTv1->prev_x = x;
    RTv1->prev_y = y;
    provider(RTv1);
}


int key_pressed(int key, void *param)
{
	t_RTv1 *RTv1;

	RTv1 = (t_RTv1 *)param;

    if (!(RTv1->selected))
        RTv1->selected = &(RTv1->scene.objs[0]);
	if (key == 0x35)
	{
		exit(1);
	}
	else if (key == 0x7C)
	{
        if (RTv1->left_mouse_pressed == 1)
		    RTv1->selected->center.x += 0.05;
        else 
            RTv1->scene.camera.center.x += 0.5;
	}
	else if (key ==0x7B)
	{
        if ( RTv1->left_mouse_pressed == 1)
		    RTv1->selected->center.x -= 0.05;
        else
            RTv1->scene.camera.center.x -= 0.5;
	}
	else if (key ==0x7E)
	{
        if ( RTv1->left_mouse_pressed == 1)
		    RTv1->selected->center.y += 0.05;
        else
            RTv1->scene.camera.center.y += 0.5;
	}
	else if (key ==0x7D)
	{
        if ( RTv1->left_mouse_pressed == 1)
		    RTv1->selected->center.y -= 0.05;
        else
            RTv1->scene.camera.center.y -= 0.5;
	}
	else if (key ==0x1B)
	{
        if ( RTv1->left_mouse_pressed == 1)
		    RTv1->selected->center.z += 0.05;
        else
            RTv1->scene.camera.center.z += 0.5;
	}
	else if (key ==0x18)
	{
        if ( RTv1->left_mouse_pressed == 1)
		    RTv1->selected->center.z -= 0.05;
        else
            RTv1->scene.camera.center.z  -= 0.5;
	}
	provider(RTv1); 
    return (0);
}