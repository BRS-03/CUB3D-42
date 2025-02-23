/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 05:14:16 by yobourai          #+#    #+#             */
/*   Updated: 2025/02/22 05:13:19 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB_H
# define CUB_H

# include "/Users/yobourai/Desktop/CUB3D-42/MLX42/include/MLX42/MLX42.h"
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <limits.h>
# include <string.h>


typedef struct s_ply
{
	char		**map;
	int			pos_x;
	int			pos_y;
	void 		*win;
	mlx_t		*mlx;
	mlx_image_t	*wall;
	mlx_image_t	*zero;
	mlx_image_t	*player;
}				t_ply;

#endif