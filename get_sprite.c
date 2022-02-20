/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprite.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 14:01:25 by abadalya          #+#    #+#             */
/*   Updated: 2021/07/08 14:01:33 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_sprite()
{
	int width;
	int height;

	if (!(g_values.t_n.img = mlx_xpm_file_to_image(g_values.mlx,
						g_values.p.nor_tex, &width, &height)))
		error("North texture is not found");
	g_values.t_n.addr = mlx_get_data_addr(g_values.t_n.img, &g_values.t_n.bits_per_pixel,
									&g_values.t_n.line_length, &g_values.t_n.endian);
	if (!(g_values.t_s.img = mlx_xpm_file_to_image(g_values.mlx,
						g_values.p.sou_tex, &width, &height)))
		error("South texture is not found");
	g_values.t_s.addr = mlx_get_data_addr(g_values.t_s.img, &g_values.t_s.bits_per_pixel,
					&g_values.t_s.line_length, &g_values.t_s.endian);
	if (!(g_values.t_w.img = mlx_xpm_file_to_image(g_values.mlx,
						g_values.p.wes_tex, &width, &height)))
		error("Western texture is not found");
	g_values.t_w.addr = mlx_get_data_addr(g_values.t_w.img, &g_values.t_w.bits_per_pixel,
									&g_values.t_w.line_length, &g_values.t_w.endian);
	if (!(g_values.t_e.img = mlx_xpm_file_to_image(g_values.mlx,
						g_values.p.eas_tex, &width, &height)))
		error("Eastern texture is not found");
	g_values.t_e.addr = mlx_get_data_addr(g_values.t_e.img, &g_values.t_e.bits_per_pixel,
									&g_values.t_e.line_length, &g_values.t_e.endian);
	if (!(g_values.t_spr.img = mlx_xpm_file_to_image(g_values.mlx,
									g_values.p.spr_tex, &width, &height)))
		error("Sprite texture is not found");
	g_values.t_spr.addr = mlx_get_data_addr(g_values.t_spr.img,
	&g_values.t_spr.bits_per_pixel, &g_values.t_spr.line_length, &g_values.t_spr.endian);
}
