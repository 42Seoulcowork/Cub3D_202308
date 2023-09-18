/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_add_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyojeon <juyojeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:50:54 by juyojeon          #+#    #+#             */
/*   Updated: 2023/09/18 23:14:50 by juyojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	add_first_sprite(t_data *data);
static void	range_update(t_sprite *sprite, int i);
static void	sprite_data_fill(t_sprite *sprite, int x, int y, int i);

void	add_sprite(t_data *data, int x, int y, int i)
{
	double		new_dist;
	t_sprite	*temp;
	t_sprite	*new;

	new_dist = sqrt(pow(x + 0.5 - data->player.x, 2) \
					+ pow(y + 0.5 - data->player.y, 2));
	if (!data->sprite)
		add_first_sprite(data);
	temp = data->sprite;
	while (temp->next)
	{
		if (temp->x == x && temp->y == y)
			return (range_update(temp, i));
		if (new_dist < temp->dist && new_dist > temp->next->dist)
			break ;
		temp = temp->next;
	}
	new = (t_sprite *)malloc(sizeof(t_sprite));
	if (!new)
		error_exit("Error : Allocation failed\n", data);
	sprite_data_fill(new, x, y, i);
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
	data->sprite->start = 0;
	data->sprite->end = 0;
	data->sprite->dist = WINDOW_WIDTH * WINDOW_HEIGHT;
	data->sprite->next = 0;
}

static void	range_update(t_sprite *sprite, int i)
{
	if (i > sprite->end)
		sprite->end = i;
	else if (i < sprite->start)
		sprite->start = i;
}

static void	sprite_data_fill(t_sprite *sprite, int x, int y, int i)
{
	sprite->x = x;
	sprite->y = y;
	sprite->start = i;
	sprite->end = i;
}
