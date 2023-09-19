/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyojeon <juyojeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:15:27 by juyojeon          #+#    #+#             */
/*   Updated: 2023/09/19 16:33:41 by juyojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	draw_sprite_img(t_data *data, t_img *s_img, t_sprite *sprite);
static void	set_tex_sprite(t_info *tex, t_sprite *spr, t_img *img);
static void	texture_color(t_info *tex, t_sprite *sprite, \
unsigned int *dst, t_img *s_img);
typedef struct s_info
{
	int	line_height;
	int	line_width;
	int	row_idx;
	int	end_idx;
	int	step_x;
	int	pos_x;
	int	step_y;
	int	pos_y;
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
	t_info	tex;
	int		i;
	char	*dst;

	set_tex_sprite(&tex, sprite, s_img);
	while (tex.row_idx <= tex.end_idx)
	{
		i = sprite->start - 1;
		tex.pos_x = (sprite->start + (tex.line_width - WINDOW_WIDTH) / 2) \
		* tex.step_x;
		while (++i <= sprite->end)
		{
			dst = data->img.addr + tex.row_idx * data->img.size_l \
					+ i * (data->img.bpp / 8);
			texture_color(&tex, sprite, (unsigned int *)dst, s_img);
			tex.pos_x += tex.step_x;
		}
		tex.row_idx++;
		tex.pos_y += tex.step_y;
	}
}

static void	set_tex_sprite(t_info *tex, t_sprite *spr, t_img *img)
{
	tex->line_height = (int)(WINDOW_HEIGHT / spr->dist);
	tex->line_width = (int)(WINDOW_WIDTH / spr->dist);
	tex->row_idx = (WINDOW_HEIGHT - tex->line_height) / 2;
	if (tex->row_idx < 0)
		tex->row_idx = 0;
	tex->end_idx = (WINDOW_HEIGHT + tex->line_height) / 2;
	if (tex->end_idx >= WINDOW_HEIGHT)
		tex->end_idx = WINDOW_HEIGHT - 1;
	tex->step_x = img->height / (double)(tex->line_width);
	tex->pos_x = (spr->start + (tex->line_width - WINDOW_WIDTH) / 2) \
	* tex->step_x;
	tex->step_y = img->height / (double)(tex->line_height);
	tex->pos_y = (tex->row_idx + (tex->line_height - WINDOW_HEIGHT) / 2) \
	* tex->step_y;

}

static void	texture_color(t_info *tex, t_sprite *sprite, \
unsigned int *dst, t_img *s_img)
{
	int		tex_x;
	int		tex_y;
	char	*tex_color;

	if ((int)(tex->pos_x) >= s_img->width)
		tex_x = s_img->width - 1;
	else
		tex_x = (int)(tex->pos_x);
	if ((int)(tex->pos_y) >= s_img->height)
		tex_y = s_img->height - 1;
	else
		tex_y = (int)(tex->pos_y);
	tex_color = s_img->addr + tex_y * s_img->size_l \
				+ tex_x * (s_img->bpp / 8);
	dst = (unsigned int *)tex_color;
}