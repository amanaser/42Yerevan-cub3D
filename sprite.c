/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 14:04:19 by abadalya          #+#    #+#             */
/*   Updated: 2021/07/08 14:04:24 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int count_sprites()
{
    int count = 0;

    for (int y = 0; y < g_values.matrix.matrixHeight; ++y)
        for (int x = 0; x < g_values.matrix.matrixWidth; ++x)
            count += (g_values.matrix.worldMap[y][x] == '2') ? 1 : 0;
    return (count);
}

void fill_sprites()
{
    int count = 0;

    for (int y = 0; y < g_values.matrix.matrixHeight; ++y)
    {
        for (int x = 0; x < g_values.matrix.matrixWidth; ++x)
        {
            if (g_values.matrix.worldMap[y][x] == '2')
            {
                g_values.sprite.sprite[count]->x = (double)y + 0.5;
                g_values.sprite.sprite[count]->y = (double)x + 0.5;
                g_values.sprite.sprite[count]->distance = 0;
                count++;
            }
        }
    }
}

void init_sprites()
{
    g_values.sprite.count = count_sprites();
    g_values.sprite.sprite = (t_sprite_elem **)malloc(g_values.sprite.count * (sizeof(t_sprite_elem*)));
    for (int i = 0; i < g_values.sprite.count; ++i)
        g_values.sprite.sprite[i] = (t_sprite_elem*)malloc(sizeof(t_sprite_elem));
    fill_sprites();
}

void bubble_sort()
{
    int i;
	int j;
    float tmp;

	i = 1;
	while (i < g_values.sprite.count)
	{
		j = i;
		while (j > 0 && (int)g_values.sprite.sprite[i]->distance > (int)g_values.sprite.sprite[j - 1]->distance)
		{
            tmp = g_values.sprite.sprite[j - 1]->distance;
            g_values.sprite.sprite[j - 1]->distance = g_values.sprite.sprite[j]->distance;
            g_values.sprite.sprite[j]->distance = tmp;
            tmp = g_values.sprite.sprite[j - 1]->x;
            g_values.sprite.sprite[j - 1]->x = g_values.sprite.sprite[j]->x;
            g_values.sprite.sprite[j]->x = tmp;
            tmp = g_values.sprite.sprite[j - 1]->y;
            g_values.sprite.sprite[j - 1]->y = g_values.sprite.sprite[j]->y;
            g_values.sprite.sprite[j]->y = tmp;
			--j;
		}
		++i;
	}
}


void			sort_sprites()
{
	int i;

	i = -1;
	while (++i < g_values.sprite.count)
	{
		g_values.sprite.sprite[i]->distance =
        ((g_values.move.posX - g_values.sprite.sprite[i]->x)
        * (g_values.move.posX - g_values.sprite.sprite[i]->x)
		+ (g_values.move.posY - g_values.sprite.sprite[i]->y)
        * (g_values.move.posY - g_values.sprite.sprite[i]->y));
	}
	if (g_values.sprite.count > 1)
		bubble_sort();
}
