// // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		// float rayDirX0 = g_cub.player.dirX - g_cub.player.planeX;
		// float rayDirY0 = g_cub.player.dirY - g_cub.player.planeY;
		// float rayDirX1 = g_cub.player.dirX + g_cub.player.planeX;
		// float rayDirY1 = g_cub.player.dirY + g_cub.player.planeY;
		// // Current y position compared to the center of the screen (the horizon)
		// int p = y - window->height / 2;
		// // Vertical position of the camera.
		// float posZ = 0.5 * window->height;
		// // Horizontal distance from the camera to the floor for the current row.
		// // 0.5 is the z position exactly in the middle between floor and ceiling.
		// float rowDistance = posZ / p;
		// // calculate the real world step vector we have to add for each x (parallel to camera plane)
		// // adding step by step avoids multiplications with a weight in the inner loop
		// float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / window->width;
		// float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / window->width;
		// // real world coordinates of the leftmost column. This will be updated as we step to the right.
		// float floorX = g_cub.player.posX + rowDistance * rayDirX0;
		// float floorY = g_cub.player.posY + rowDistance * rayDirY0;
		// for(int x = 0; x < window->width; ++x)
		// {
		// 	// the cell coord is simply got from the integer parts of floorX and floorY
		// 	int cellX = (int)(floorX);
		// 	int cellY = (int)(floorY);
		// 	// get the texture coordinate from the fractional part
		// 	int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
		// 	int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
		// 	floorX += floorStepX;
		// 	floorY += floorStepY;
		// 	// choose texture and draw the pixel
		// 	int checkerBoardPattern = (int)(cellX + cellY) & 1;
		// 	int floorTexture;
		// 	if(checkerBoardPattern == 0) floorTexture = 3;
		// 	else floorTexture = 4;
		// 	int ceilingTexture = 6;
		// 	int color;
		// 	// floor
		// 	color = g_cub.texture[floorTexture][texWidth * ty + tx];
		// 	color = (color >> 1) & 8355711; // make a bit darker
		// 	window->buf[y][x] = color;
		// 	//ceiling (symmetrical, at height - y - 1 instead of y)
		// 	color = g_cub.texture[ceilingTexture][texWidth * ty + tx];
		// 	color = (color >> 1) & 8355711; // make a bit darker
		// 	window->buf[window->height - y - 1][x] = color;
		// }