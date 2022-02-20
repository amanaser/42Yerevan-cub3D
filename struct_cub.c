/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 14:04:37 by abadalya          #+#    #+#             */
/*   Updated: 2021/07/08 14:04:40 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_init()
{
	g_values.keys.up = 0;
	g_values.keys.down = 0;
	g_values.keys.left = 0;
	g_values.keys.right = 0;
	g_values.keys.rotate_left = 0;
	g_values.keys.rotate_right = 0;
    g_values.moveSpeed = 0.1; //the constant value is in squares/second
    g_values.rotSpeed = 0.05; //the constant value is in radians/second
}

int	key_press(int keycode)
{
	
	if (keycode == 53)
		exit(0);
	if (keycode == key_w) //w = 13
		g_values.keys.up = 1;
	else if (keycode == key_s) //s = 1
		g_values.keys.down = 1;
	if (keycode == key_a) //a = 0
		g_values.keys.left = 1;
	else if (keycode == key_d) //d = 2
		g_values.keys.right = 1;
	if (keycode == key_rot_left) //<- == 123
		g_values.keys.rotate_left = 1;
	else if (keycode == key_rot_right) //-> == 124
		g_values.keys.rotate_right = 1;
	
	return (0);
}

int	key_release(int keycode)
{
	if (keycode == key_w) //w = 13
		g_values.keys.up = 0;
	else if (keycode == key_s) //s = 1
		g_values.keys.down = 0;
	if (keycode == key_a) //a = 0
		g_values.keys.left = 0;
	else if (keycode == key_d) //d = 2
		g_values.keys.right = 0;
	if (keycode == key_rot_left) //<- == 123
		g_values.keys.rotate_left = 0;
	else if (keycode == key_rot_right) //-> == 124
		g_values.keys.rotate_right = 0;
	return (0);
}

int my_rgb(int r, int g, int b)
{
    return(r << 16 | g << 8 | b);
}


void frame()
{
    double posX = g_values.move.posX;
    double posY = g_values.move.posY;
    double dirX = g_values.move.dirX;
    double dirY = g_values.move.dirY;
	double planeX = g_values.move.planeX;
	double planeY = g_values.move.planeY;
    double ZBuffer[g_values.screenWidth];
    //double moveSpeed = g_values.moveSpeed;

	int x = 0;
	while (x < g_values.screenWidth)
	{
		double cameraX = 2 * x / (double)g_values.screenWidth - 1;
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)posX;
		int mapY = (int)posY;
		//length of ray from one x or y-side to next x or y-side

		double sideDistX;
        double sideDistY;
        
        int stepX;
        int stepY;
		//what direction to step in x or y-direction (either +1 or -1)
		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;
		int side;
		int hit = 0;
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}

		//DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if(g_values.matrix.worldMap[mapX][mapY] == '1')
				hit = 1;
	
			
		}

		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0) 
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else          
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
		//Calculate height of line to draw on screen
		int lineHeight = (int)(g_values.screenHeight / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + g_values.screenHeight / 2;
		if(drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + g_values.screenHeight / 2;
		if(drawEnd >= g_values.screenHeight) drawEnd = g_values.screenHeight - 1;

		//texturing calculations
		double wallX;
		if (side == 0)
		    wallX = posY + perpWallDist * rayDirY;
    	else
    		wallX = posX + perpWallDist * rayDirX;
		wallX -= floor((wallX));
		int textX = (int)(wallX * (double)(g_values.texWidth));
		if (side == 0 && rayDirX > 0)
			textX = g_values.texWidth - textX - 1;
		if (side == 1 && rayDirY < 0)
			textX = g_values.texWidth - textX - 1;
		double step = 1.0 * g_values.texHeight / lineHeight;
		double textPos = (drawStart - g_values.screenHeight / 2 + lineHeight / 2) * step;

		for (int y = 0; y < drawStart; y++)
            my_mlx_pixel_put(&g_values.data, x, y, g_values.p.ceilling_color);

	 for (int y = drawStart; y<drawEnd; y++)
        {
            int texY = (int)textPos & (g_values.texHeight - 1);
            textPos += step;
            int color = 0;

            if (side == 0)
            {
                if (stepX > 0)
                    color = get_pixel(&g_values.t_n , textX, texY);
                else
                    color = get_pixel(&g_values.t_s, textX, texY);
            }
            else
            {
                if (stepY > 0)
                    color = get_pixel(&g_values.t_e, textX, texY);
                else
                    color = get_pixel(&g_values.t_w, textX, texY);;

            }
            my_mlx_pixel_put(&g_values.data, x, y, color);
        }
        for (int y = drawEnd; y < g_values.screenHeight; y++)                    
            my_mlx_pixel_put(&g_values.data, x, y, g_values.p.floore_color);
        ZBuffer[x] = perpWallDist;
        x++;
    }


	for(int i = 0; i < g_values.sprite.count; i++)
      g_values.sprite.sprite[i]->distance = ((posX - g_values.sprite.sprite[i]->x) * (posX - g_values.sprite.sprite[i]->x) + (posY - g_values.sprite.sprite[i]->y) * (posY - g_values.sprite.sprite[i]->y)); //sqrt not taken, unneeded
    sort_sprites();
    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < g_values.sprite.count; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = g_values.sprite.sprite[i]->x - posX;
      double spriteY = g_values.sprite.sprite[i]->y - posY;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication
      double transformX = invDet * (dirY * spriteX - dirX * spriteY);
      double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D
      int spriteScreenX = (int)((g_values.screenWidth / 2) * (1 + transformX / transformY));
      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(g_values.screenHeight / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + g_values.screenHeight / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + g_values.screenHeight / 2;
      if(drawEndY >= g_values.screenHeight) drawEndY = g_values.screenHeight - 1;
      //calculate width of the sprite
      int spriteWidth = abs((int)(g_values.screenHeight / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= g_values.screenWidth) drawEndX = g_values.screenWidth - 1;

    	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
    	{
        	int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * g_values.texWidth / spriteWidth) / 256;
        	if(transformY > 0 && stripe > 0 && stripe < g_values.screenWidth && transformY < ZBuffer[stripe])
			{
        		for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
        		{
          			int d = (y) * 256 - g_values.screenHeight * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
         			int texY = ((d * g_values.texHeight) / spriteHeight) / 256;
         			if((get_pixel(&g_values.t_spr, texX, texY)))
						my_mlx_pixel_put(&g_values.data, stripe, y, (get_pixel(&g_values.t_spr, texX, texY)));
        		}
      		}
    	}
	}
}

int	motion()
{

	char **worldMap = g_values.matrix.worldMap;
    double posX = g_values.move.posX;
    double posY = g_values.move.posY;
    double dirX = g_values.move.dirX;
    double dirY = g_values.move.dirY;
    double moveSpeed = g_values.moveSpeed;
    
    if (g_values.keys.up)
    {
        if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == '0') g_values.move.posX += dirX * moveSpeed;
        if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == '0') g_values.move.posY += dirY * moveSpeed;
    }
    if (g_values.keys.rotate_left)
    {
        double oldDirX = g_values.move.dirX;
        g_values.move.dirX = g_values.move.dirX * cos(g_values.rotSpeed) - dirY * sin(g_values.rotSpeed);
        g_values.move.dirY = oldDirX * sin(g_values.rotSpeed) + dirY * cos(g_values.rotSpeed);
        double oldPlaneX = g_values.move.planeX;
        g_values.move.planeX = g_values.move.planeX * cos(g_values.rotSpeed) - g_values.move.planeY * sin(g_values.rotSpeed);
        g_values.move.planeY = oldPlaneX * sin(g_values.rotSpeed) + g_values.move.planeY * cos(g_values.rotSpeed);
    }
    if (g_values.keys.down)
    {
        if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == '0') g_values.move.posX -= dirX * moveSpeed;
        if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == '0') g_values.move.posY -= dirY * moveSpeed;
    }
    if (g_values.keys.left)
    {
        if(worldMap[(int)(posX - dirY * moveSpeed)][(int)(posY)] == '0') g_values.move.posX -= dirY * moveSpeed;
        if(worldMap[(int)(posX)][(int)(posY + dirX * moveSpeed)] == '0') g_values.move.posY += dirX * moveSpeed;
    }
    if (g_values.keys.right)
    {
        if(worldMap[(int)(posX + dirY * moveSpeed)][(int)(posY)] == '0') g_values.move.posX += dirY * moveSpeed;
        if(worldMap[(int)(posX)][(int)(posY - dirX * moveSpeed)] == '0') g_values.move.posY -= dirX * moveSpeed;
    }
    if (g_values.keys.rotate_right)
    {
        double oldDirX = g_values.move.dirX;
        g_values.move.dirX = g_values.move.dirX * cos(-g_values.rotSpeed) - dirY * sin(-g_values.rotSpeed);
        g_values.move.dirY = oldDirX * sin(-g_values.rotSpeed) + dirY * cos(-g_values.rotSpeed);
        double oldPlaneX = g_values.move.planeX;
        g_values.move.planeX = g_values.move.planeX * cos(-g_values.rotSpeed) - g_values.move.planeY * sin(-g_values.rotSpeed);
        g_values.move.planeY = oldPlaneX * sin(-g_values.rotSpeed) + g_values.move.planeY * cos(-g_values.rotSpeed);
    }
    return 0;
}


void clear_screen()
{
    for (int y = 0; y < g_values.screenHeight; y++)
    {
        for (int x = 0; x < g_values.screenWidth; x++)
        {
		    my_mlx_pixel_put(&g_values.data, x, y, 0x00000000);
        }
    }
}

int	next_frame()
{
	motion();
	clear_screen();
	frame();
	mlx_put_image_to_window(g_values.mlx, g_values.mlx_win, g_values.data.img, 0, 0);
	mlx_do_sync(g_values.mlx);
	return (0);
}

int check_arg2(char *str)
{
    int len = ft_strlen(str);
    return (str[len - 1] == 'b'
            && str[len - 2] == 'u'
            && str[len - 3] == 'c'
            && str[len - 4] == '.');
}


int main(int argc, char **argv)
{
	globs_init();
	g_values.mlx = mlx_init();
	if (argc == 1)
        {
			exit(0);
		}
	if ((argc == 2 && check_arg2(argv[1])))
    {
		matrix_parser(argv[1]);
		g_values.mlx_win = mlx_new_window(g_values.mlx, g_values.screenWidth, g_values.screenHeight, "CUB!");
		init_sprites();
		get_sprite();

	
		g_values.data.img = mlx_new_image(g_values.mlx, g_values.screenWidth, g_values.screenHeight);
    	g_values.data.addr = mlx_get_data_addr(g_values.data.img,
        	&g_values.data.bits_per_pixel, &g_values.data.line_length, &g_values.data.endian);

		key_init();
		mlx_hook(g_values.mlx_win, 2, 1L<<0, key_press, &g_values);
		mlx_hook(g_values.mlx_win, 3, 1L<<1, key_release, &g_values);
		mlx_hook(g_values.mlx_win, 17, 1L<<17, win_close, &g_values.move);
		mlx_loop_hook(g_values.mlx, next_frame, &g_values);
		mlx_loop(g_values.mlx);
	}
	else 
        error("Wrong input parameters");
    return 0;
}
