/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 05:14:04 by yobourai          #+#    #+#             */
/*   Updated: 2025/02/21 07:27:20 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ftt_free(char **str)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		*str = *(str + i);
		free(*str);
		i++;
	}
}
void	ft_init(t_ply *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (info->map[i][j] == 'P')
			{
				info->pos_y = i;
				info->pos_x = j;
				return ;
			}
			j++;
		}
		i++;
	}
}
void	ft_exit(t_ply *ply)
{
    ftt_free(ply->map);
    free(ply->map);
    free(ply);
    exit(0);
}

void	update_player_position(t_ply *prm, int new_y, int new_x)
{
    prm->map[new_y][new_x] = 'p';
    prm->map[prm->pos_y][prm->pos_x] = '0';
    mlx_image_to_window(prm->mlx, prm->zero, prm->pos_x * 50, prm->pos_y * 50);
    prm->pos_y = new_y;
    prm->pos_x = new_x;
    mlx_image_to_window(prm->mlx, prm->player, prm->pos_x * 50, prm->pos_y * 50);
}

void	handle_movement(t_ply *prm, int dy, int dx, mlx_key_data_t keyboard)
{
    int	new_y;
    int	new_x;

    new_y = prm->pos_y + dy;
    new_x = prm->pos_x + dx;
    if (prm->map[new_y][new_x] != '1' && (keyboard.action == MLX_PRESS
            || keyboard.action == MLX_REPEAT))
    {
        update_player_position(prm, new_y, new_x);
    }
}

void	ft_graph(t_ply *mpr)
{
    int	i;
    int	j;

    i = 0;
    j = 0;
    while (mpr->map[i])
    {
        j = 0;
        while (mpr->map[i][j])
        {
            if (mpr->map[i][j] == '1')
                mlx_image_to_window(mpr->mlx, mpr->wall, j * 50, i * 50);
            if (mpr->map[i][j] == '0' || mpr->map[i][j] == 'P')
                return ;
            j++;
        }
        i++;
    }
}
void	handle_image_load_failure(t_ply *mpr, int count)
{
	if (count >= 1)
		mlx_delete_image(mpr->mlx, mpr->wall);
	if (count >= 2)
		mlx_delete_image(mpr->mlx, mpr->player);
	mlx_terminate(mpr->mlx);
	exit(EXIT_FAILURE);
}

mlx_image_t	*load_texture_as_image(t_ply *mpr, const char *path)
{
	mlx_texture_t	*texture;
	mlx_image_t		*image;

	texture = mlx_load_png(path);
	if (!texture)
		return (NULL);
	image = mlx_texture_to_image(mpr->mlx, texture);
	mlx_delete_texture(texture);
	if (!image)
		return (NULL);
	return (image);
}
void	ft_hook(mlx_key_data_t keyboard, void *param)
{
	t_ply	*prm;

	prm = (t_ply *)param;
	if (keyboard.key == MLX_KEY_ESCAPE)
	{
		ftt_free(prm->map);
		free(prm->map);
		free(prm);
		exit(0);
	}
	if (keyboard.key == MLX_KEY_UP)
		handle_movement(prm, -1, 0, keyboard);
	else if (keyboard.key == MLX_KEY_DOWN)
		handle_movement(prm, 1, 0, keyboard);
	else if (keyboard.key == MLX_KEY_LEFT)
		handle_movement(prm, 0, -1, keyboard);
	else if (keyboard.key == MLX_KEY_RIGHT)
		handle_movement(prm, 0, 1, keyboard);
}
void	setup_images(t_ply *mpr)
{
	mpr->wall = load_texture_as_image(mpr, "./textures/images.png");
	if (!mpr->wall)
		handle_image_load_failure(mpr, 0);
	mpr->player = load_texture_as_image(mpr, "./textures/player.png");
	if (!mpr->player)
		handle_image_load_failure(mpr, 1);
	mpr->zero = load_texture_as_image(mpr, "./textures/wero.png");
	if (!mpr->zero)
		handle_image_load_failure(mpr, 2);
}
int	ft_count_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}
void	handle_allocation_error(t_ply *kask, char **tmp)
{
	ftt_free(kask->map);
	if (kask->map)
		free(kask->map);
	ftt_free(tmp);
	if (tmp)
		free(tmp);
	free(kask);
	exit(1);
}
void	copy_map(t_ply *kask, char **tmp)
{
	int	i;

	i = 0;
	while (kask->map[i])
	{
		tmp[i] = ft_strdup(kask->map[i]);
		if (!tmp[i])
			handle_allocation_error(kask, tmp);
		i++;
	}
	tmp[i] = NULL;
}
void	parsse_error(t_ply *kask)
{
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc((ft_count_map(kask->map) + 1) * sizeof(char *));
	if (!tmp)
	{
		handle_allocation_error(kask, NULL);
	}
	copy_map(kask, tmp);
	ftt_free(tmp);
	free(tmp);
}
t_ply	*allocat(void)
{
	t_ply	*cor;

	cor = NULL;
	cor = malloc(sizeof(t_ply));
	if (!cor)
		exit(1);
	cor->map = NULL;
	cor->mlx = NULL;
	cor->wall = NULL;
	cor->zero = NULL;
	cor->player = NULL;
	return (cor);
}
int	county_line(char *file)
{
	char	buffer[100];
	int		fd;
	int		nline;
	int		i;

	nline = 1;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while (read(fd, buffer + i, 1) > 0)
	{
		if (i > 51 || nline > 28)
		{
			close(fd);
			return (0);
		}
		if (buffer[i] == '\n')
		{
			nline++;
			i = -1;
		}
		i++;
	}
	return (close(fd), nline);
}
char	**ft_read_map(char *mp)
{
	int		line_count;
	int		i;
	char	*line;
	int		fd;
	char	**map;

	i = -1;
	line_count = county_line(mp);
	if (!line_count)
		return (NULL);
	fd = open(mp, O_RDONLY);
	map = malloc((line_count + 1) * sizeof(char *));
	if (!map)
		return (close(fd), NULL);
	line = get_next_line(fd);
	while (line != NULL || line_count > i)
	{
		map[++i] = line;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (close(fd), map);
}

void	files(int ac, char *av[])
{
	int	len;

	if (ac != 2)
	{
		printf("Error: name of the map !!\n");
		exit(EXIT_FAILURE);
	}
	len = 0;
	while (av[1][len] != '\0')
		len++;
	if (len < 4 || av[1][len - 1] != 'r' || av[1][len - 2] != 'e' || av[1][len
		- 3] != 'b' || av[1][len - 4] != '.')
	{
		printf("Invalid file extension expected .ber\n");
		exit(EXIT_FAILURE);
	}
}
void	initialize_mlx(t_ply *mpr)
{
	int	width;
	int	height;

	width = strlen(mpr->map[0]) * 50 - 50;
	height = ft_count_map(mpr->map) * 50;
	mpr->mlx = mlx_init(width, height, "so_long", false);
	if (!mpr->mlx)
	{
		printf("Failed to initialize mlx\n");
		exit(EXIT_FAILURE);
	}
}
int	game(t_ply *mpr)
{
	initialize_mlx(mpr);
	setup_images(mpr);
	if (!mpr->wall || !mpr->player || !mpr->zero)
		return (0);
	ft_graph(mpr);
	mlx_key_hook(mpr->mlx, ft_hook, mpr);
	mlx_loop(mpr->mlx);
	mlx_terminate(mpr->mlx);
	return (EXIT_SUCCESS);
}
int	main(int ac, char **av)
{
    t_ply	*cortab;
    files(ac, av);
	cortab = allocat();
	if (!cortab)
		return (1);
	cortab->map = ft_read_map(av[1]);
	if (!cortab->map)
	{
		free(cortab);
		printf("error\n");
		return (1);
	}
	ft_init(cortab);
	if(!game(cortab))
	{
		return (1);
	}
    return (0);
}