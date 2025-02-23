/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yobourai <yobourai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 05:14:04 by yobourai          #+#    #+#             */
/*   Updated: 2025/02/22 05:46:58 by yobourai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_exit(t_ply *ply)
{
    ftt_free(ply->map);
    free(ply->map);
    free(ply);
    exit(0);
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
	cor->win = NULL;
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
void fill_image(mlx_image_t *image, uint32_t color)
{
    for (int y = 0; y < TILE_SIZE; y++)
    {
        for (int x = 0; x < TILE_SIZE; x++)
        {
            mlx_put_pixel(image, x, y, color);
        }
    }
}

void ft_init(t_ply *mlx_ptr)
{
    mlx_ptr->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "MAP2D", false);
    if (!mlx_ptr->mlx)
    {
        fprintf(stderr, "Error: Failed to initialize MLX\n");
        exit(EXIT_FAILURE);
    }

    // Create images
    mlx_ptr->wall = mlx_new_image(mlx_ptr->mlx, TILE_SIZE, TILE_SIZE);
    mlx_ptr->zero = mlx_new_image(mlx_ptr->mlx, TILE_SIZE, TILE_SIZE);
    mlx_ptr->player = mlx_new_image(mlx_ptr->mlx, TILE_SIZE, TILE_SIZE);

    if (!mlx_ptr->wall || !mlx_ptr->zero || !mlx_ptr->player)
    {
        fprintf(stderr, "Error: Failed to create one or more MLX images\n");
        exit(EXIT_FAILURE);
    }

    printf("Images created successfully\n");

    // Fill images with colors
    fill_image(mlx_ptr->wall, 0xFFFFFF);  // White for walls
    fill_image(mlx_ptr->zero, 0x000000);  // Black for empty space
    fill_image(mlx_ptr->player, 0xFF0000); // Red for player
    if (mlx_image_to_window(mlx_ptr->mlx, mlx_ptr->wall, 10, 10) < 0)
        fprintf(stderr, "Error: Failed to attach wall image to window\n");

    if (mlx_image_to_window(mlx_ptr->mlx, mlx_ptr->zero, 100, 100) < 0)
        fprintf(stderr, "Error: Failed to attach zero image to window\n");

    if (mlx_image_to_window(mlx_ptr->mlx, mlx_ptr->player, 200, 200) < 0)
        fprintf(stderr, "Error: Failed to attach player image to window\n");
}



void window(t_ply *mlx_ptr)
{
    if (!mlx_ptr || !mlx_ptr->mlx)
    {
        fprintf(stderr, "Error: Invalid MLX pointer\n");
        return;
    }
    mlx_loop(mlx_ptr->mlx);  // This should only be called once, in main()
}

void printf_map(t_ply *map)
{
	int i = 0;
	while (map->map[i])
	{
		printf("%s", map->map[i]);
		i++;
	}
}
void draw_map(t_ply *mlx_ptr)
{
	int i = 0;
	printf_map(mlx_ptr);
    while(mlx_ptr->map[i])
    {
		int j = 0;
        while( mlx_ptr->map[i][j])
        {
            if (mlx_ptr->map[i][j] == '1')
                mlx_put_pixel(mlx_ptr->wall, j * TILE_SIZE, i * TILE_SIZE, 0xFFFFFF);
            else if (mlx_ptr->map[i][j] == '0')
                mlx_put_pixel(mlx_ptr->zero, j * TILE_SIZE, i * TILE_SIZE, 0x000000);
            else if (mlx_ptr->map[i][j] == 'P')
                mlx_put_pixel(mlx_ptr->player, j * TILE_SIZE, i * TILE_SIZE, 0xFF0000);
			j++;
        }
		i++;
    }
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
    draw_map(cortab);
	window(cortab);
    mlx_loop(cortab->mlx);

    return (0);
}
