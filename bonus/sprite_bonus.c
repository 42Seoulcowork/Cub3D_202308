/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyojeon <juyojeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:15:27 by juyojeon          #+#    #+#             */
/*   Updated: 2023/09/18 23:56:57 by juyojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	draw_sprite_img(t_data *data, t_img *s_img, t_sprite *sprite);
static void set_tex_sprite(t_texture *tex, t_sprite *spr, int row, t_img *img);
static void	texture_color(t_texture *tex, t_sprite *sprite, unsigned int *dst);

typedef struct s_info
{
	int	line_height;
	int	pos_x;
	int	pos_y;
	int	step_x;
	int	step_y;
}	t_info;

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
	// t_info		tex;
	// int			row_idx;
	// int			end_idx;
	// int			i;
	// char		*dst;

	// tex.line_height = (int)(WINDOW_HEIGHT / sprite->dist);
	// row_idx = (WINDOW_HEIGHT - tex.line_height) / 2;
	// end_idx = (WINDOW_HEIGHT + tex.line_height) / 2;
	// set_tex_sprite(&tex, sprite, row_idx, s_img);
	// if (row_idx < 0)
	// 	row_idx = 0;
	// if (end_idx >= WINDOW_HEIGHT)
	// 	end_idx = WINDOW_HEIGHT - 1;
	// while (row_idx <= end_idx)
	// {
	// 	i = sprite->start - 1;
	// 	while (++i <= sprite->end)
	// 	{
			
	// 		dst = data->img.addr + row_idx * data->img.size_l \
	// 				+ i * (data->img.bpp / 8);
	// 		texture_color(&tex, sprite, (unsigned int *)dst);
	// 	}
	// 	row_idx++;
	// 	tex.pos += tex.step;
	// }
}

// static void	set_tex_sprite(t_texture *tex, t_sprite *spr, int row, t_img *img)
// {

// }

// static void	texture_color(t_texture *tex, t_sprite *sprite, unsigned int *dst)
// {
// 	int		tex_x;
// 	int		tex_y;

// 	tex_x = (int)(tex->pos) & (tex->curr_img->width - 1);
// }