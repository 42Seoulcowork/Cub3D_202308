/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyojeon <juyojeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:15:27 by juyojeon          #+#    #+#             */
/*   Updated: 2023/09/18 22:20:26 by juyojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	draw_sprite_img(t_data *data, t_img *s_img, t_sprite *sprite);
static void	add_first_sprite(t_data *data);

void	draw_sprite(t_data *data)
{
	struct timeval	time;
	t_img			*sprite_img;
	t_sprite		*temp;

	if (!data->sprite)
		return ;
	gettimeofday(&time, 0);
	sprite_img = &((data->texture)[SP1 + (time.tv_usec % 100000) / 25000]);
	temp = data->sprite->next;
	while (temp)
	{
		draw_sprite_img(data, sprite_img, temp);
		temp = temp->next;
	}
}

static void	draw_sprite_img(t_data *data, t_img *s_img, t_sprite *sprite)
{
}

void	add_sprite(t_data *data, int x, int y)
{
	double		new_dist;
	t_sprite	*temp;
	t_sprite	*new;

	new_dist = pow(data->player.x - x, 2) + pow(data->player.y - y, 2);
	if (!data->sprite)
		add_first_sprite(data);
	temp = data->sprite;
	while (temp->next)
	{
		if (temp->x == x && temp->y == y)
			return ;
		if (new_dist < temp->dist && new_dist > temp->next->dist)
			break ;
		temp = temp->next;
	}
	new = (t_sprite *)malloc(sizeof(t_sprite));
	if (!new)
		error_exit("Error : Allocation failed\n", data);
	new->x = x;
	new->y = y;
	new->dist = new_dist;
	new->next = temp->next;
	temp->next = new;
}

static void	add_first_sprite(t_data *data)
{
	data->sprite = (t_sprite *)malloc(sizeof(t_sprite));
	if (!data->sprite)
		error_exit("Error : Allocation failed\n", data);
	data->sprite->x = 0;
	data->sprite->y = 0;
	data->sprite->dist = WINDOW_WIDTH * WINDOW_HEIGHT;
	data->sprite->next = 0;
}
