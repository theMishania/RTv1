/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chorange <chorange@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 12:38:21 by cocummin          #+#    #+#             */
/*   Updated: 2019/04/10 21:37:24 by chorange         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector	rotate_view(t_vector point, double alpha, double beta)
{
	t_vector tempo = point;

	// point.x = tempo.x * cos(beta) + tempo.z * sin(alpha);
	// point.y = tempo.x * sin(alpha) * sin(beta) + tempo.y * cos(alpha) - tempo.z * sin(alpha) * cos(beta);
	// point.z = tempo.x * sin(alpha) * sin(beta) * tempo.y * sin(alpha) + tempo.z * cos(alpha) * cos(beta);

	point.y = tempo.y * cos(alpha) + tempo.z * sin(alpha);
	point.z = -tempo.y * sin(alpha) + tempo.z * cos(alpha);

	tempo = point;

	point.x = tempo.x * cos(beta) - tempo.z * sin(beta);
	point.z = tempo.x * sin(beta) + tempo.z * cos(beta);

	return (point);
}

int mouse_pressed(int button, int x, int y, void *param)
{
	t_RTv1 *RTv1;
	t_vector pixel_pos_3d;
	static t_obj *ptr = NULL;
	RTv1 = (t_RTv1 *)param;
    RTv1->prev_x = x;
    RTv1->prev_y = y;
    RTv1->selected_t = 9999999.9;
    if (y < 0)
        return (0);

	if (button == 1)
	{
        RTv1->left_mouse_pressed = 1;
		pixel_pos_3d = get_pixel_pisition(x - CW / 2, -y + CH / 2);
        pixel_pos_3d = rotate_view(pixel_pos_3d, RTv1->scene.view_alpha, RTv1->scene.view_beta);
		ptr = get_closest_object(&(RTv1->selected_t), RTv1->scene.camera.center, pixel_pos_3d, &(RTv1->scene));
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
        dx = x - RTv1->prev_x;
        dy = y - RTv1->prev_y;
        RTv1->scene.view_alpha += atan((double)dy * 0.001);
        RTv1->scene.view_beta += atan((double)dx * 0.001);
    }
    else if (RTv1->left_mouse_pressed)
    {
        dx = x - RTv1->prev_x;
        dy = y - RTv1->prev_y;
        if (!(RTv1->selected))
        {
            RTv1->selected = &(RTv1->scene.objs[0]);
            RTv1->selected_t = 1.0;
        }
        RTv1->selected->center.x += 0.001 *  dx * RTv1->selected_t;
        RTv1->selected->center.y -= 0.001 * dy * RTv1->selected_t;
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
        //if ( RTv1->left_mouse_pressed == 1)
		    RTv1->selected->center.z += 0.2;
        //else
        ///    RTv1->scene.camera.center.z += 0.5;
	}
	else if (key == 0x18)
	{
       // if ( RTv1->left_mouse_pressed == 1)
		    RTv1->selected->center.z -= 0.2;
       // else
         //   RTv1->scene.camera.center.z  -= 0.5;
	}/*
    else if (key == 0x08)
    {
        RTv1->selected->rgb = color_to_rgb(rgb_to_color(RTv1->selected->rgb) + 1);
    }*/
	provider(RTv1); 
    return (0);
}