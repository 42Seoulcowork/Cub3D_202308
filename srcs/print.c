/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyeolee <jiyeolee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:20:52 by juyojeon          #+#    #+#             */
/*   Updated: 2023/09/12 21:20:26 by jiyeolee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	print_image(t_data *data)
{
	print_background(data);
	ray_casting(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}

void	ray_casting(t_data *data)
{
	int		i;
	double	camera_x;
	t_ray	ray;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		camera_x = 2 * i / (double)WINDOW_WIDTH - 1;
		calculate_dda(&data->player, &ray, camera_x);
		perform_dda(data, &data->player, &ray, i);
		i++;
	}
	return (0);
}

void	calculate_dda(t_player *player, t_ray *ray, double camera_x)
{
	ray->raydir_x = player->dir_x + player->plane_x * camera_x;
	ray->raydir_y = player->dir_y + player->plane_y * camera_x;
	ray->deltadist_x = fabs(1 / ray->raydir_x);
	ray->deltadist_y = fabs(1 / ray->raydir_y);
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->x - (int)player->x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = ((int)player->x + 1.0 - player->x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->y - (int)player->y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = ((int)player->y + 1.0 - player->y) * ray->deltadist_y;
	}
}

void	perform_dda(t_data *data, t_player *player, t_ray *ray, int i)
{
	int		hit;
	int		side;
	int		map_x;
	int		map_y;
	
	map_x = (int)player->x;
	map_y = (int)player->y;
	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[map_y][map_x] > 0)
			hit = 1;
	}
	ray->perpwall_dist = perpetual_wall_dist(ray);
	print_vertical_line(data, ray, i);
}

double	perpetual_wall_dist(t_ray *ray)
{
	if(ray->side == 0)
		return (ray->sidedist_x - ray->deltadist_x);
	else
		return (ray->sidedist_y - ray->deltadist_y);
}

int	texture_color(t_img *texture, t_player *player, t_ray *ray, int i)
{
	int		color;
	int		tex_y;
	int		tex_x;
	double	wallX; //where exactly the wall was hit

      //calculate value of wallX
      if (ray->side == 0)
		wallX = player->y + ray->perpwall_dist * ray->raydir_y;
      else
	  	wallX = player->x + ray->perpwall_dist * ray->raydir_x;
      wallX -= floor(wallX);
      if(ray->side == 0 && ray->raydir_x > 0)
	  	tex_x = TEXTURE_WIDTH - wallX * (double)TEXTURE_WIDTH - 1;
      if(ray->side == 1 && ray->raydir_y < 0)
	  	tex_x = TEXTURE_WIDTH - wallX * (double)TEXTURE_WIDTH - 1;
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		tex_y = (int)ray->texpos & (TEXTURE_HEIGHT - 1);
        ray->texpos += ray->step;
		if (ray->side == 0)
		{
			if (ray->raydir_x >= 0)
				color = texture[EAST].addr + TEXTURE_HEIGHT * tex_x + tex_y;
			else
				color = texture[WEST].addr + TEXTURE_HEIGHT * tex_x + tex_y;
		}
		else
		{
			if (ray->raydir_y >= 0)
				color = texture[SOUTH].addr + TEXTURE_HEIGHT * tex_x + tex_y;
			else
				color = texture[NORTH].addr + TEXTURE_HEIGHT * tex_x + tex_y;
		}
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(ray->side == 1)
			color = (color >> 1) & 8355711;
	return (color);
}

void	print_vertical_line(t_data *data, t_ray *ray, int i)
{
	int		color;
	int		y;
	int 	start;
	int 	end;
	int 	line_height;
	char	*dst;

	line_height = (int)(WINDOW_HEIGHT / ray->perpwall_dist);
	start = -line_height / 2 + WINDOW_HEIGHT / 2;
    if (start < 0)
		start = 0;
	end = line_height / 2 + WINDOW_HEIGHT / 2;
    if (end >= WINDOW_HEIGHT)
		end = WINDOW_HEIGHT - 1;	
	// How much to increase the texture coordinate per screen pixel
	ray->step = 1.0 * TEXTURE_HEIGHT / line_height;
	ray->texpos = (start - WINDOW_WIDTH / 2 + line_height / 2) * ray->step;
	y = start;
	while (y < end)
	{
		dst = data->img.addr + (y * data->img.size_l + i * (data->img.bpp / 8));
		*(unsigned int *)dst = texture_color(&data->texture, &data->player, ray, i);
		y++;
	}
}

void	print_background(t_data *data)
{
	int		color;
	char	*dst;
	int		i;

	dst = data->img.addr;
	color = data->ceiling_color;
	i = 0;
	while (i < WINDOW_WIDTH * WINDOW_HEIGHT / 2)
	{
		*(unsigned int *)dst = color;
		dst += data->img.bpp / 8;
		i++;
	}
	color = data->floor_color;
	while (i < WINDOW_WIDTH * WINDOW_HEIGHT)
	{
		*(unsigned int *)dst = color;
		dst += data->img.bpp / 8;
		i++;
	}
}
