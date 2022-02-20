/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 14:04:56 by abadalya          #+#    #+#             */
/*   Updated: 2021/07/08 14:05:00 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void globs_init()
{
    g_values.texWidth = 64;
    g_values.texHeight = 64;
    g_values.move.posX = 0;
    g_values.move.posY = 0;
    g_values.move.dirX = 0;
    g_values.move.dirY = 0;
    g_values.move.planeX = 0;
    g_values.move.planeY = 0;
    g_values.moveSpeed = 0.1;
    g_values.rotSpeed = 0.05;
    g_values.parser_flags.res = 0;
    g_values.parser_flags.tex_e = 0;
    g_values.parser_flags.tex_s = 0;
    g_values.parser_flags.tex_w = 0;
    g_values.parser_flags.tex_n = 0;
    g_values.parser_flags.spr = 0;
    g_values.parser_flags.ceiling = 0;
    g_values.parser_flags.floor = 0;
    g_values.sprite.count = 0;
    g_values.should_save = 0;
    g_values.p.pos_count = 0;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned	int	get_pixel(t_data *data, int x, int y)
{
	unsigned int	color;
	char			*dst;

 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void	error(char *str)
{
	(void)g_values;
	ft_putendl_fd(str, 1);
	exit(1);
}

int 			win_close()
{
    exit(0);
    return 0;
}
