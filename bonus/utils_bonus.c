/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juyojeon <juyojeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:39:30 by juyojeon          #+#    #+#             */
/*   Updated: 2023/09/22 16:56:32 by juyojeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	is_valid_format(const char *path, const char *format)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = ft_strlen(path) - 1;
	j = ft_strlen(format) - 1;
	while (i > 0)
	{
		k = 0;
		while (path[i - k] == format[j - k])
		{
			k++;
			if (k > j)
				return (SUCCESS);
			else if (k > i)
				return (FAILURE);
		}
		i--;
	}
	return (FAILURE);
}

static int	return_color(const char *str, int return_value)
{
	if (*str != '\0')
		return (-1);
	else
		return (return_value);
}

int	color_to_i(const char *str)
{
	int	temp;
	int	return_value;
	int	i;

	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	i = 0;
	return_value = 0;
	while (++i <= 3)
	{
		temp = 0;
		while (*str >= '0' && *str <= '9' && temp < 255)
		{
			temp = (temp * 10) + (*str - '0');
			str++;
		}
		if (temp > 255 || (*str != ',' && i != 3) || (*str != '\0' && i == 3))
			return (-1);
		return_value = (return_value << 8) + temp;
		if (*str == ',')
			str++;
		while (*str == ' ')
			str++;
	}
	return (return_color(str, return_value));
}
