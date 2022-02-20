/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 13:59:25 by abadalya          #+#    #+#             */
/*   Updated: 2021/07/08 13:59:41 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		CUB3D_H
# define	CUB3D_H

#include <fcntl.h>
#include <math.h>
#include "./libs/mlx/mlx.h"
#include "libs/libft/libft.h"
#include "gnl/get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define key_w	13
#define key_s	1
#define key_a	0
#define key_d	2
#define key_rot_left 123
#define key_rot_right 124

typedef unsigned int rgb;

typedef struct 	s_matrix
{
    char		**worldMap;
    int			matrixWidth;
    int			matrixHeight;
	int			rows_count;
} 				t_matrix;

typedef struct  s_data 
{
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

typedef struct	s_move
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;	
}				t_move;

typedef struct   s_keys
{
	int			up;
	int			down;
	int			left;
	int			right;
	int			rotate_left;
	int			rotate_right;
}				t_keys;

typedef struct 		s_p_flags 
{
	int 			res;
	int 			tex_n;
	int 			tex_w;
	int 			tex_e;
	int 			tex_s;
	int 			spr;
	int 			ceiling;
	int 			floor;
} 					t_p_flags;

typedef	struct		s_parser
{
	char			*nor_tex;
	char			*sou_tex;
	char			*wes_tex;
	char			*eas_tex;

	char			*spr_tex;

	rgb				floore_color;

	rgb				ceilling_color;

	int				size_map;
	int				pos_count;
}					t_parser;


typedef struct 	s_sprite_elem
{
	double		x;
	double		y;
	double		distance;
}				t_sprite_elem;

typedef struct	s_sprite
{
	int 		count;
	t_sprite_elem **sprite;
}               t_sprite;

struct 				s_values
{
	void        	*mlx;
	void        	*mlx_win;
	int             screenWidth;
	int             screenHeight;
	int             texWidth;
	int             texHeight;
	double          moveSpeed;
	double          rotSpeed;
	void            *currentImage;
	int 			should_save;
	t_matrix		matrix;
	t_move			move;
	t_data		  	data;
	t_sprite      	sprite;
	t_keys		 	keys;
	t_data        	t_n;
  	t_data        	t_s;
  	t_data        	t_e;
  	t_data        	t_w;
	t_data        	t_spr;
	t_parser		p;
	t_p_flags		parser_flags;
}					g_values;

void			init_sprites();
void			globs_init();
void			sort_sprites();
void	        get_sprite();
void			matrix_parser(char *filepath);
void            bubble_sort();
void            fill_sprites();
void	        my_mlx_pixel_put(t_data *data, int x, int y, int color);
unsigned int	get_pixel(t_data *data, int x, int y);
int 			win_close();
void            error();
int				my_rgb_pars(char * line);
void	        error(char *str);

#endif
