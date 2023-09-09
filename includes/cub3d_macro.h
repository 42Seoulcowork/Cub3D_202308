/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_macro.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyojeon <juyojeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 17:06:31 by jiyeolee          #+#    #+#             */
/*   Updated: 2023/09/09 22:31:33 by juyojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_MACRO_H
# define CUB3D_MACRO_H

# define WALK_SPEED 0.125
# define TURN_SPEED 0.125

# define NUM_TEXTURES 4

# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64
# define TILE_SIZE 64

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 768

# define SUCCESS 0
# define FAILURE 1
# define FALSE 0
# define TRUE 1
# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define FLOOR 4
# define CEILING 5

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 17

# define MINIMAP_SCALE_FACTOR 0.3

# define PI 3.1415926535
typedef struct s_img
{
	void	*img;
	char	*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	walk_speed;
	double	turn_speed;
}	t_player;

typedef struct s_map
{
	char			*line;
	int				len;
	struct s_map	*next;
}	t_map;
typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_img		texture[NUM_TEXTURES];
	char		**map;
	t_map		*tempmap;
	int			map_width;
	int			map_height;
	t_player	player;
	int			floor_color;
	int			ceiling_color;
}	t_data;

#endif