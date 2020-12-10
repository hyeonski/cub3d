/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lodev.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 19:53:20 by yohlee            #+#    #+#             */
/*   Updated: 2020/12/10 17:31:33 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// char	worldMap[mapWidth][mapHeight] =
// {
// 	{'1','1','1','1','1','1'},
// 	{'1','0','0','0','0','1'},
// 	{'1','0','1','0','0','1'},
// 	{'1','0','0','0','0','1'},
// 	{'1','0','0','0','0','1'},
// 	{'1','1','1','1','1','1'}
// };

void	draw(t_info *info)
{
	for (int y = 0; y < g_cub.window.height; y++)
	{
		for (int x = 0; x < g_cub.window.width; x++)
		{
			info->img.data[y * g_cub.window.width + x] = g_cub.window.buf[y][x];
		}
	}
	mlx_put_image_to_window(g_cub.mlx, g_cub.win, info->img.img, 0, 0);
}

void	calc(t_info *info)
{
	//FLOOR CASTING
	for(int y = 0; y < g_cub.window.height; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		g_cub.temp.rayDirX0 = g_cub.player.dirX - g_cub.player.planeX;
		g_cub.temp.rayDirY0 = g_cub.player.dirY - g_cub.player.planeY;
		g_cub.temp.rayDirX1 = g_cub.player.dirX + g_cub.player.planeX;
		g_cub.temp.rayDirY1 = g_cub.player.dirY + g_cub.player.planeY;

		// Current y position compared to the center of the screen (the horizon)
		g_cub.temp.p = y - g_cub.window.height / 2;

		// Vertical position of the camera.
		g_cub.temp.posZ = 0.5 * g_cub.window.height;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		g_cub.temp.rowDistance = g_cub.temp.posZ / g_cub.temp.p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		g_cub.temp.floorStepX = g_cub.temp.rowDistance * (g_cub.temp.rayDirX1 - g_cub.temp.rayDirX0) / g_cub.window.width;
		g_cub.temp.floorStepY = g_cub.temp.rowDistance * (g_cub.temp.rayDirY1 - g_cub.temp.rayDirY0) / g_cub.window.width;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		g_cub.temp.floorX = g_cub.player.posX + g_cub.temp.rowDistance * g_cub.temp.rayDirX0;
		g_cub.temp.floorY = g_cub.player.posY + g_cub.temp.rowDistance * g_cub.temp.rayDirY0;

		for(int x = 0; x < g_cub.window.width; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			g_cub.temp. cellX = (int)(g_cub.temp.floorX);
			g_cub.temp. cellY = (int)(g_cub.temp.floorY);

			// get the texture coordinate from the fractional part
			g_cub.temp.tx = (int)(g_cub.texture[0].width * (g_cub.temp.floorX - g_cub.temp.cellX)) & (g_cub.texture[0].width - 1);
			g_cub.temp.ty = (int)(g_cub.texture[0].height * (g_cub.temp.floorY - g_cub.temp.cellY)) & (g_cub.texture[0].height - 1);

			g_cub.temp.floorX += g_cub.temp.floorStepX;
			g_cub.temp.floorY += g_cub.temp.floorStepY;

			// choose texture and draw the pixel
			g_cub.temp.floorTexture = 3;
			g_cub.temp.ceilingTexture = 6;

			// floor
			g_cub.temp.color = g_cub.texture[g_cub.temp.floorTexture].data[g_cub.texture[0].width * g_cub.temp.ty + g_cub.temp.tx];
			g_cub.temp.color = (g_cub.temp.color >> 1) & 8355711; // make a bit darker

			g_cub.window.buf[y][x] = g_cub.temp.color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			g_cub.temp.color = g_cub.texture[g_cub.temp.ceilingTexture].data[g_cub.texture[0].width * g_cub.temp.ty + g_cub.temp.tx];
			g_cub.temp.color = (g_cub.temp.color >> 1) & 8355711; // make a bit darker

			g_cub.window.buf[g_cub.window.height - y - 1][x] = g_cub.temp.color;
		}
	}
	//WALL CASTING
	for(int x = 0; x < g_cub.window.width; x++)
	{
		g_cub.temp.cameraX = 2 * x / (double)g_cub.window.width - 1;
		g_cub.temp.rayDirX = g_cub.player.dirX + g_cub.player.planeX * g_cub.temp.cameraX;
		g_cub.temp.rayDirY = g_cub.player.dirY + g_cub.player.planeY * g_cub.temp.cameraX;
		
		g_cub.temp.mapX = (int)g_cub.player.posX;
		g_cub.temp.mapY = (int)g_cub.player.posY;

		//length of ray from current position to next x or y-side
		
		//length of ray from one x or y-side to next x or y-side
		g_cub.temp.deltaDistX = fabs(1 / g_cub.temp.rayDirX);
		g_cub.temp.deltaDistY = fabs(1 / g_cub.temp.rayDirY);
		
		//what direction to step in x or y-direction (either +1 or -1)
		
		g_cub.temp.hit = 0; //was there a wall hit?

		if (g_cub.temp.rayDirX < 0)
		{
			g_cub.temp.stepX = -1;
			g_cub.temp.sideDistX = (g_cub.player.posX - g_cub.temp.mapX) * g_cub.temp.deltaDistX;
		}
		else
		{
			g_cub.temp.stepX = 1;
			g_cub.temp.sideDistX = (g_cub.temp.mapX + 1.0 - g_cub.player.posX) * g_cub.temp.deltaDistX;
		}
		if (g_cub.temp.rayDirY < 0)
		{
			g_cub.temp.stepY = -1;
			g_cub.temp.sideDistY = (g_cub.player.posY - g_cub.temp.mapY) * g_cub.temp.deltaDistY;
		}
		else
		{
			g_cub.temp.stepY = 1;
			g_cub.temp.sideDistY = (g_cub.temp.mapY + 1.0 - g_cub.player.posY) * g_cub.temp.deltaDistY;
		}

		while (g_cub.temp.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (g_cub.temp.sideDistX < g_cub.temp.sideDistY)
			{
				g_cub.temp.sideDistX += g_cub.temp.deltaDistX;
				g_cub.temp.mapX += g_cub.temp.stepX;
				g_cub.temp.side = 0;
			}
			else
			{
				g_cub.temp.sideDistY += g_cub.temp.deltaDistY;
				g_cub.temp.mapY += g_cub.temp.stepY;
				g_cub.temp.side = 1;
			}
			//Check if ray has hit a wall
			if (g_cub.map.data[g_cub.temp.mapX][g_cub.temp.mapY] > '0')
				g_cub.temp.hit = 1;
		}
		if (g_cub.temp.side == 0)
			g_cub.temp.perpWallDist = (g_cub.temp.mapX - g_cub.player.posX + (1 - g_cub.temp.stepX) / 2) / g_cub.temp.rayDirX;
		else
			g_cub.temp.perpWallDist = (g_cub.temp.mapY - g_cub.player.posY + (1 - g_cub.temp.stepY) / 2) / g_cub.temp.rayDirY;

		//Calculate height of line to draw on screen
		g_cub.temp.lineHeight = (int)(g_cub.window.height / g_cub.temp.perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		g_cub.temp.drawStart = -g_cub.temp.lineHeight / 2 + g_cub.window.height / 2;
		if (g_cub.temp.drawStart < 0)
			g_cub.temp.drawStart = 0;
		g_cub.temp.drawEnd = g_cub.temp.lineHeight / 2 + g_cub.window.height / 2;
		if (g_cub.temp.drawEnd >= g_cub.window.height)
			g_cub.temp.drawEnd = g_cub.window.height - 1;

		// texturing calculations
		// info->temp.texNum = worldMap[info->temp.mapX][info->temp.mapY] - 1;
		if (g_cub.temp.side == 1)
		{
			g_cub.temp.texNum = g_cub.temp.rayDirY > 0 ? 0 : 1;
		}
		else
		{
			g_cub.temp.texNum = g_cub.temp.rayDirX > 0 ? 2 : 3;
		}


		// calculate value of wallX
		if (g_cub.temp.side == 0)
			g_cub.temp.wallX = g_cub.player.posY + g_cub.temp.perpWallDist * g_cub.temp.rayDirY;
		else
			g_cub.temp.wallX = g_cub.player.posX + g_cub.temp.perpWallDist * g_cub.temp.rayDirX;
		g_cub.temp.wallX -= floor(g_cub.temp.wallX);

		// x coordinate on the texture
		g_cub.temp.texX = (int)(g_cub.temp.wallX * (double)g_cub.texture[0].width);
		if (g_cub.temp.side == 0 && g_cub.temp.rayDirX > 0)
			g_cub.temp.texX = g_cub.texture[0].width - g_cub.temp.texX - 1;
		if (g_cub.temp.side == 1 && g_cub.temp.rayDirY < 0)
			g_cub.temp.texX = g_cub.texture[0].width - g_cub.temp.texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		g_cub.temp.step = 1.0 * g_cub.texture[0].height / g_cub.temp.lineHeight;

		// Starting texture coordinate
		g_cub.temp.texPos = (g_cub.temp.drawStart - g_cub.window.height / 2 + g_cub.temp.lineHeight / 2) * g_cub.temp.step;

		for (int y = g_cub.temp.drawStart; y < g_cub.temp.drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (g_cub.texture[0].height - 1) in case of overflow
			g_cub.temp.texY = (int)g_cub.temp.texPos & (g_cub.texture[0].height - 1);
			g_cub.temp.texPos += g_cub.temp.step;

			g_cub.temp.color = g_cub.texture[g_cub.temp.texNum].data[g_cub.texture[0].height * g_cub.temp.texY + g_cub.temp.texX];

			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (g_cub.temp.side == 1)
				g_cub.temp.color = (g_cub.temp.color >> 1) & 8355711;

			g_cub.window.buf[y][x] = g_cub.temp.color;
		}

		//FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)

		//4 different wall directions possible
		if (g_cub.temp.side == 0 && g_cub.temp.rayDirX > 0)
		{
			g_cub.temp.floorXWall = g_cub.temp.mapX;
			g_cub.temp.floorYWall = g_cub.temp.mapY + g_cub.temp.wallX;
		}
		else if(g_cub.temp.side == 0 && g_cub.temp.rayDirX < 0)
		{
			g_cub.temp.floorXWall = g_cub.temp.mapX + 1.0;
			g_cub.temp.floorYWall = g_cub.temp.mapY + g_cub.temp.wallX;
		}
		else if(g_cub.temp.side == 1 && g_cub.temp.rayDirY > 0)
		{
			g_cub.temp.floorXWall =g_cub.temp. mapX + g_cub.temp.wallX;
			g_cub.temp.floorYWall =g_cub.temp. mapY;
		}
		else
		{
			g_cub.temp.floorXWall =g_cub.temp. mapX + g_cub.temp.wallX;
			g_cub.temp.floorYWall = g_cub.temp.mapY + 1.0;
		}


		g_cub.temp.distWall = g_cub.temp.perpWallDist;
		g_cub.temp.distPlayer = 0.0;

		if (g_cub.temp.drawEnd < 0)
			g_cub.temp.drawEnd = g_cub.window.height; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for (int y = g_cub.temp.drawEnd + 1; y < g_cub.window.height; y++)
		{
			g_cub.temp.currentDist = g_cub.window.height / (2.0 * y - g_cub.window.height); //you could make a small lookup table for this instead

			g_cub.temp.weight = (g_cub.temp.currentDist - g_cub.temp.distPlayer) / (g_cub.temp.distWall - g_cub.temp.distPlayer);

			g_cub.temp.currentFloorX = g_cub.temp.weight * g_cub.temp.floorXWall + (1.0 - g_cub.temp.weight) * g_cub.player.posX;
			g_cub.temp.currentFloorY = g_cub.temp.weight * g_cub.temp.floorYWall + (1.0 - g_cub.temp.weight) * g_cub.player.posY;

			g_cub.temp.floorTexX = (int)(g_cub.temp.currentFloorX * g_cub.texture[0].width) % g_cub.texture[0].width;
			g_cub.temp.floorTexY = (int)(g_cub.temp.currentFloorY * g_cub.texture[0].height) % g_cub.texture[0].height;

			g_cub.temp.floorTexture = 3;

			//floor
			g_cub.window.buf[y][x] = (g_cub.texture[g_cub.temp.floorTexture].data[g_cub.texture[0].width * g_cub.temp.floorTexY + g_cub.temp.floorTexX] >> 1) & 8355711;
			//ceiling (symmetrical!)
			g_cub.window.buf[g_cub.window.height - y][x] = g_cub.texture[3].data[g_cub.texture[0].width * g_cub.temp.floorTexY + g_cub.temp.floorTexX];
		}
	}
}

int	main_loop(t_info *info)
{
	calc(info);
	draw(info);
	return (0);
}

int	key_press(int key, t_info *info)
{
	if (key == KEY_W)
	{
		if (g_cub.map.data[(int)(g_cub.player.posX + g_cub.player.dirX * g_cub.player.moveSpeed)][(int)(g_cub.player.posY)] == '0')
			g_cub.player.posX += g_cub.player.dirX * g_cub.player.moveSpeed;
		if (g_cub.map.data[(int)(g_cub.player.posX)][(int)(g_cub.player.posY + g_cub.player.dirY * g_cub.player.moveSpeed)] == '0')
			g_cub.player.posY += g_cub.player.dirY * g_cub.player.moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == KEY_S)
	{
		if (g_cub.map.data[(int)(g_cub.player.posX - g_cub.player.dirX * g_cub.player.moveSpeed)][(int)(g_cub.player.posY)] == '0')
			g_cub.player.posX -= g_cub.player.dirX * g_cub.player.moveSpeed;
		if (g_cub.map.data[(int)(g_cub.player.posX)][(int)(g_cub.player.posY - g_cub.player.dirY * g_cub.player.moveSpeed)] == '0')
			g_cub.player.posY -= g_cub.player.dirY * g_cub.player.moveSpeed;
	}
	//rotate to the right
	if (key == KEY_D)
	{
		//both camera direction and camera plane must be rotated
		g_cub.temp.oldDirX = g_cub.player.dirX;
		g_cub.player.dirX = g_cub.player.dirX * cos(-g_cub.player.rotSpeed) - g_cub.player.dirY * sin(-g_cub.player.rotSpeed);
		g_cub.player.dirY = g_cub.temp.oldDirX * sin(-g_cub.player.rotSpeed) + g_cub.player.dirY * cos(-g_cub.player.rotSpeed);
		g_cub.temp.oldPlaneX = g_cub.player.planeX;
		g_cub.player.planeX = g_cub.player.planeX * cos(-g_cub.player.rotSpeed) - g_cub.player.planeY * sin(-g_cub.player.rotSpeed);
		g_cub.player.planeY = g_cub.temp.oldPlaneX * sin(-g_cub.player.rotSpeed) + g_cub.player.planeY * cos(-g_cub.player.rotSpeed);
	}
	//rotate to the left
	if (key == KEY_A)
	{
		//both camera direction and camera plane must be rotated
		g_cub.temp.oldDirX = g_cub.player.dirX;
		g_cub.player.dirX = g_cub.player.dirX * cos(g_cub.player.rotSpeed) - g_cub.player.dirY * sin(g_cub.player.rotSpeed);
		g_cub.player.dirY = g_cub.temp.oldDirX * sin(g_cub.player.rotSpeed) + g_cub.player.dirY * cos(g_cub.player.rotSpeed);
		g_cub.temp.oldPlaneX = g_cub.player.planeX;
		g_cub.player.planeX = g_cub.player.planeX * cos(g_cub.player.rotSpeed) - g_cub.player.planeY * sin(g_cub.player.rotSpeed);
		g_cub.player.planeY = g_cub.temp.oldPlaneX * sin(g_cub.player.rotSpeed) + g_cub.player.planeY * cos(g_cub.player.rotSpeed);
	}
	if (key == KEY_ESC)
		exit(0);
	printf("x: %f , y: %f\n", g_cub.player.posX, g_cub.player.posY);
	return (0);
}

int	main(int ac, char **av)
{
	t_str_arr	str_arr;

	g_cub.mlx = mlx_init();
	g_cub.player.posX = 1.1;
	g_cub.player.posY = 1.5;
	g_cub.player.dirX = -1.0;
	g_cub.player.dirY = 0.0;
	g_cub.player.planeX = 0.0;
	g_cub.player.planeY = 0.66;
	g_cub.player.moveSpeed = 0.05;
	g_cub.player.rotSpeed = 0.05;

	map_parser(av[1], &str_arr);
	
	// g_cub.win = mlx_new_window(info.mlx, width, height, "mlx");

	// info.img.img = mlx_new_image(info.mlx, width, height);
	// info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);

	mlx_loop_hook(g_cub.mlx, &main_loop, &g_cub);
	mlx_hook(g_cub.win, X_EVENT_KEY_PRESS, 0, &key_press, &g_cub);

	mlx_loop(g_cub.mlx);
}