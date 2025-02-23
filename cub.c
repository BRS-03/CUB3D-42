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
	window();
    return (0);
}